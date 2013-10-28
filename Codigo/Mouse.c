#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>

#define LMB 0x01
#define RMB 0x02

//Define altura e largura da tela
int larguraTela = 800;
int alturaTela = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
ALLEGRO_BITMAP *botaoIntro = NULL;

//Protótipos
void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);                  //Função de fade in, espera e fade out
void intro();                                                                       //Chamada simplificada de fadeInOut
bool checkSair(ALLEGRO_EVENT *evento);                                              //Verifica se o ícone de fechar programa foi acionado
bool checkBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento);    //Verifica se o mouse está sobre o botão
bool clickBotao(ALLEGRO_BITMAP *botao, float x, float y, ALLEGRO_EVENT *evento);    //Verifica se o botão foi clicado
bool init();                                                                        //Inicia os componentes
void finish();                                                                      //Limpa os componentes

int main(){

    if(init() == false){        //Caso algum componente nõo tenha sido carregado corretamente, 
        printf("Erro\n");       //exibe mensagem de erro e fecha o prorama.
        return -1;
    }

    ALLEGRO_EVENT evento;       //Cria um evento

    //Codigo
    while(!clickBotao(botaoIntro, larguraTela/2, alturaTela/2, &evento)){       //Enquanto o botão não for clicado
        if(checkSair(&evento))                                                  //Caso o ícone para fechar programa tenha sido clicado
            return 0;

        al_clear_to_color(al_map_rgb(0, 0, 0));                                 //Limpa a tela

        if(checkBotao(botaoIntro, larguraTela/2, alturaTela/2, &evento))        //Caso o mouse esteja em cima do botão
            al_draw_tinted_bitmap(botaoIntro, al_map_rgba(128, 128, 128, 0), larguraTela/3, alturaTela/3, 0);   //Draw com mask

        else
            al_draw_bitmap(botaoIntro, larguraTela/3, alturaTela/3, 0);         //Draw padrão

        al_flip_display();                                                      //Atualiza a tela
    }

    intro();

    finish();

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

    background = al_load_bitmap("Imagem/the game.png");                             //Carrega background (perdi)
    if(!background){                                                                //Se o background não for carregado
        fprintf(stderr, "Bitmap nao foi criado.\n");
        return false;
    }

    botaoIntro = al_load_bitmap("Imagem/botao.png");                                //Carrega bitmap do botão
    if(!botaoIntro){                                                                //Botão não carregado
        fprintf(stderr, "Botao nao foi criado.\n");
        return false;
    }

    filaEventos = al_create_event_queue();                                          //Cria fila de eventos
    if(!filaEventos){                                                               //Fila não criada
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_display(janela);
        return false;
    }

    return true;                                                                    //Tudo em ordem
}

void finish(){                          //Desaloca a memória
    al_destroy_bitmap(background);
    al_destroy_bitmap(botaoIntro);
    al_destroy_display(janela);
    al_destroy_event_queue(filaEventos);
}

void intro(){                       //Chamada simplificada de fadeInOut
    fadeInOut(background, 8, 2);        //Fade in e fade out +- 0.5 seg cada + 2 segs em al_rest
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
