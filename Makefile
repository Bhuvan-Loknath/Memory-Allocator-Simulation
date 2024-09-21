CC = gcc
CFLAGS = -Wall
TARGET = allocator
SRCS = allocator.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
