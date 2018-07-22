# sktest
sktest is an application that allows to test the connectivity status to http://www.google.com/, via the sklib library.
This library executes the specific functions needed in order to perform the mentioned test.

# Code style
The code is written in C using POSIX / ISO C standards.

# Installation
First the libcurl external library has to be installed, as the sklib will need it. This library can be downloaded from: https://curl.haxx.se/download.html
After the download, the library will be installed in a Unix machine using the following commands:
```
./configure
make
make test (optional)
make install (requires root)
```

Then the repo can be cloned using:
```
git clone https://github.com/alexpa24/sktest.git
```

# Built
Use the makefile provided to build the sktest application in a Unix machine by using the below command:
```
make sktest
```
Another command alternative would be:
```
gcc -o sktest sktest.c sklib.c -lcurl -I.
```

# How to use?
Once the application is compiled, it can run:
```
./sktest -n <number of HTTP requests> - H <Header-name: Header-value> -t <time between requests>
```

All the arguments are optional. The number of requests is 1 and the time between requests is 0 by default. The parameter -H can be used multiple times to add additional HTTP headers.

For example:
```
./sktest -n 3 -H Connection: keep-alive -t 5
```

# Tests
The parameter time between request (-t) has been added in order to space the different HTTP requests and get a better sample for the statistic analysis.

The application has been tested in a Macbook machine with Mac OS 10.13.6 and curl 7.61.0. The results with different input parameters are the following:

```
MBPdeAlejandro:sktest alex$ ./sktest -n 3 -t 2
SKTEST;2a00:1450:4009:813::2004;200;0.001375;0.024575;0.087812;0.087846
MBPdeAlejandro:sktest alex$ ./sktest
SKTEST;2a00:1450:4009:813::2004;200;0.001870;0.026070;0.087508;0.087574
MBPdeAlejandro:sktest alex$ ./sktest -n 10
SKTEST;2a00:1450:4009:813::2004;200;0.001182;0.023435;0.089413;0.089445
```

# Future improvement areas
One usefull improvement of the application would be to pass the target URL as an argument. In this way the library wouldn´t just test the connection to google.com, but to any remote server.

Since the purpose of the application is to make a POSIX / ISO C compliant code, there are some modifications required to make it portable to Windows that are proposed here and not added to the code. Change the sleep line in sklib.c for:
```
if(t>0)
    //sleep the time between requests
    #ifdef _WIN32
    Sleep(t*1000);
    #else
    sleep(t);
    #endif
```
And, add the following lines to aklib.h:
```
#ifdef _WIN32
#include <Windows.h> //for the Sleep() function in Windows
#else
#include <unistd.h> // for the sleep() function in Unix
#endif
```
