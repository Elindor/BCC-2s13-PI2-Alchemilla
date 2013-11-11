#ifndef allegroFuncoes
#define allegroFuncoes

int mainMenu();
int gameMenu(int NSNumeroDaFase);
void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);                  //Função de fade in, espera e fade out
bool intro();                                                                       //Chamada simplificada de fadeInOut
bool checkSair(ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);                                              //Verifica se o ícone de fechar programa foi acionado
bool checkBotao(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);    //Verifica se o mouse está sobre o botão
bool clickBotao(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);    //Verifica se o botão foi clicado
bool mainInit();                                                                        //Inicia os componentes
bool introInit();
bool selectInit();
void mainFinish();                                                                      //Limpa os componentes
void introFinish();
void selectFinish();
bool gameInit();
void gameFinish();
int selectMenu();

#endif