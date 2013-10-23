#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
//Fora do visual studio, usar #include <stdbool.h>

int larguraTela = 800;
int alturaTela = 600;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *background = NULL;

void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime);
bool introInit();

int main(){
    if(!introInit()){
        return -1;
    }

    fadeInOut(background, 8, 2);        //Fade in e fade out +- 0.5 seg cada + 2 segs em al_rest

    return 0;
}

bool introInit(){
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

void fadeInOut(ALLEGRO_BITMAP *img, int velocidade, int restTime){
    int alpha;

    //alpha = 0 -> sem transparencia, alpha = 255-> transparente
    for(alpha = 0; alpha <= 255; alpha += velocidade){
        al_clear_to_color(al_map_rgb(0, 0, 0));     //Usar isso no fadeIn e no fadeOut para não ter sobrposição de duas imagens.
        //Cria uma imagem com mask
        al_draw_tinted_bitmap(img, al_map_rgba(alpha, alpha, alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }

    al_rest(restTime);

    for(alpha = 0; alpha<= 255; alpha += velocidade){
		al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(img, al_map_rgba(255-alpha, 255-alpha, 255-alpha, alpha), 0, 0, 0);
        al_flip_display();
        al_rest(0.015);
    }
}