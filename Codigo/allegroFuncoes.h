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
int selectMenu();

extern int larguraTela = 1000 ;
extern int alturaTela = 750;

extern ALLEGRO_DISPLAY *janela = NULL;

extern ALLEGRO_BITMAP *introImg = NULL;

extern ALLEGRO_EVENT_QUEUE *mainFila = NULL;
extern ALLEGRO_EVENT_QUEUE *selectFila = NULL;

extern ALLEGRO_BITMAP *menuA = NULL;

extern ALLEGRO_BITMAP *menuB = NULL;

extern ALLEGRO_FONT *fonte = NULL;

extern ALLEGRO_BITMAP *botao = NULL;

extern ALLEGRO_AUDIO_STREAM *bgm = NULL;

extern ALLEGRO_SAMPLE *somNoBotao = NULL;
extern ALLEGRO_SAMPLE *somClickBotao = NULL;

extern ALLEGRO_EVENT evento;

#endif