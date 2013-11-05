#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "leitura.h"
#include "struct.h"

#include <stdio.h>
//#include <stdbool.h>

//Define endereço p/ botões de mouse
#define LMB 0x01
#define RMB 0x02

//Define altura e largura da tela
int larguraTela = 1000 ;
int alturaTela = 750;

ALLEGRO_DISPLAY *janela = NULL;

ALLEGRO_BITMAP *introImg = NULL;

ALLEGRO_EVENT_QUEUE *mainFila = NULL;
ALLEGRO_EVENT_QUEUE *selectFila = NULL;

ALLEGRO_BITMAP *menuA = NULL;

ALLEGRO_BITMAP *menuB = NULL;

ALLEGRO_FONT *fonte = NULL;

ALLEGRO_BITMAP *botao = NULL;

ALLEGRO_AUDIO_STREAM *bgm = NULL;

ALLEGRO_SAMPLE *somNoBotao = NULL;
ALLEGRO_SAMPLE *somClickBotao = NULL;

ALLEGRO_EVENT evento;

//Protótipos
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

int main(){

    if(mainInit() == false){        //Caso algum componente nõo tenha sido carregado corretamente, 
        printf("Erro\n");       //exibe mensagem de erro e fecha o prorama.
        return -1;
    }

    al_attach_audio_stream_to_mixer(bgm, al_get_default_mixer());
    al_set_audio_stream_playing(bgm, true);

    while(!checkSair(&evento, mainFila)){       //Enquanto o botão não for clicado

        al_clear_to_color(al_map_rgb(0, 0, 0));                                 //Limpa a tela
        al_draw_bitmap(menuA, 0, 0, 0);

        if(clickBotao(740, 909, 98, 154, &evento, mainFila)){
            selectMenu();
        }

        else if(clickBotao(741, 909, 187, 243, &evento, mainFila)){
            intro();
        }

        else if(clickBotao(741, 909, 277, 333, &evento, mainFila)){
            intro();
            mainFinish();
            return 0;
        }

        else if(clickBotao(740, 909, 365, 421, &evento, mainFila)){
            mainFinish();
            return 0;
        }

        //Checagens de maouse sobre botão
        if(checkBotao(740, 909, 98, 154, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 98, ALLEGRO_ALIGN_CENTRE, "Jogar");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 98, ALLEGRO_ALIGN_CENTRE, "Jogar");

        if(checkBotao(741, 909, 187, 243, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825, 187, ALLEGRO_ALIGN_CENTRE, "Intro");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825, 187, ALLEGRO_ALIGN_CENTRE, "Intro");

        if(checkBotao(741, 909, 277, 333, &evento, mainFila))        //Caso o mouse esteja em cima do botão
           al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825, 277, ALLEGRO_ALIGN_CENTRE, "Intro e sair");

        else  
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825, 277, ALLEGRO_ALIGN_CENTRE, "Intro e sair");

        if(checkBotao(740, 909, 365, 421, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 365, ALLEGRO_ALIGN_CENTRE, "Sair");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 365, ALLEGRO_ALIGN_CENTRE, "Sair");

        al_flip_display();                                                      //Atualiza a tela
        al_drop_next_event(mainFila);
    }

    mainFinish();

    return 0;
}

bool mainInit(){                                                                        //Inicia os componentes
    if(!al_init()){                                                                 //Se o allegro5 não for iniciado
        fprintf(stderr, "Allegro nao foi carregado.\n");
        return false;
    }

    if(!al_init_image_addon()){                                                     //Se o allegro_image não for iniciado
        fprintf(stderr, "Allegro image nao foi carregado.\n");
        return false;
    }

    al_init_font_addon();

    if(!al_init_ttf_addon()){
        fprintf(stderr, "Erro ao carregar plugin de ttf\n");
        return false;
    }

    if(!al_install_audio()){
        fprintf(stderr, "Erro ao instalar audio.\n");
        return false;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "Erro ao instalar codec de audio.\n");
        return false;
    }


    if(!al_reserve_samples(1)){
        fprintf(stderr, "Erro ao alocar canais de audio.\n");
        return false;
    }

    janela = al_create_display(larguraTela, alturaTela);                            //Cria a janela
    if(!janela){                                                                    //Se a janela não for criada
        fprintf(stderr, "Janela nao foi criada.\n");
        return false;
    }

    al_set_window_title(janela, "Teste mouse+intro");                               //Cria um título pra janela

    if(!al_install_mouse()){                                                        //Se o mouse não for instalado corretamente
        fprintf(stderr, "Falha ao instalar o mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    if(!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){   //Se o cursor do mouse não for determinado
        fprintf(stderr, "Falha ao atribuir ponteiro ao mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    mainFila = al_create_event_queue();                                          //Cria fila de eventos
    if(!mainFila){                                                               //Fila não criada
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_display(janela);
        return false;
    }

    fonte = al_load_font("Fonte/anirom.ttf", 22, 0);
    if(!fonte){
        fprintf(stderr, "Erro ao carregar fonte\n");
        return false;
    }

    menuA = al_load_bitmap("Imagem/MenuA.png");
    if(!menuA){
        fprintf(stderr, "MenuA nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    bgm = al_load_audio_stream("Audio/bgm.ogg", 4, 1024);
    if(!bgm){
        fprintf(stderr, "Erro ao criar bgm.\n");
        al_destroy_display(janela);
        return false;
    }

    somClickBotao = al_load_sample("Audio/badDisk.wav");
    if(!somClickBotao){
        fprintf(stderr, "Erro ao criar somClickBotao.\n");
        al_destroy_display(janela);
        return false;
    }

    return true;                                                                    //Tudo em ordem
}

void mainFinish(){                          //Desaloca a memória
    al_destroy_bitmap(menuA);
    al_destroy_display(janela);
    al_destroy_event_queue(mainFila);
    al_destroy_font(fonte);
    al_destroy_audio_stream(bgm);
    al_destroy_sample(somNoBotao);
    al_destroy_sample(somClickBotao);
}

bool intro(){                       //Chamada simplificada de fadeInOut
    if(!introInit()){
        printf("Erro.\n");
        return false;
    }

    fadeInOut(introImg, 8, 2);        //Fade in e fade out +- 0.5 seg cada + 2 segs em al_rest

    introFinish();

    return true;
}

void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime){              //Função de fade in, espera e fade out
    int alpha;

    for(alpha = 0; alpha <= 255; alpha += velocidade){                              //Fade in
        al_clear_to_color(al_map_rgb(0, 0, 0));                                         //Limpa a tela para não haver sobrposição dos masks
        al_draw_tinted_bitmap(img, al_map_rgba(alpha, alpha, alpha, alpha), 0, 0, 0);   //Cria uma imagem com mask
        al_flip_display();
        al_rest(0.015);                                                                 //Determinado para rodar a 30fps
    }

    al_rest(restTime);

    for(alpha = 0; alpha<= 255; alpha += velocidade){                               //Fade out
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(img, al_map_rgba(255-alpha, 255-alpha, 255-alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }
}

bool checkSair(ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila){                                      //Verifica se o ícone de fechar programa foi acionado
    al_register_event_source(fila, al_get_display_event_source(janela)); //Registra a fonte do evento (janela)

    al_wait_for_event_timed(fila, evento, 0.05);                         //Espera 0.05 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_DISPLAY_CLOSE){                            //Se o tipo do evento for fechar a janela
        return true;
    }

    return false;
}

bool checkBotao(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila){    //Verifica se o mouse está sobre o botão
    al_register_event_source(fila, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)

    al_wait_for_event_timed(fila, evento, 0.001);                                //Espera 0.001 até que algum evento apareça

    if(evento->mouse.x >= xa &&                                                         //Calcula a "hitbox" do bitmap
    evento->mouse.x <= xb &&                                                            //Draw bitmap tem como referencia o pixel esquerdo superior,
    evento->mouse.y >= ya &&                                                            //mas para comparar área, usa-se o pixel central
    evento->mouse.y <= yb){
        return true;
    }

    return false;                                                       //Caso o mouse não esteja nessa "hitbox"
}

bool clickBotao(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila){    //Verifica se o botão foi clicado
    al_register_event_source(fila, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)
    
    al_wait_for_event_timed(fila, evento, 0.001);                                //Espera 0.001 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && evento->mouse.button == LMB){   //Além de calcular a hitbox, verifica o evento foi um clique
        if(evento->mouse.x >= xa &&                                                     //E se foi com o botão esquerdo do mouse
        evento->mouse.x <= xb &&
        evento->mouse.y >= ya &&
        evento->mouse.y <= yb){
            al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            return true;
        }
    }

    return false;
}

bool introInit(){
    introImg = al_load_bitmap("Imagem/the game.png");                             //Carrega introImg (perdi)
    if(!introImg){                                                                //Se o introImg não for carregado
        fprintf(stderr, "Bitmap nao foi criado.\n");
        mainFinish();
        return false;
    }

    return true;
}

bool selectInit(){
    menuB = al_load_bitmap("Imagem/MenuB.png");
    if(!menuB){
        fprintf(stderr, "MenuB nao foi criado.\n");
        mainFinish();
        return false;
    }

    botao = al_load_bitmap("Imagem/botao.png");
    if(!botao){
        fprintf(stderr, "botao não foi criado.\n");
        al_destroy_bitmap(menuB);
        mainFinish();
        return false;
    }

    selectFila = al_create_event_queue();                                          //Cria fila de eventos
    if(!selectFila){                                                               //Fila não criada
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_bitmap(menuB);
        al_destroy_bitmap(botao);
        mainFinish();
        return false;
    }


    return true;
}

void selectFinish(){
    al_destroy_bitmap(menuB);
    al_destroy_bitmap(botao);
    al_destroy_event_queue(selectFila);
}

void introFinish(){
    al_destroy_bitmap(introImg);
}

int selectMenu(){
    if(!selectInit()){
        printf("Erro.\n");
        mainFinish();
        return -1;
    }

    while(1){
        if(checkSair(&evento, selectFila)){
            break;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(menuB, 0, 0, 0);

        if(checkBotao(742, 911, 114, 170, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 826.5, 114, ALLEGRO_ALIGN_CENTRE, "Fase 1");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 826.5, 114, ALLEGRO_ALIGN_CENTRE, "Fase 1");

        if(checkBotao(741, 910, 204, 260, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825.5, 204, ALLEGRO_ALIGN_CENTRE, "Fase 2");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825.5, 204, ALLEGRO_ALIGN_CENTRE, "Fase 2");

        if(checkBotao(740, 909, 293, 349, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 293, ALLEGRO_ALIGN_CENTRE, "Fase 3");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 293, ALLEGRO_ALIGN_CENTRE, "Fase 3");

        if(checkBotao(739, 908, 382, 438, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 382, ALLEGRO_ALIGN_CENTRE, "Fase 4");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 382, ALLEGRO_ALIGN_CENTRE, "Fase 4");

        if(checkBotao(739, 908, 471, 527, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 471, ALLEGRO_ALIGN_CENTRE, "Fase 5");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 471, ALLEGRO_ALIGN_CENTRE, "Fase 5");

        if(checkBotao(739, 908, 560, 616, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 560, ALLEGRO_ALIGN_CENTRE, "Fase 6");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 560, ALLEGRO_ALIGN_CENTRE, "Fase 6");

        //////////////////////////////////////////

        if(checkBotao(0, 100, 0, 100, &evento, selectFila))
            al_draw_tinted_bitmap(botao, (al_map_rgba(128, 128, 128, 0)), 0, 0, 0);

        else
            al_draw_bitmap(botao, 0, 0, 0);

        if(clickBotao(0, 100, 0, 100, &evento, selectFila)){
            break;
        }

        al_flip_display();
    }

    selectFinish();

    return 0;
}
