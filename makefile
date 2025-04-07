# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Sources and output
SRC = test.c serializador.c
OBJ = $(SRC:.c=.o)
EXEC = test

# Default rule
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f *.o $(EXEC)
