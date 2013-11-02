#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
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
ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
ALLEGRO_BITMAP *botao1 = NULL;
ALLEGRO_BITMAP *botao2 = NULL;
ALLEGRO_BITMAP *botao3 = NULL;
ALLEGRO_BITMAP *botao4 = NULL;
ALLEGRO_BITMAP *mainMenu = NULL;
ALLEGRO_BITMAP *selectMenu = NULL;

//Protótipos
void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);                  //Função de fade in, espera e fade out
int intro();                                                                       //Chamada simplificada de fadeInOut
bool checkSair(ALLEGRO_EVENT *evento);                                              //Verifica se o ícone de fechar programa foi acionado
bool checkBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento);    //Verifica se o mouse está sobre o botão
bool clickBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento);    //Verifica se o botão foi clicado
bool init();                                                                        //Inicia os componentes
bool introInit();
void finish();                                                                      //Limpa os componentes
void introFinish();

int main(){

    if(init() == false){        //Caso algum componente nõo tenha sido carregado corretamente, 
        printf("Erro\n");       //exibe mensagem de erro e fecha o prorama.
        return -1;
    }

    ALLEGRO_EVENT evento;       //Cria um evento

    //Codigo
    bool eventoTrue = false;

    while(!eventoTrue){       //Enquanto o botão não for clicado
        if(checkSair(&evento))                                                  //Caso o ícone para fechar programa tenha sido clicado
            return 0;

        al_clear_to_color(al_map_rgb(0, 0, 0));                                 //Limpa a tela
        al_draw_bitmap(mainMenu, 0, 0, 0);

        if(clickBotao(botao1, 824.5, 126, &evento)){
            //Ir p/MenuB
        }

        else if(clickBotao(botao2, 825, 215, &evento)){
            intro();
        }

        else if(clickBotao(botao3, 825, 305, &evento)){
            intro();
            finish();
            return 0;
        }

        else if(clickBotao(botao4, 824.5, 393, &evento)){
            finish();
            return 0;
        }

        //Checagens de maouse sobre botão
        if(checkBotao(botao1, 774.5, 76, &evento))        //Caso o mouse esteja em cima do botão
            al_draw_tinted_bitmap(botao1, al_map_rgba(128, 128, 128, 0), 774.5, 76, 0);   //Draw com mask

        else
            al_draw_bitmap(botao1, 774.5, 76, 0);         //Draw padrão

        if(checkBotao(botao2, 775, 165, &evento))        //Caso o mouse esteja em cima do botão
            al_draw_tinted_bitmap(botao2, al_map_rgba(128, 128, 128, 0), 775, 165, 0);   //Draw com mask

        else
            al_draw_bitmap(botao2, 775, 165, 0);         //Draw padrão

        if(checkBotao(botao3, 775, 255, &evento))        //Caso o mouse esteja em cima do botão
            al_draw_tinted_bitmap(botao3, al_map_rgba(128, 128, 128, 0), 775, 255, 0);   //Draw com mask

        else
            al_draw_bitmap(botao3, 775, 255, 0);         //Draw padrão

        if(checkBotao(botao4, 774.5, 343, &evento))        //Caso o mouse esteja em cima do botão
            al_draw_tinted_bitmap(botao4, al_map_rgba(128, 128, 128, 0), 774.5, 343, 0);   //Draw com mask

        else
            al_draw_bitmap(botao4, 774.5, 343, 0);         //Draw padrão

        al_flip_display();                                                      //Atualiza a tela
    }

    return 0;
}

bool init(){                                                                        //Inicia os componentes
    if(!al_init()){                                                                 //Se o allegro5 não for iniciado
        fprintf(stderr, "Allegro nao foi carregado.\n");
        return false;
    }

    if(!al_init_image_addon()){                                                     //Se o allegro_image não for iniciado
        fprintf(stderr, "Allegro image nao foi carregado.\n");
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

    filaEventos = al_create_event_queue();                                          //Cria fila de eventos
    if(!filaEventos){                                                               //Fila não criada
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_display(janela);
        return false;
    }

    mainMenu = al_load_bitmap("Imagem/MenuA.png");
    if(!mainMenu){
        fprintf(stderr, "MenuA nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    selectMenu = al_load_bitmap("Imagem/MenuB.png");
    if(!mainMenu){
        fprintf(stderr, "MenuB nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    botao1 = al_load_bitmap("Imagem/botao.png");                                //Carrega bitmap do botão
    if(!botao1){                                                                //Botão não carregado
        fprintf(stderr, "Botao nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    botao2 = al_load_bitmap("Imagem/botao.png");                                //Carrega bitmap do botão
    if(!botao2){                                                                //Botão não carregado
        fprintf(stderr, "Botao nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    botao3 = al_load_bitmap("Imagem/botao.png");                                //Carrega bitmap do botão
    if(!botao3){                                                                //Botão não carregado
        fprintf(stderr, "Botao nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    botao4 = al_load_bitmap("Imagem/botao.png");                                //Carrega bitmap do botão
    if(!botao4){                                                                //Botão não carregado
        fprintf(stderr, "Botao nao foi criado.\n");
        al_destroy_display(janela);
        return false;
    }

    return true;                                                                    //Tudo em ordem
}

void finish(){                          //Desaloca a memória
    al_destroy_bitmap(botao1);
    al_destroy_bitmap(botao2);
    al_destroy_bitmap(botao3);
    al_destroy_bitmap(botao4);
    al_destroy_bitmap(mainMenu);
    al_destroy_bitmap(selectMenu);
    al_destroy_display(janela);
    al_destroy_event_queue(filaEventos);
}

int intro(){                       //Chamada simplificada de fadeInOut
    if(!introInit()){
        printf("Erro.\n");
        return -1;
    }

    fadeInOut(introImg, 8, 2);        //Fade in e fade out +- 0.5 seg cada + 2 segs em al_rest

    introFinish();
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

bool checkSair(ALLEGRO_EVENT *evento){                                      //Verifica se o ícone de fechar programa foi acionado
    al_register_event_source(filaEventos, al_get_display_event_source(janela)); //Registra a fonte do evento (janela)

    al_wait_for_event_timed(filaEventos, evento, 0.05);                         //Espera 0.05 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_DISPLAY_CLOSE){                            //Se o tipo do evento for fechar a janela
        finish();
        return true;
    }

    return false;
}

bool checkBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento){    //Verifica se o mouse está sobre o botão
    al_register_event_source(filaEventos, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)

    al_wait_for_event_timed(filaEventos, evento, 0.001);                                //Espera 0.001 até que algum evento apareça

    if(evento->mouse.x >= x - al_get_bitmap_width(botao)/2 &&                           //Calcula a "hitbox" do bitmap
    evento->mouse.x <= x + al_get_bitmap_width(botao)/2 &&                              //Draw bitmap tem como referencia o pixel esquerdo superior,
    evento->mouse.y >= y - al_get_bitmap_height(botao)/2 &&                             //mas para comparar área, usa-se o pixel central
    evento->mouse.y <= y + al_get_bitmap_height(botao)/2){
        return true;
    }

    return false;                                                       //Caso o mouse não esteja nessa "hitbox"
}

bool clickBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento){    //Verifica se o botão foi clicado
    al_register_event_source(filaEventos, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)
    
    al_wait_for_event_timed(filaEventos, evento, 0.001);                                //Espera 0.001 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && evento->mouse.button == LMB){   //Além de calcular a hitbox, verifica o evento foi um clique
        if(evento->mouse.x >= x - al_get_bitmap_width(botao)/2 &&                       //E se foi com o botão esquerdo do mouse
        evento->mouse.x <= x + al_get_bitmap_width(botao)/2 &&
        evento->mouse.y >= y - al_get_bitmap_height(botao)/2 &&
        evento->mouse.y <= y + al_get_bitmap_height(botao)/2){
            return true;
        }
    }

    return false;
}

bool introInit(){
    introImg = al_load_bitmap("Imagem/the game.png");                             //Carrega introImg (perdi)
    if(!introImg){                                                                //Se o introImg não for carregado
        fprintf(stderr, "Bitmap nao foi criado.\n");
        return false;
    }

    return true;
}

void introFinish(){
    al_destroy_bitmap(introImg);
}