#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
//#include <stdbool.h>

int larguraTela = 800;
int alturaTela = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
ALLEGRO_BITMAP *botaoIntro = 0;

void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);
void intro();
bool checkSair(ALLEGRO_EVENT *evento, ALLEGRO_TIMEOUT *timeout);
bool init();
void finish();

int main(){

    if(init() == false){
        printf("Erro\n");
        return 0;
    }

    //Codigo
    al_register_event_source(filaEventos, al_get_mouse_event_source());

    bool botaoClick = false, noBotao = false;

    while(!botaoClick){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.001);

        al_init_timeout(&timeout, 0.001);
        int checkEvento = al_wait_for_event_until(filaEventos, &evento, &timeout);

        if(checkEvento && evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            if(evento.mouse.x >= larguraTela/2 - al_get_bitmap_width(botaoIntro)/2 &&
            evento.mouse.x <= larguraTela/2 + al_get_bitmap_width(botaoIntro)/2 &&
            evento.mouse.y >= alturaTela/2 - al_get_bitmap_height(botaoIntro)/2 &&
            evento.mouse.y <= alturaTela/2 + al_get_bitmap_height(botaoIntro)/2)
                noBotao = true;

            else
                noBotao = false;
        }

        else if(checkEvento && evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(evento.mouse.x >= larguraTela/2 - al_get_bitmap_width(botaoIntro)/2 &&
            evento.mouse.x <= larguraTela/2 + al_get_bitmap_width(botaoIntro)/2 &&
            evento.mouse.y >= alturaTela/2 - al_get_bitmap_height(botaoIntro)/2 &&
            evento.mouse.y <= alturaTela/2 + al_get_bitmap_height(botaoIntro)/2){
                botaoClick = true;
            }
        }

        if(checkSair(&evento, &timeout))
            return 0;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_set_target_bitmap(al_get_backbuffer(janela));

        if(noBotao == true)
            al_draw_tinted_bitmap(botaoIntro, al_map_rgba(128, 128, 128, 0), larguraTela/3, alturaTela/3, 0);

        else
            al_draw_bitmap(botaoIntro, larguraTela/3, alturaTela/3, 0);

        al_flip_display();
    }

    intro();

    finish();

    return 0;
}

bool init(){
    if(!al_init()){
        fprintf(stderr, "Allegro nao foi carregado.\n");
        return false;
    }

    if(!al_init_image_addon()){
        fprintf(stderr, "Allegro image nao foi carregado.\n");
        return false;
    }

    janela = al_create_display(larguraTela, alturaTela);
    if(!janela){
        fprintf(stderr, "Janela nao foi criada.\n");
        return false;
    }

    al_set_window_title(janela, "Teste mouse+intro");

    if(!al_install_mouse()){
        fprintf(stderr, "Falha ao instalar o mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    if(!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro ao mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    background = al_load_bitmap("Imagem/the game.png");
    if(!background){
        fprintf(stderr, "Bitmap nao foi criado.\n");
        return false;
    }

    botaoIntro = al_load_bitmap("Imagem/botao.png");
    if(!botaoIntro){
        fprintf(stderr, "Botao nao foi criado.\n");
        return false;
    }

    filaEventos = al_create_event_queue();
    if(!filaEventos){
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_display(janela);
        return false;
    }

    return true;
}

void finish(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(botaoIntro);
    al_destroy_display(janela);
    al_destroy_event_queue(filaEventos);
}

void intro(){
    fadeInOut(background, 8, 1);        //Fade in e fade out +- 0.5 seg cada + 1 seg em al_rest
}

void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime){
    int alpha;

    for(alpha = 0; alpha <= 255; alpha += velocidade){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        //Cria uma imagem com mask
        al_draw_tinted_bitmap(img, al_map_rgba(alpha, alpha, alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }

    al_rest(restTime);
    al_rest(restTime);

    for(alpha = 0; alpha<= 255; alpha += velocidade){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(img, al_map_rgba(255-alpha, 255-alpha, 255-alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }
}

bool checkSair(ALLEGRO_EVENT *evento, ALLEGRO_TIMEOUT *timeout){

    al_register_event_source(filaEventos, al_get_display_event_source(janela));

    int checkEvento = al_wait_for_event_until(filaEventos, evento, timeout);

    if(checkEvento && evento->type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        finish();
        return true;
    }

    return false;
}