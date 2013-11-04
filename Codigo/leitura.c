#include "struct.h"


int in1, in2, inreag, out1, out2; char out1name, out2name, in1name, in2name, inreagname; //Variaveis globais, os numeros pra saida da tela de elementos.
int fase; //Variavel global, a fase do jogo.
char checklist[12], startlist[12], itemlist[12], infolist[11]; //Nomes dos arquivos que serão usados
int target; char targetname[30]; //Objetivo da fase
int reagentes[10];        //reagentes ativos
char reagname[30][10];    //e seus nomes
char infoname[30], infosymbol[30], infotext[500];    // Para janela de informações






void filenamesgen(){
    sprintf (checklist, "check%02d.txt", fase); //
    sprintf (startlist, "start%02d.txt", fase); // Isto gera os nomes dos 4 arquivos necessários para as leituras de cada função.
    sprintf (itemlist, "stage%02d.txt", fase); //
    sprintf(infolist, "info%02d.txt", fase);
}

void useElement(int elem, lista *menu){         //
    if(in2 != 0)                                //  Esta fuinção é responsável por ler um struct(clicado) e adicioná-lo
        return;                                 // nos espaços de entrada da reação. Ele recebe o numero clicado da lista
                                                // (por ordem), procura até chegar na informação do struct, e então coloca
    for(int i = 1; i < elem; i++){              // adequadamente no espaço correto.
        if(menu -> prox = NULL)                 //
            return;
        menu = menu -> prox;
    }

    if(in1 == 0){
        in1 = menu -> Elnum;
        in1name = menu -> ElName;
    }
    else{
        in2 = menu -> Elnum;
        in2name = menu -> ElName;
    }
}



void insert(int num, lista *menu){              //
    lista *p, *q;                               //  Esta função é responsável por inserir elementos na lista dinamica
    p = menu;                                   // de elementos. Ela é ativada ao clicar em um botão de out(int num) e
    q = menu -> prox;                           // insere numa lista dinamica (lista *menu) todas as informações
    while(q != NULL){                           // correspondentes ao numero do elemento.
        if(q -> ElNum == num)                   //
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

void nomeia_reag(int reagente, int i){              //
FILE *reag;                                         //  Esta função é chamada dentro da função start_menu.
int aux; char descarta[30];                         // Ela recebe os reagentes da lista de entrada, e insere-os num
reag = fopen("reaglist", "r");                      // vetor global, e então esta função aqui deverá ler os numeros no
do{                                                 // vetor global e inserir os nomes adequados na interface.
        fscanf(info, "%d", &aux);                   // Os nomes são inseridos na matriz reagname[10][30].
        if(aux == reagente){                        //
            fgets(reagname[i], 30, info);
            fclose(reag);
            return void;
        }

        
        fgets(confere, 30, info);
        fgets(confere, 30, info);
    }while(aux != 0);
    fcloe(reag);
    return ;
}



void info_reag(int reagente){                       //
FILE *reag;                                         //  Esta função é ativada com o clique direito sobre um reagente.
int aux; char descarta[30];                         // Ela coloca as informações do elemento correspondente no vetor
reag = fopen("reaglist", "r");                      // de reagentes, e coloca-os nos vetores de informação antes da
do{                                                 // janela de informações mostrá-los.
        fscanf(info, "%d", &aux);                   //
        if(aux == reagente){
            fgets(infoname, 30, info);
            fgets(infosymbol, 30, info);
            fgets(infotext, 30, info);
            fclose(reag);
            return void;
        }

        
        fgets(confere, 30, info);
        fgets(confere, 30, info);
        fgets(confere, 30, info);
    }while(aux != 0);
    fcloe(reag);
    return ;
}

void start_menu(lista *menu){                       //
    FILE *file;                                     //  Esta função deve ser chamada no inicio da fase. Ela lÊ os
    int x;                                          // parametros iniciais e os insere no menu, em seguida lê o objetivo
    file = fopen(startlist, "r");                   // da fase e também o inicializa, e por fim faz o mesmo nos
                                                    // reagentes, já os nomeando pela função nomeia_reag.
    fscanf(file, "%d", &x);                         //
    while(x != -1){
        insert(x, menu);
        fscanf(file, "%d", &x);
    }
    fscanf(file, "%d", &target); //pega numero do objetivo p/ global
    fgets(targetname, 30, file);
    //fscanf(file, "%s", targetname); //pega nome do objetivo p/ global
    
    fscanf(file, "%d", &x); // Só pra tirar o próximo -1
    for(int i; i < 10; i++){
        reagentes[i] = 0;
        reagname[i][30] = NULL
    }
    i = 0;
    fscanf(file, "%d", &x);
    while(x != -1){
        reagentes[i] = x;
        nomeia_reag(x, i);
        i++;
        fscanf(file, "%d", &x);
    }
    printf("EXIT");
    
    fclose(file);
    
    return ;
}


char * nomeia(int num){                                             //
FILE *info;                                                         //  Esta função recebe o numero de um elemento criado
    int aux; //Usado em ordenação e conferir entradas               // e devolve o nome. É feita para incializar após a
    char confere[1]; // Usado nos do/while e conferir reagente      // criação de elementos novos, para então nomeá-los
    char nome[30];                                                  // na interface. (out1name/out2name recebem o resultado)
    confere[0] = NULL;                                              //

    file = fopen(checklist, "r");

    do{
        fscanf(info, "%d", &aux);
        if(aux == num){
            fgets(nome, 30, info);
            fclose(info);
            return nome;
        }

        do{
            fgets(confere, 1, info);
        }while(confere[1] != '-' && confere[1] != '!');
    }while(confere[1] != '!');

    fclose(info);
    return NULL;
}

void info_elem(int elem){                   //
FILE *reag;                                 //  Esta função é ativada ao clicar com o direito em um elemento.
int aux; char descarta[30];                 // Ela buscará todas as informações correspondente ao numero (int elem) que
reag = fopen(infolist, "r");                // ela recebe, e dará o nome, simbolo e descrição antes da janela de
do{                                         // informações carregar.
        fscanf(info, "%d", &aux);           //
        if(aux == elem){
            fgets(infoname, 30, info);
            fgets(infosymbol, 30, info);
            fgets(infotext, 30, info);
            fclose(reag);
            return void;
        }

        
        fgets(confere, 30, info);
        fgets(confere, 30, info);
        fgets(confere, 30, info);
    }while(aux != 0);
    fcloe(reag);
    return ;
}

int checagem(int in1, int in2, int reag){                       //
    FILE *file;                                                 //  Esta função é executada toda a vez em que os espaços
    int aux; //Usado em ordenação e conferir entradas           // para elementos são preenchidos. Ela ordena os elementos
                                                                // e procura por resultados da combinação inserida.
                                                                //  A função devolve sucesso ou falha
    if(in1 > in2){                                              //
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

lista inicializa_lista(){                                   //
                                                            //  Esta função inicializa a lista dinamica de elementos
    lista *l = malloc(sizeof(lista));                       // e deve ser chamada no inicio do jogo (ou fase?)
    l -> prox = NULL;                                       //
    return *l;
}
