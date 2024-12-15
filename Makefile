
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2


SRCS = src/keccak.c src/sha3.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = keccak_test


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

test: all
	./$(TARGET)

