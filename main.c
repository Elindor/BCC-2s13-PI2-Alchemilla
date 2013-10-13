#include <stdio.h>
#include <stdlib.h>
#include <string.h>














int out1, out2, outb;					//Variaveis globais, os numeros pra saida da tela de elementos.
int fase;						//Variavel global, a fase do jogo.
char checklist[11], startlist[11], itemlist[11];	//Nomes dos arquivos que serão usados



void filenamesgen(){
	sprintf (checklist, "check%d.txt", fase);		//
	sprintf (startlist, "start%d.txt", fase);		// Isto gera os nomes dos 3 arquivos necessários para as leituras de cada função.
	sprintf (itemlist, "stage%d.txt", fase);		//
}




int checagem(int in1, int in2, int reag){
	FILE *file;
	int aux;					//Usado em ordenação e conferir entradas
	char confere;               			// Usado nos do/while e conferir reagente
    
    
	if(in1 > in2){
		aux = in1;
		in1 = in2;
		in2 = aux;
	}
    
	file = fopen(checklist, "r");
    
	do
        fscanf(file, "%c", &confere);		// Vai até o começo da checagem.
	while(confere != ':');
    
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
                        outb = aux;
                        
                    }
		  			
                    fclose(file);
                    return 1;
                    
				}
			}
		}
        
		do{
			fscanf(file, "%c", &confere);
		}while(confere != '-' || confere != '!');
		
	}while(confere != '!');
    fclose(file);
    return 0;
} 
