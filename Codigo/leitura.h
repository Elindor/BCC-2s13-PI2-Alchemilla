#ifndef Whiskas_Sache   /* Proteção */
#define Whiskas_Sache


void filenamesgen();
void insert(int num, lista *menu);
void start_menu(lista *menu);
char * nomeia(int num);
int checagem(int in1, int in2, int reag);
lista inicializa_lista();
void nomeia_reag(int reagente, int i);
void info_elem(int elem);
void info_reag(int reagente);

extern int out1, out2, fase, target, reagentes[10]; 
extern char out1name, out2name, checklist[12], startlist[12], itemlist[12], infolist[11], targetname[30], reagname[30][10], infoname[30], infosymbol[30], infotext[500];


#endif
