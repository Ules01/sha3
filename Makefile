
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wvla -Werror


SRCS = src/utils.c src/keccak.c src/sha3.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = sha3


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

