#include <stdlib.h> //for atoi()
#include <sklib.h>

int main(int argc, char *argv[])
{
    int n = 1; //the number of HTTP requests by default
    int t = 0; //time between requests
    struct list lst;
    struct list *plst = &lst;

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
                insert(plst, argv[i+1]);
                i++;
            }
            if (strcmp(argv[i], "-t") == 0) //HTTP time between request
            {   
                t = atoi(argv[i+1]);   
                i++;
            }
        }
    }
 
    TestandMetrics(n,plst,t);
    return 0;
}