CC=gcc
CFLAGS=-Wall -g 
TARGET=myapp
OBJS=database.o main_database.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

lib.o: database.c database.h
	$(CC) $(CFLAGS) -c lib.c

main_database.o: main_database.c database.h
	$(CC) $(CFLAGS) -c main_database_database.c

clean:
	rm -f $(TARGET) $(OBJS)