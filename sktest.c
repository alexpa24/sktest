#include <stdlib.h> //for atoi()
#include <sklib.h>
 
int main(int argc, char *argv[])
{
    int n = 1; //the number of HTTP requests by default

    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-n") == 0) //number of HTTP requests to make
            {   
                n = atoi(argv[i+1]);   
                i++;
            }
        }
    }
 
    TestandMetrics(n);
    return 0;
}