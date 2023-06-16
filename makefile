###########################################################
# Makefile for CS480 Assignment #1
# Kobi Bell and Mark Duraid
###########################################################

CC = gcc
CFLAGS = -Wall -pthread
SRC = chatbots.c
OBJ = $(SRC:.c=.o)
EXEC = chatbots

all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJ)

#######################[ EOF: Makefile ]###################
