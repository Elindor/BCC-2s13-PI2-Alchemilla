#include "struct.h"


int out1, out2; char out1name, out2name; //Variaveis globais, os numeros pra saida da tela de elementos.
int fase; //Variavel global, a fase do jogo.
char checklist[12], startlist[12], itemlist[12], infolist[11]; //Nomes dos arquivos que serão usados
int target; char targetname[30]; //Objetivo da fase
int tabreagentes[2][10];        //reagentes ativos







void filenamesgen(){
    sprintf (checklist, "check%02d.txt", fase); //
    sprintf (startlist, "start%02d.txt", fase); // Isto gera os nomes dos 4 arquivos necessários para as leituras de cada função.
    sprintf (itemlist, "stage%02d.txt", fase); //
    sprintf(infolist, "stage%02d.txt", fase)
}



void insert(int num, lista *menu){
    lista *p, *q;
    p = menu;
    q = menu -> prox;
    while(q != NULL){
        if(q -> ElNum == num)
            return;
        p = q;
        q = q -> prox;
    }
    lista *nova;
    nova = malloc(sizeof (lista));
    
    FILE *file;
    int x;
    file = fopen(itemlist, "r");
    do{
        fscanf(file, "%d", &x); // procura traços / saidas.
        if(x == -1){
            fscanf(file, "%d", &x); //verifica primeiro numero -> checa com valor num.
            if(x == num){
                nova -> ElNum = num;
                while(confere != '\0'){
                    fgets(nova -> ElName, 30, file);
                    //fscanf(file, "%s", nova -> ElName);
                    
                }
                fscanf(file, "%d", &nova -> ElType);
                
                nova -> prox = NULL;
                fclose(file);
                return;
            }
        }
    }while(x != -2);
    fclose(file);
    return ;
}


void start_menu(lista *menu){
    FILE *file;
    int x;
    file = fopen("start00.txt", "r");
    
    fscanf(file, "%d", &x);
    while(x != -1){
        insert(x, menu);
        fscanf(file, "%d", &x);
    }
    fscanf(file, "%d", &target); //pega numero do objetivo p/ global
    fgets(targetname, 30, file);
    //fscanf(file, "%s", targetname); //pega nome do objetivo p/ global
    
    fscanf(file, "%d", &x); // Só pra tirar o próximo -1
    
    fscanf(file, "%d", &x);
    while(x != -1){
        printf("registra %d\n\n", x);
        fscanf(file, "%d", &x);
    }
    printf("EXIT");
    
    fclose(file);
    
    return ;
}


char * nomeia(int num){
FILE *info;
    int aux; //Usado em ordenação e conferir entradas
    char confere[1]; // Usado nos do/while e conferir reagente
    char nome[30];
    confere[0] = NULL;

    file = fopen(checklist, "r");

    do{
        fscanf(info, "%d", &aux);
        if(aux == num){
            fgets(nome, 30, info);
            fclose(info)
            return nome;
        }

        do{
            fgets(confere, 1, info)
        }while(confere[1] != '-' && confere[1] != '!')
    }while(confere[1] != '!');

    fclose(info);
    return NULL;
}

int checagem(int in1, int in2, int reag){
    FILE *file;
    int aux; //Usado em ordenação e conferir entradas
    
    
    if(in1 > in2){
        aux = in1;
        in1 = in2;
        in2 = aux;
    }
    
    file = fopen(checklist, "r");
    
    do{
        fscanf(file, "%d", &aux);
        if(aux == in1){
            fscanf(file, "%d", &aux);
            if(aux == in2){
                fscanf(file, "%d", &aux);
                if(aux == reag){
                    
                    fscanf(file, "%d", &aux);
                    if(aux != 0){
                        out1 = aux;
                    }
                    
                    fscanf(file, "%d", &aux);
                    if(aux != 0){
                        out2 = aux;
                    }
                    
                    fscanf(file, "%d", &aux);
                    if(aux != 0){
                        insert(aux);
                        
                    }
                    
                    fclose(file);
                    return 1; // Se retornar um, faz checagem na lista INFO pelo nome dos elementos.
                    
                }
            }
        }
        
        do{
            fscanf(file, "%d", &x);
        }while(x < 0);
        
    }while(x != -2);
    fclose(file);
    return 0;
}

lista inicializa_lista(){
    
    lista *l = malloc(sizeof(lista));
    l -> prox = NULL;
    return *l;
}

