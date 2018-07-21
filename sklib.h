#include <stdio.h>
#include <curl/curl.h>
#include <string.h> //for strcmp()
#include <stdlib.h> //for qsort

#ifdef _WIN32
#include <Windows.h> //for the Sleep() function in Windows
#else
#include <unistd.h> // for the sleep() function in Unix
#endif

struct node
{
    char *param;
    struct node *nextNode;
};

struct list
{
    struct node *firstNode;
};

void insert(struct list *pList, char *newParam);
int compare (const void * a, const void * b);
double Median(double *array, size_t length);
void TestandMetrics(int n, struct list *lst, int t);