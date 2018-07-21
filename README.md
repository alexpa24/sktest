# sktest
sktest is an application to test how good the connectivity to http://www.google.com/ is, using libcurl functions.

# Code style
The code is written in C using POSIX / ISO C standards.

# Installation
First of all, libcurl should be installed. It can be downloaded from: https://curl.haxx.se/download.html
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
One the application is compiled, can be run using:
```
./sktest -n <number of HTTP requests>
```
For example:
```
./sktest -n 3
```

# Tests
