#include <sklib.h>

//function to insert new parameters in the HTTP headers linked list
void insert(struct list *pList, char *newParam)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));

    newNode->param = malloc(strlen(newParam)+1);
    strcpy(newNode->param,newParam);

    if (pList->firstNode == NULL)
    {
        pList->firstNode = newNode;
        newNode->nextNode = NULL;
    }

    else
    {
        struct node *pos = pList->firstNode;
        for(; pos->nextNode; pos = pos->nextNode);
        pos->nextNode = newNode;
        newNode->nextNode = NULL;
    }

}

//function to compare couples of double values to sort the times arrays
int compare (const void * a, const void * b)
{
  if ( *(double*)a == *(double*)b ) return 0;
  else if ( *(double*)a <  *(double*)b ) return -1;
  else return 1;
}

//function to obtain the median from an array
double Median(double *array, size_t length)
{
    if(length % 2 == 0)
    {
        double median = (array[length / 2] + array[length / 2 - 1]) / 2.0;
        return median;
    }
    else 
    {
        double median = array[length / 2];
        return median;
    }
}

//main function 
void TestandMetrics(int n, struct list *lst, int t)
{
    CURL *curl;
    CURLcode res;
    int http_code = 0;
    char *ip;
    double lookuptime;
    double connecttime;
    double starttime;
    double totaltime;
    double total_lookuptime;
    double total_connecttime;
    double total_starttime;
    double total_totaltime;
    double* Arraylookuptime=(double*) malloc(n*sizeof(double));
    double* Arrayconnecttime=(double*) malloc(n*sizeof(double));
    double* Arraystarttime=(double*) malloc(n*sizeof(double));
    double* Arraytotaltime=(double*) malloc(n*sizeof(double));

    struct curl_slist *headerlist=NULL;
    struct node *tmp = lst->firstNode;

    //number of HTTP request can't be less than 1
    if(n < 1){
        n = 1;
    }

    if(t > UINT_MAX){ //POSIX / ISO C compliance
        printf("Error: time between requests cannot be more than: %d", UINT_MAX);
        t=UINT_MAX;
    }

    for(int k=0;k<n;k++){
        //get the CURL easy handle
        curl = curl_easy_init();
        //set the URL to work on
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/");
        //avoid curl to print the output from the request
        curl_easy_setopt(curl, CURLOPT_NOBODY,1);

        //add all the extra HTTP headers
        while(tmp){
            headerlist = curl_slist_append(headerlist, tmp->param);
            tmp=tmp->nextNode;
        }
        //headerlist = curl_slist_append(headerlist, "Connection: MyConnection");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

        //perform the request 
        res = curl_easy_perform(curl);

        if(res == CURLE_OK)
        {
            //grab the IP value
            res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip);
            if(res != CURLE_OK) {
                printf("Error getting the SERVER IP: %s", curl_easy_strerror(res));
            }
            //grab the HTTP return code
            res = curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            if(res != CURLE_OK) {
                printf("Error getting the RESPONSE CODE: %s", curl_easy_strerror(res));
            }
            //grab the NAME LOOKUP TIME
            res = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &lookuptime);
            if(res != CURLE_OK) {
                printf("Error getting the NAMELOOKUP TIME: %s", curl_easy_strerror(res));
            }
            //grab the CONNECT TIME
            res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connecttime);
            if(res != CURLE_OK) {
                printf("Error getting the CONNECT TIME: %s", curl_easy_strerror(res));
            }
            //grab the STARTTRANSFER TIME
            res = curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &starttime);
            if(res != CURLE_OK) {
                printf("Error getting the START TRANSFER TIME: %s", curl_easy_strerror(res));
            }
            //grab the TOTAL TIME
            res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totaltime);
            if(res != CURLE_OK) {
                printf("Error getting the TOTAL TIME: %s", curl_easy_strerror(res));
            }

            //printf("lookuptime %f connecttime %f starttime %f totaltime %f\n",lookuptime,connecttime,starttime,totaltime);
            Arraylookuptime[k]=lookuptime;
            Arrayconnecttime[k]=connecttime;
            Arraystarttime[k]=starttime;
            Arraytotaltime[k]=totaltime;
        }
        else //error
        {
            printf("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }
        //release the easy handle
        curl_easy_cleanup(curl);

        if(t>0)
        {
            //sleep the time between requests
            sleep(t);
        }
    }
    //Calculate the median for the 4 time values
    qsort(Arraylookuptime, n, sizeof(double), compare);
    total_lookuptime = Median(Arraylookuptime,n);

    qsort(Arrayconnecttime, n, sizeof(double), compare);
    total_connecttime = Median(Arrayconnecttime,n);

    qsort(Arraystarttime, n, sizeof(double), compare);
    total_starttime = Median(Arraystarttime,n);

    qsort(Arraytotaltime, n, sizeof(double), compare);
    total_totaltime = Median(Arraytotaltime,n);

    //output information format:
    //SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;
    //<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>
    printf("SKTEST;%s;%d;%f;%f;%f;%f\n",ip,http_code,total_lookuptime,total_connecttime,total_starttime,total_totaltime);

    free(Arraylookuptime);
    free(Arrayconnecttime);
    free(Arraystarttime);
    free(Arraytotaltime);

    return;
}