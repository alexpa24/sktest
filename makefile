CC=gcc
CFLAGS=-I.
CFLAGS2=-lcurl -I.
DEPS = sklib.h
OBJ = sktest.o sklib.o 
binaries=sklib sktest

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sktest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS2)

.PHONY: clean

clean:
	rm -f $(binaries) *.o