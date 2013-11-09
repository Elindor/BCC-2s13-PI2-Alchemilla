CC=gcc -std=c99
CFLAGS=-W -Wall
EXEC = Alchemilla
SRC= $(wildcard *.c) $(wildcard *.h) $(wildcard *.txt) $(wildcard *.png)
OBJ= $(SRC:.c=.o)
LIBS =-lallegro_primitives -lallegro_audio -lallegro -lallegro_image -lallegro_font -lallegro_ttf
all: $(EXEC)

$(EXEC): $(OBJ)
# $@= PI2_temp
# $^=main.o
	$(CC) -o $@ $^ $(LIBS)
  
# main.o: main.c
%.o: %.c
  $(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
  rm -rf *.o
