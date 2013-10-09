











int out1, out2;		//Variaveis globais, os numeros pra saida da tela de elementos.
int fase;			//Variavel global, a fase do jogo.


int checagem(int in1, int in2, int reag){
	FILE * checklist;
	int aux;					//Usado em ordenação e conferir entradas
	char confere;				// Usado nos do/while e conferir reagente
	char reagente = (char)reag;
	char x1 = (char)fase / 10;
	char x2 = (char)fase % 10;
	char archive[11];
	strcpy (archive,"check");
	strcpy (archive, x1);
	strcpy (archive, x2);
	strcpy (archive,".txt");


	if(ent1 < ent2){
		aux = ent1;
		ent1 = ent2;
		ent2 = aux;
	}

	checklist = fopen("archive", "r");

	do
	fscanf(checklist, %c, confere);		// Vai até o começo da checagem.
	while(confere != ":");

	do{
		fscanf(checklist, %d, aux);
		if(aux == in1){
			fscanf(checklist, %d, aux);
			if(aux == in2){
				fscanf(checklist, %c, confere);
				if(confere == reagente){

					/*
					*
					*			Parte de inserção na interface.
					*   <<----+ Ultimas checagens e saidas.
					*			Cada if separado individualmente.
					*
					*/


				}
			}
		}
	
		do{
			fscanf(checklist, %c, confere);
		}while(confere != "-" || confere != "!");
		
	}while(confere != "!");

return 0;
} 
