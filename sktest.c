#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h> //for atoi()
#include <string.h> //for strcmp()
 
int main(int argc, char *argv[])
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
    int n = 1; //the number of HTTP requests by default

    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-n") == 0) //number of HTTP requests to make
            {   
                n = atoi(argv[i+1]);   
                if(n < 1){
                    printf("Error: Incorrect number of HTTP requests to make %d", n);
                    n = 1;
                }
                i++;
            }
        }
    }
 
    curl = curl_easy_init();
    if(curl) {
        for(int k=0;k<n;k++){
            curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/");
            //avoid curl to print the output from the request
            curl_easy_setopt(curl, CURLOPT_NOBODY,1);

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
                
                total_lookuptime = total_lookuptime + lookuptime;
                total_connecttime = total_connecttime + connecttime;
                total_starttime = total_starttime + starttime;
                total_totaltime = total_totaltime + totaltime;
            }
            else //error
            {
                printf("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            }
        }
        total_lookuptime = total_lookuptime / n;
        total_connecttime = total_connecttime / n;
        total_starttime = total_starttime / n;
        total_totaltime = total_totaltime / n;
        //output information format:
        //SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;
        //<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>
        printf("SKTEST;%s;%d;%f;%f;%f;%f\n",ip,http_code,total_lookuptime,total_connecttime,total_starttime,total_totaltime);

        //cleanup
        curl_easy_cleanup(curl);
    }
    return 0;
}