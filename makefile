CC=gcc -std=c99
CFLAGS=-I$(IDIR) -Wall -g


SRCDIR=src
SRCDIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
ODIR=obj
LIBS=-lallegro -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf -lallegro_primitives -lm

_OBJ = MenuNav.o Mouse.o allegroFuncoes.o gameMenu.o intro.o introV2.o leitura.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

OUTPUTDIR = ../bin


$(ODIR)/%.o: $(SRCDIR)/%.c
        @$(call make_dir)
        $(CC) -c -o $@ $< $(CFLAGS)
        
$(OUTPUTDIR)/ProjetoPI2: $(OBJ) 
        $(CC) -o $@ $^ $(CFLAGS) $(LIBS)
        $(info ************  SUCESS: O Jogo ************)
        
all: $(OUTPUTDIR)/Alchemilla


define make_dir
        @mkdir -p $(ODIR)
        for dir in $(SRCDIRS); \
        do \
                mkdir -p $(ODIR)/$$dir; \
        done
endef

.PHONY: clean
    
clean:
        rm -f $(ODIR)/*.o *~ allegro.log $(SRCDIR)/*~ $(OUTPUTDIR)/*
