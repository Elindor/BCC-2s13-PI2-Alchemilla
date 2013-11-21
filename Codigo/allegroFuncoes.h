#ifndef allegroFuncoes
#define allegroFuncoes
bool mainInit();                                                                        //Inicia os componentes
int mainMenu();
void mainFinish();                                                                      //Limpa os componentes

bool introInit();
void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);                  //Função de fade in, espera e fade out
bool intro();                                                                       //Chamada simplificada de fadeInOut
void introFinish();

bool checkSair(ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);                                              //Verifica se o ícone de fechar programa foi acionado
bool checkBotao(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);    //Verifica se o mouse está sobre o botão
bool clickBotaoL(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);    //Verifica se o botão foi clicado
bool clickBotaoR(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila);    //Verifica se o botão foi clicado

void playSample(ALLEGRO_SAMPLE *sample);

bool selectInit();
int selectMenu();
void selectFinish();

bool infoInit();
int infoMenu();
void infoFinish();

bool gameInit();
int gameMenu(int NSNumeroDaFase);
void gameFinish();

extern ALLEGRO_SAMPLE *somClickBotao;
#endif