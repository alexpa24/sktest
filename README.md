# sktest
sktest is an application to test how good the connectivity to http://www.google.com/ is, using the library sklib.

# Code style
The code is written in C using POSIX / ISO C standards.

# Installation
First of all, libcurl should be installed, because the sklib needs it. It can be downloaded from: https://curl.haxx.se/download.html
Then, it can be installed in a Unix machine using:
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
Use the proposed makefile to build the sktest application in a Unix machine using
```
make sktest
```
Alternatively you can use
```
gcc -o sktest sktest.c sklib.c -lcurl -I.
```

# How to use?
Once the application is compiled, can be run using:
```
./sktest -n <number of HTTP requests> - H <Header-name: Header-value> -t <time between requests>
```

All the arguments are optional. The number of requests is 1 and the time between requests is 0 by default. -H can be used multiple times to add additional header parameters.

For example:
```
./sktest -n 3 -H Connection: keep-alive -t 5
```

# Tests
The parameter time between request has been added in order to space the different HTTP requests and get a better sample for the analysis.

