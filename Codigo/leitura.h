#ifndef Whiskas_Sache   /* Proteção */
#define Whiskas_Sache

#include "struct.h"

void filenamesgen();
void insert(int num, lista *menu, int type);
void start_menu(lista *menu);
void nomeia(int num, int casa);
int checagem(int in1, int in2, int reag, lista *menu);
lista inicializa_lista();
void termina_lista(lista *l);
void nomeia_reag(int reagente, int i);
void info_elem(int elem);
void info_reag(int reagente);
void useElement(int elem, lista *menu);
int fgetline(FILE *fp, char s[], int lim);

extern int out1, out2, fase, in1, in2, inreag, target, reagentes[10]; 
extern char out1name[30], out2name[30], checklist[21], startlist[21], itemlist[21], infolist[20], targetname[30], reagname[10][30], infoname[30], infosymbol[30], infotext[500], in1name[30], in2name[30], inreagname[30], confere[30], logtext1[40], logtext2[40];

#endif
