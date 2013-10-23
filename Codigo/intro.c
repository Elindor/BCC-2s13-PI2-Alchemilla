#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
//Se for no VC++, não incluuir #include <stdbool.h>

//fadin e fadeout +-0.5seg cada

int larguraTela = 800;
int alturaTela = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *background = NULL;

void fadeIn(ALLEGRO_BITMAP *img, int velocidade);
void fadeOut(int velocidade);
bool init();

int main(){
    if(!init()){
        return -1;
    }

    fadeIn(background, 8);
    al_rest(2.0);
    fadeOut(8);

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

    background = al_load_bitmap("img.png");
    if(!background){
        fprintf(stderr, "Bitmap nao foi criado.\n");
        return false;
    }

    return true;
}

void fadeIn(ALLEGRO_BITMAP *img, int velocidade){
	int alpha;

    if(velocidade < 0)
        velocidade = 1;

    else if(velocidade > 15)
        velocidade = 15;

    for(alpha = 0; alpha <= 255; alpha += velocidade){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(img, al_map_rgba(alpha, alpha, alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }
}

void fadeOut(int velocidade){
	int alpha;

    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(larguraTela, alturaTela);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(janela), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(janela));

    if(velocidade <= 0)
        velocidade = 1;

    for(alpha = 0; alpha<= 255; alpha += velocidade){
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255-alpha, 255-alpha, 255-alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }
}