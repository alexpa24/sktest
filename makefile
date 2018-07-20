CC=gcc
CFLAGS=-lcurl -I.
DEPS = sklib.h
OBJ = sktest.o sklib.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sktest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)