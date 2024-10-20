CC=gcc
CFLAGS=-Wall -g -fsanitize=address
TARGET=myapp
OBJS=cs457_crypto.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

lib.o: cs457_crypto.c cs457_crypto.h
	$(CC) $(CFLAGS) -c lib.c

main.o: main.c cs457_crypto.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET) $(OBJS)
