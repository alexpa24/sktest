#include <stdio.h>
#include <curl/curl.h>
#include <string.h> //for strcmp()
#include <stdlib.h> //for qsort
#include <unistd.h> // for the sleep() function in Unix

int compare (const void * a, const void * b);
double Median(double *array, size_t length);
void TestandMetrics(int n, struct curl_slist *hlist, int t);