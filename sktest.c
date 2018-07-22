#include <stdlib.h> //for atoi()
#include <sklib.h>

int main(int argc, char *argv[])
{
    int n = 1; //the number of HTTP requests by default
    int t = 0; //time between requests
    struct curl_slist *headerlist=NULL;

    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-n") == 0) //number of HTTP requests to make
            {   
                n = atoi(argv[i+1]); 
                i++;
            }
            if (strcmp(argv[i], "-H") == 0) //HTTP header information
            {   
                headerlist = curl_slist_append(headerlist, argv[i+1]);
                i++;
            }
            if (strcmp(argv[i], "-t") == 0) //HTTP time between request
            {   
                t = atoi(argv[i+1]);   
                i++;
            }
        }
    }
    
    //call to the sklib function with the parameters
    TestandMetrics(n,headerlist,t);
    return 0;
}