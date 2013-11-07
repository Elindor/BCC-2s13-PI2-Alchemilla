#ifndef Whiskas_Sache   /* Proteção */
#define Whiskas_Sache

#include "struct.h"

void filenamesgen();
void insert(int num, lista *menu);
void start_menu(lista *menu);
void nomeia(int num, int casa);
int checagem(int in1, int in2, int reag, lista *menu);
lista inicializa_lista();
void nomeia_reag(int reagente, int i);
void info_elem(int elem);
void info_reag(int reagente);
void useElement(int elem, lista *menu);

extern int out1, out2, fase, in1, in2, inreag, target, reagentes[10]; 
extern char out1name, out2name, checklist[12], startlist[12], itemlist[12], infolist[11], targetname[30], reagname[30][10], infoname[30], infosymbol[30], infotext[500], in1name, in2name, inreagname, confere;

#endif
