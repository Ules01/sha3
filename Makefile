CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wvla -Werror
OBJ=sha3.o keccak.o utils.o main.o
SRC=src/sha3.c src/keccak.c src/utils.c src/main.c
BIN=sha3

all: $(BIN)

$(BIN):$(OBJ)

$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC)
	
debug:CFLAGS += -g
debug:$(BIN)
	

clean:
	$(RM) $(OBJ) $(BIN)
