CC=gcc
CFLAGS=-W -Wall
EXEC = Alchemilla
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS =-lallegro_primitives

PI2_temp: $(OBJ)
# $@= PI2_temp
# $^=main.o
	$(CC) -o $@ $^
  
# main.o: main.c
%.o: %.c
  $(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
  rm -rf *.o
