#include <stdio.h>
#include <stdlib.h>
#include <string.h>














int out1, out2, outb;		//Variaveis globais, os numeros pra saida da tela de elementos.
int fase;			//Variavel global, a fase do jogo.


int checagem(int in1, int in2, int reag){
	FILE *checklist;
	int aux;					//Usado em ordenação e conferir entradas
	char confere;               // Usado nos do/while e conferir reagente
    int y = fase + 48;
	char x = (char)y;
	char *z = &x;
    //char *z1 = &x1;
    //char *z2 = &x2;
	char archive[11];
	strcpy (archive,"check");
	strcat (archive, z);
	strcat (archive,".txt");
    
    
	if(in1 > in2){
		aux = in1;
		in1 = in2;
		in2 = aux;
	}
    
	checklist = fopen("check00.txt", "r");
    
	do
        fscanf(checklist, "%c", &confere);		// Vai até o começo da checagem.
	while(confere != ':');
    
	do{
		fscanf(checklist, "%d", &aux);
		if(aux == in1){
            fscanf(checklist, "%d", &aux);
			if(aux == in2){
				fscanf(checklist, "%d", &aux);
				if(aux == reag){
                    
					fscanf(checklist, "%d", &aux);
                    if(aux != 0){
                        out1 = aux;
                    }
                    
                    fscanf(checklist, "%d", &aux);
                    if(aux != 0){
                        out2 = aux;
                    }
                    
                    fscanf(checklist, "%d", &aux);
                    if(aux != 0){
                        outb = aux;
                        
                    }
					
                    return 1;
                    
				}
			}
		}
        
		do{
			fscanf(checklist, "%c", &confere);
		}while(confere != '-' || confere != '!');
		
	}while(confere != '!');
    
    return 0;
} 
