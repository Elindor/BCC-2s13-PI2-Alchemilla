#include "header.h"


int in1, in2, inreag, out1, out2; char out1name[30], out2name[30], in1name[30], in2name[30], inreagname[30]; //Variaveis globais, os numeros pra saida da tela de elementos.
int fase; //Variavel global, a fase do jogo.
char checklist[21], startlist[21], itemlist[21], infolist[20]; //Nomes dos arquivos que serão usados
int target; char targetname[30]; //Objetivo da fase
int reagentes[10];        //reagentes ativos
char reagname[30][10];    //e seus nomes
char infoname[30], infosymbol[30], infotext[500];    // Para janela de informações
char confere[30];

void filenamesgen(){
    sprintf (checklist, "Entradas/check%02d.txt", fase); //
    sprintf (startlist, "Entradas/start%02d.txt", fase); // Isto gera os nomes dos 4 arquivos necessários para as leituras de cada função.
    sprintf (itemlist, "Entradas/stage%02d.txt", fase); //
    sprintf(infolist, "Entradas/info%02d.txt", fase);
}

int fgetline(FILE *fp, char s[], int lim)
{
char *t;
int c, len=lim;
 
t = s;
while (--lim>1 && (c=getc(fp)) != EOF && c != '\n')
{
*s++ = c;
if (c == '\n')
*s++ = c;
else if (lim == 1)
{
*s++ = '\n';
fprintf(stderr, "WARNING. fgetline: Line too long, splitted.\n");
}
}
*s = '\0';
return s - t;
}

void useElement(int elem, lista *menu){         //
    if(in2 != 0)                                //  Esta fuinção é responsável por ler um struct(clicado) e adicioná-lo
        return;                                 // nos espaços de entrada da reação. Ele recebe o numero clicado da lista
                                                // (por ordem), procura até chegar na informação do struct, e então coloca
    for(int i = 1; i < elem; i++){              // adequadamente no espaço correto.
        if(menu -> prox == NULL)                 //
            return;
        menu = menu -> prox;
    }

    if(in1 == 0){
        in1 = menu -> ElNum;
		strcpy(in1name, menu->ElName);
    }
    else{
        in2 = menu -> ElNum;
        strcpy(in1name, menu->ElName);
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
    printf("0.1\n");
    printf("Num: %d\n", num);
    lista *nova = (lista *)malloc(sizeof(lista));
    p -> prox = nova;
    printf("0.2\n");

    FILE *file;
    int x;
    char c, buff[30];

    file = fopen(itemlist, "r");
    if(!file){
        fprintf(stderr, "Erro ao abrir itemlist.\n");
        return;
    } 
    printf("0.3\n");
    int a, b, y;
    //PROBLEMA!!!
    fgetline(file, buff, 20);
    printf("y = %s\r\n", buff);
    y = atoi(buff);
    do{      
        fgetline(file, buff, 20);
        printf("x = %s\r\n", buff);
        x = atoi(buff);

        if(x == -1){
            fgetline(file, buff, 20);
            printf("x/num = %s\r\n", buff);
            x = atoi(buff);

            if(x == num){
                printf("0.3.2\n");
                nova -> ElNum = num;
                char temp[30]; int tempo;

                fgetline(file, buff, 20);
                printf("Name = %s\r\n", buff);
                strcpy(nova->ElName, buff);
                printf("0.3.3\n");
                fgetline(file, buff, 20);
                printf("x/TYPE = %s\r\n", buff);
                nova->ElType = atoi(buff);

                printf("%d, %s, %d\n", nova->ElNum, nova->ElName, nova->ElType);

                nova -> prox = NULL;
                                printf("0.3.4");
                fclose(file);
                printf("0.3.5");
                return;
            }

            else{
                fgetline(file, buff, 20);fgetline(file, buff, 20);
            }
        }

        printf("0.3.1\n");
    }while(x != -2);

    printf("0.4\n");

    fclose(file);
    return;
}

void nomeia_reag(int reagente, int i){              //
    FILE *reag;                                         //  Esta função é chamada dentro da função start_menu.
    int aux; char confere[30];                         // Ela recebe os reagentes da lista de entrada, e insere-os num

    reag = fopen("Entradas/reaglist.txt", "r");                      // vetor global, e então esta função aqui deverá ler os numeros no
    if(!reag){
        fprintf(stderr, "Erro ao abrir reaglist.\n");
        return;
    }

    do{                                                 // vetor global e inserir os nomes adequados na interface.
        fscanf(reag, "%d", &aux);                   // Os nomes são inseridos na matriz reagname[10][30].
        if(aux == reagente){                        //
            fgets(reagname[i], 30, reag);
            fclose(reag);
            return;
        }

        else
            fgets(confere, 30, reag); 
            
        fgets(confere, 30, reag);
        fgets(confere, 30, reag);
    }while(aux != 0);

    fclose(reag);

    return;
}

void info_reag(int reagente){                           //
    FILE *reag;                                         //  Esta função é ativada com o clique direito sobre um reagente.
    int aux; char kill[30];                                          // Ela coloca as informações do elemento correspondente no vetor

    reag = fopen("Entradas/reaglist.txt", "r");         // de reagentes, e coloca-os nos vetores de informação antes da
    if(!reag){
        fprintf(stderr, "Erro ao abrir reaglist.\n");
        return;
    }

    do{                                                 // janela de informações mostrá-los.
        fscanf(reag, "%d", &aux);                   //
        if(aux == reagente){
            fgets(infoname, 30, reag);
            fgets(infosymbol, 30, reag);
            fgets(infotext, 30, reag);
            fclose(reag);
            return;
        }
            
        fgets(kill, 30, reag);
        fgets(kill, 30, reag);
        fgets(kill, 30, reag);
    }while(aux != 0);

    fclose(reag);

    return;
}

void start_menu(lista *menu){                       //
    FILE *file;                                     //  Esta função deve ser chamada no inicio da fase. Ela lÊ os
    int x, i, y; 
    char c;                                      // parametros iniciais e os insere no menu, em seguida lê o objetivo
    file = fopen(startlist, "r");                   // da fase e também o inicializa, e por fim faz o mesmo nos      
    if(!file){
        fprintf(stderr, "Erro ao abrir starlist.\n");
        return;
    }
    fscanf(file, "%d", &y); // Mata um primeiro valor bugado.
    do{fscanf(file, "%c", &c); }while(c != '\n');  
    printf("y = %d\n", y);

                                                    // reagentes, já os nomeando pela função nomeia_reag.
    fscanf(file, "%d", &x);                         //
    printf("x = %d\n", x);
    x = 1; // porque "sei lá que merda deu aqui"
    while(x != -1){
        insert(x, menu);
        fscanf(file, "%d", &x);
    }
    printf("1\n");

    fscanf(file, "%d", &target); //pega numero do objetivo p/ global
    fgets(targetname, 30, file);
    printf("2\n");
    //fscanf(file, "%s", targetname); //pega nome do objetivo p/ global
    
    fscanf(file, "%d", &x); // Só pra tirar o próximo -1
    for(i = 0; i < 10; i++){
        reagentes[i] = 0;
        reagname[i][30] = NULL;
    }
    printf("3\n");

    i = 0;
    fscanf(file, "%d", &x);

    while(x != -1){
        reagentes[i] = x;
        nomeia_reag(x, i);
        i++;
        fscanf(file, "%d", &x);
    }
    printf("4\n");
    
    fclose(file);
    printf("5\n");
}

void nomeia(int num, int casa){                                             //
    FILE *info;                                                         //  Esta função recebe o numero de um elemento criado
    int aux; //Usado em ordenação e conferir entradas               // e devolve o nome. É feita para incializar após a
    char confere[1]; // Usado nos do/while e conferir reagente      // criação de elementos novos, para então nomeá-los
    char nome[30];                                                  // na interface. (out1name/out2name recebem o resultado)
    confere[0] = NULL;                                              //

    info = fopen(checklist, "r");
    if(!info){
        fprintf(stderr, "Erro ao abrir checklist.\n");
        return;
    }

    do{
        fscanf(info, "%d", &aux);
        if(aux == num){
            fgets(nome, 30, info);
            if(casa == 1)
            	strcpy(out1name, nome);
            else if(casa == 2)
            	strcpy(out2name, nome);
            	
            fclose(info);
            return ;		//retorna var temporaria???
        }

        do{
            fgets(confere, 1, info);
        }while(confere[1] != '-' && confere[1] != '!');
    }while(confere[1] != '!');

    fclose(info);
    return;
}

void info_elem(int elem){                   //
    FILE *reag;                                 //  Esta função é ativada ao clicar com o direito em um elemento.
    int aux;                 // Ela buscará todas as informações correspondente ao numero (int elem) que
    reag = fopen(infolist, "r");                // ela recebe, e dará o nome, simbolo e descrição antes da janela de
    if(!reag){
        fprintf(stderr, "Erro ao abrir infolist.\n");
        return;
    }

    do{                                         // informações carregar.
        fscanf(reag, "%d", &aux);           //
        if(aux == elem){
            fgets(infoname, 30, reag);
            fgets(infosymbol, 30, reag);
            fgets(infotext, 30, reag);
            fclose(reag);
            return;
        }

        
        fgets(confere, 30, reag);
        fgets(confere, 30, reag);
        fgets(confere, 30, reag);
    }while(aux != 0);
    fclose(reag);
    return ;
}

int checagem(int in1, int in2, int reag, lista *menu){                       //
    FILE *file;                                                 //  Esta função é executada toda a vez em que os espaços
    int aux, x; //Usado em ordenação e conferir entradas           // para elementos são preenchidos. Ela ordena os elementos
                                                                // e procura por resultados da combinação inserida.
                                                                //  A função devolve sucesso ou falha
    if(in1 > in2){                                              //
        aux = in1;
        in1 = in2;
        in2 = aux;
    }
    
    file = fopen(checklist, "r");
    if(!file){
        fprintf(stderr, "Erro ao abrir checklist.\n");
        return -1;
    }
    
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
                        nomeia(out1, 1);
                    }
                    
                    fscanf(file, "%d", &aux);
                    if(aux != 0){
                        out2 = aux;
                        nomeia(out2, 2);
                    }
                    
                    fscanf(file, "%d", &aux);
                    if(aux != 0){
                        insert(aux, menu);
                        
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
                                                    //  Esta função inicializa a lista dinamica de elementos
    lista *l = (lista*)malloc(sizeof(lista));       // e deve ser chamada no inicio do jogo (ou fase?)
    l -> prox = NULL;                               //
    return *l;
}

void termina_lista(lista *l){
    free(l->prox->prox->prox->prox->prox->prox->prox->prox->prox);
    free(l->prox->prox->prox->prox->prox->prox->prox->prox);
    free(l->prox->prox->prox->prox->prox->prox->prox);
    free(l->prox->prox->prox->prox->prox->prox);
    free(l->prox->prox->prox->prox->prox);
    free(l->prox->prox->prox->prox);
    free(l->prox->prox->prox);
    free(l->prox->prox);
    free(l->prox);
    free(l);
}
