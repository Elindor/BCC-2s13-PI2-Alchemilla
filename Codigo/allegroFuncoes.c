#include "header.h"

//Define endereço p/ botões de mouse
#define LMB 0x01
#define RMB 0x02

//Define altura e largura da tela
int larguraTela = 1000 ;
int alturaTela = 750;

//Variáveis globais
ALLEGRO_DISPLAY *janela = NULL;

ALLEGRO_BITMAP *introImg = NULL;

ALLEGRO_EVENT_QUEUE *mainFila = NULL;
ALLEGRO_EVENT_QUEUE *selectFila = NULL;
ALLEGRO_EVENT_QUEUE *gameFila = NULL;
ALLEGRO_EVENT_QUEUE *infoFila = NULL;
ALLEGRO_EVENT_QUEUE *creditoFila = NULL;

ALLEGRO_BITMAP *menuA = NULL;
ALLEGRO_BITMAP *menuB = NULL;
ALLEGRO_BITMAP *inGameBackground = NULL;
ALLEGRO_BITMAP *infoBackground = NULL;
ALLEGRO_BITMAP *creditoBackground = NULL;

ALLEGRO_FONT *fonte = NULL;
ALLEGRO_FONT *titleFont = NULL;
ALLEGRO_FONT *textFont = NULL;

ALLEGRO_BITMAP *botao = NULL;

ALLEGRO_AUDIO_STREAM *bgm = NULL;

ALLEGRO_SAMPLE *somNoBotao = NULL;
ALLEGRO_SAMPLE *somClickBotao = NULL;
bool playBgm = true;
bool playFx = true;

bool buttonPressed = false;

lista menu;

//Mouse
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

bool clickBotaoL(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila){    //Verifica se o botão foi clicado
    al_register_event_source(fila, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)
    
    al_wait_for_event_timed(fila, evento, 0.0001);                                //Espera 0.001 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && evento->mouse.button == LMB){   //Além de calcular a hitbox, verifica o evento foi um clique
        if(evento->mouse.x >= xa &&                                                     //E se foi com o botão esquerdo do mouse
        evento->mouse.x <= xb &&
        evento->mouse.y >= ya &&
        evento->mouse.y <= yb){
            return true;
        }
    }

    return false;
}

bool clickBotaoR(float xa, float xb, float ya, float yb, ALLEGRO_EVENT *evento, ALLEGRO_EVENT_QUEUE *fila){    //Verifica se o botão foi clicado
    al_register_event_source(fila, al_get_mouse_event_source());                 //Registra fonte dos eventos (mouse)
    
    al_wait_for_event_timed(fila, evento, 0.0001);                                //Espera 0.001 até que algum evento apareça

    if(evento->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && evento->mouse.button == RMB){   //Além de calcular a hitbox, verifica o evento foi um clique
        if(evento->mouse.x >= xa &&                                                     //E se foi com o botão esquerdo do mouse
        evento->mouse.x <= xb &&
        evento->mouse.y >= ya &&
        evento->mouse.y <= yb){
            return true;
        }
    }

    return false;
}

//Som
void playSample(ALLEGRO_SAMPLE *sample){
    if(!buttonPressed){
        al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        printf("sample tocado.\n");
    }

    else
        printf("sample não tocado.\n");
}

//mainMenu
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

    al_set_window_title(janela, "Alchemilla");                                      //Cria um título pra janela

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

    mainFila = al_create_event_queue();                                             //Cria fila de eventos
    if(!mainFila){                                                                  //Fila não criada
        fprintf(stderr, "Fila de eventos nao foi criada.\n");
        al_destroy_display(janela);
        return false;
    }

    fonte = al_load_font("Fonte/zekton.ttf", 26, 0);
    if(!fonte){
        fprintf(stderr, "Erro ao carregar fonte\n");
        al_destroy_display(janela);
        al_destroy_event_queue(mainFila);
        return false;
    }

    menuA = al_load_bitmap("Imagem/MenuA.png");
    if(!menuA){
        fprintf(stderr, "MenuA nao foi criado.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(mainFila);
        al_destroy_font(fonte);
        return false;
    }

    bgm = al_load_audio_stream("Audio/bgm.ogg", 4, 1024);
    if(!bgm){
        fprintf(stderr, "Erro ao criar bgm.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(mainFila);
        al_destroy_font(fonte);
        al_destroy_bitmap(menuA);
        return false;
    }

    somClickBotao = al_load_sample("Audio/badDisk.wav");
    if(!somClickBotao){
        fprintf(stderr, "Erro ao criar somClickBotao.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(mainFila);
        al_destroy_font(fonte);
        al_destroy_bitmap(menuA);
        al_destroy_audio_stream(bgm);
        return false;
    }

    al_attach_audio_stream_to_mixer(bgm, al_get_default_mixer());
    al_set_audio_stream_playing(bgm, true);
    al_set_audio_stream_playmode(bgm, ALLEGRO_PLAYMODE_LOOP);

    return true;                                                                    //Tudo em ordem
}

int mainMenu(){

    if(mainInit() == false){        //Caso algum componente nõo tenha sido carregado corretamente, 
        printf("Erro\n");       //exibe mensagem de erro e fecha o prorama.
        return -1;
    }

    while(1){       //Enquanto o botão não for clicado

        ALLEGRO_EVENT evento;

        if(checkSair(&evento, mainFila))
            break;

        al_clear_to_color(al_map_rgb(0, 0, 0));                                 //Limpa a tela
        al_draw_bitmap(menuA, 0, 0, 0);

        //Check
        if(clickBotaoL(740, 909, 98, 154, &evento, mainFila)){
            playSample(somClickBotao);

            if(selectMenu() == 1)                                               //Se o retorno for devido ao click de sair do jogo
                break;
        }

        else if(clickBotaoL(741, 909, 187, 243, &evento, mainFila)){
            playSample(somClickBotao);

            intro();
        }

        else if(clickBotaoL(741, 909, 277, 333, &evento, mainFila)){
            playSample(somClickBotao);

            if(creditos() == 1)
            	break;
        }

        else if(clickBotaoL(740, 909, 365, 421, &evento, mainFila)){
            playSample(somClickBotao);
            
            mainFinish();
            return 0;
        }

        //Checagens de maouse sobre botão
        if(checkBotao(740, 909, 98, 154, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 108, ALLEGRO_ALIGN_CENTRE, "Jogar");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 108, ALLEGRO_ALIGN_CENTRE, "Jogar");

        if(checkBotao(741, 909, 187, 243, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825, 197, ALLEGRO_ALIGN_CENTRE, "Intro");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825, 197, ALLEGRO_ALIGN_CENTRE, "Intro");

        if(checkBotao(741, 909, 277, 333, &evento, mainFila))        //Caso o mouse esteja em cima do botão
           al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825, 287, ALLEGRO_ALIGN_CENTRE, "Créditos");

        else  
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825, 287, ALLEGRO_ALIGN_CENTRE, "Créditos");

        if(checkBotao(740, 909, 365, 421, &evento, mainFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 375, ALLEGRO_ALIGN_CENTRE, "Sair");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 375, ALLEGRO_ALIGN_CENTRE, "Sair");

        al_flip_display();                                                      //Atualiza a tela
        
        /*do{
            al_wait_for_event(mainFila, &evento);
        }while(evento.type == ALLEGRO_EVENT_TIMER);*/

        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            buttonPressed = true;
        }

        else
            buttonPressed = false;
    }

    mainFinish();

    return 0;
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

//Intro
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

bool introInit(){
    introImg = al_load_bitmap("Imagem/the game.png");                             //Carrega introImg (perdi)
    if(!introImg){                                                                //Se o introImg não for carregado
        fprintf(stderr, "Bitmap nao foi criado.\n");
        mainFinish();
        return false;
    }

    return true;
}

void introFinish(){
    al_destroy_bitmap(introImg);
}

//selectMenu
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

int selectMenu(){
    if(!selectInit()){
        printf("Erro.\n");
        mainFinish();
        return -1;
    }

    while(1){

        ALLEGRO_EVENT evento;

        if(checkSair(&evento, selectFila)){
            selectFinish();
            return 1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(menuB, 0, 0, 0);

        if(checkBotao(742, 911, 114, 170, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 826.5, 124, ALLEGRO_ALIGN_CENTRE, "Fase 1");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 826.5, 124, ALLEGRO_ALIGN_CENTRE, "Fase 1");

        if(checkBotao(741, 910, 204, 260, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 825.5, 214, ALLEGRO_ALIGN_CENTRE, "Fase 2");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 825.5, 214, ALLEGRO_ALIGN_CENTRE, "Fase 2");

        if(checkBotao(740, 909, 293, 349, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 824.5, 303, ALLEGRO_ALIGN_CENTRE, "Fase 3");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 824.5, 303, ALLEGRO_ALIGN_CENTRE, "Fase 3");

        if(checkBotao(739, 908, 382, 438, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 392, ALLEGRO_ALIGN_CENTRE, "Fase 4");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 392, ALLEGRO_ALIGN_CENTRE, "Fase 4");

        if(checkBotao(739, 908, 471, 527, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 481, ALLEGRO_ALIGN_CENTRE, "Fase 5");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 481, ALLEGRO_ALIGN_CENTRE, "Fase 5");

        if(checkBotao(739, 908, 560, 616, &evento, selectFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 823.5, 570, ALLEGRO_ALIGN_CENTRE, "Fase 6");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 823.5, 570, ALLEGRO_ALIGN_CENTRE, "Fase 6");

        //////////////////////////////////////////

        if(checkBotao(0, 50, 0, 50, &evento, selectFila))
            al_draw_tinted_bitmap(botao, (al_map_rgba(128, 128, 128, 0)), 0, 0, 0);

        else
            al_draw_bitmap(botao, 0, 0, 0);

        if(clickBotaoL(0, 50, 0, 50, &evento, selectFila)){
            playSample(somClickBotao);
            break;
        }

        ///////////////////////////////////////////////

        if(clickBotaoL(742, 911, 114, 170, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(1) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }
        }

        else if(clickBotaoL(741, 910, 204, 260, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(2) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }
        }

        else if(clickBotaoL(740, 909, 293, 349, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(3) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }
        }

        else if(clickBotaoL(739, 908, 382, 438, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(4) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }

        }

        else if(clickBotaoL(739, 908, 471, 527, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(5) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }
        }

        else if(clickBotaoL(739, 908, 560, 616, &evento, selectFila)){
            playSample(somClickBotao);

            if(gameMenu(6) == 1){       //Se o retorno for devido ao click de sair do jogo
                selectFinish();
                return 1;
            }
        }

        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            buttonPressed = true;
        }

        else
            buttonPressed = false;

        al_flip_display();
    }

    selectFinish();

    return 0;
}

void selectFinish(){
    al_destroy_bitmap(menuB);
    al_destroy_bitmap(botao);
    al_destroy_event_queue(selectFila);
}

//infoMenu
bool infoInit(){
    infoBackground = al_load_bitmap("Imagem/infoBackground.png");
    if(!infoBackground){
        fprintf(stderr, "Falha ao carregar infoBackground.\n");
        return false;
    }

    titleFont = al_load_font("Fonte/zektonbo.ttf", 36, 0);
    if(!titleFont){
        fprintf(stderr, "Erro ao carregar titleFont.\n");
        al_destroy_bitmap(infoBackground);
        return false;
    }

    textFont = al_load_font("Fonte/zekton.ttf", 14, 0);
    if(!textFont){
    	fprintf(stderr, "Erro ao carregar textFont\n");
    	al_destroy_bitmap(infoBackground);
    	al_destroy_font(titleFont);
    }

    infoFila = al_create_event_queue();
    if(!infoFila){
    	fprintf(stderr, "Erro ao criar infoFila.\n");
    	al_destroy_bitmap(infoBackground);
    	al_destroy_font(titleFont);
    	al_destroy_font(textFont);
    	return false;
    }

    return true;
}

void infoFinish(){
    al_destroy_bitmap(infoBackground);
    al_destroy_font(titleFont);
    al_destroy_event_queue(infoFila);

    infoname[0] = '\0';
    infosymbol[0] = '\0';
    infotext[0] = '\0';
}

int infoMenu(){
    if(!infoInit()){
        fprintf(stderr, "Erro ao iniciar info.\n");
        return -1;
    }

    int i;
    char linha1[101], linha2[101], linha3[101], linha4[101], linha5[101];

    for(i=0; i<100; i++){
    	linha1[i] = infotext[i];

    	if(infotext[i] == '\0')
    		break;
    }

    if(i == 100){
    	for(i = 100; i<200; i++){
    		linha2[i%100] = infotext[i];

    		if(infotext[i] == '\0')
    			break;
    	}

    	if(i == 200){
    		for(i = 200; i<300; i++){
    			linha3[i%100] = infotext[i];

    			if(infotext[i] == '\0')
    				break;
    		}

    		if(i == 300){
    			for(i = 300; i<400; i++){
    				linha4[i%100] = infotext[i];

    				if(infotext[i] == '\0')
    					break;
    			}

    			if(i == 400){
    				for(i = 400; i<500; i++){
    					linha5[i%100] = infotext[i];

    					if(infotext[i] == '\0')
    						break;
    				}
    			}

    			else
    				linha5[0] = '\0';
    		}

    		else
    			linha4[0] = '\0';
    	}

    	else
    		linha3[0] = '\0';
    }

    else
    	linha2[0] = '\0';

    linha1[100] = '\0';
    linha2[100] = '\0';
    linha3[100] = '\0';
    linha4[100] = '\0';
    linha5[100] = '\0';

    while(1){
        ALLEGRO_EVENT evento;

        if(checkSair(&evento, infoFila)){
            infoFinish();
            return 1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(infoBackground, 0, 0, 0);

        if(checkBotao(425, 600, 585, 641, &evento, infoFila))        //Caso o mouse esteja em cima do botão
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 512.5, 595, ALLEGRO_ALIGN_CENTRE, "Voltar");

        else
            al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 512.5, 595, ALLEGRO_ALIGN_CENTRE, "Voltar");

        if(clickBotaoL(425, 600, 585, 641, &evento, infoFila))
            break;

        al_draw_textf(titleFont, (al_map_rgb(0, 0, 0)), 140, 160, ALLEGRO_ALIGN_LEFT, "%s", infoname);
        al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 885, 170, ALLEGRO_ALIGN_RIGHT, "%s", infosymbol);

        al_draw_textf(textFont, (al_map_rgb(0, 0, 0)), 160, 300, ALLEGRO_ALIGN_LEFT, "%s", linha1);
        al_draw_textf(textFont, (al_map_rgb(0, 0, 0)), 160, 325, ALLEGRO_ALIGN_LEFT, "%s", linha2);
        al_draw_textf(textFont, (al_map_rgb(0, 0, 0)), 160, 350, ALLEGRO_ALIGN_LEFT, "%s", linha3);
        al_draw_textf(textFont, (al_map_rgb(0, 0, 0)), 160, 375, ALLEGRO_ALIGN_LEFT, "%s", linha4);
        al_draw_textf(textFont, (al_map_rgb(0, 0, 0)), 160, 400, ALLEGRO_ALIGN_LEFT, "%s", linha5);

        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            buttonPressed = true;
        }

        else
            buttonPressed = false;

        al_flip_display();
    }

    infoFinish();

    return 0;
}

//gameMenu
bool gameInit(){
	gameFila = al_create_event_queue();
	if(!gameFila){
		fprintf(stderr, "Erro ao criar gameFila.\n");
		mainFinish();
		return false;
	}

    inGameBackground = al_load_bitmap("Imagem/inGameBackground.png");
    if(!inGameBackground){
        fprintf(stderr, "Erro ao carregar inGameBackground.\n");
        al_destroy_event_queue(gameFila);
        mainFinish();
        return false;
    }

    menu = inicializa_lista();
    filenamesgen();
    start_menu(&menu);

	return true;
}

int gameMenu(int NSNumeroDaFase){
    fase = NSNumeroDaFase;
    int page = 1;				//Define qual página de elementos usar

    if(!gameInit()){
        fprintf(stderr, "Erro,\n");
        return -1;
    }

    while(1){

        ALLEGRO_EVENT evento;

        if(checkSair(&evento, gameFila)){
            gameFinish();
            return 1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(inGameBackground, 0, 0, 0);
        //al_draw_text(fonte, al_map_rgb(0, 0, 0), 831.5, 65, ALLEGRO_ALIGN_CENTRE, "Lista de Elementos");

    //Checagem para voltar à seleção de fase(funcionará direito quando for implementado os pop-ups)
        if(checkBotao(0, 50, 0, 50, &evento, gameFila))
            al_draw_tinted_bitmap(botao, (al_map_rgba(128, 128, 128, 0)), 0, 0, 0);

        else
            al_draw_bitmap(botao, 0, 0, 0);

        if(clickBotaoL(0, 50, 0, 50, &evento, gameFila)){
            playSample(somClickBotao);
            break;
        }

    /////////////////////////////////////////////////////////////
        if(clickBotaoL(201, 317, 597, 712, &evento, gameFila) && reagentes[0] != 0){   // Reag1
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            
            inreag = reagentes[0];
            strcpy(inreagname, reagname[0]);
            printf("Colocou reagente: %d\n", reagentes[0]);
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(201, 317, 597, 712, &evento, gameFila)){   // Reag1
        	if(reagentes[0] != 0){
        		info_reag(reagentes[0]);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }


        else if(clickBotaoL(320, 438, 597, 712, &evento, gameFila) && reagentes[1] != 0){   // Reag2
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            inreag = reagentes[1];
            strcpy(inreagname, reagname[1]);
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(320, 438, 597, 712, &evento, gameFila)){   // Reag2
        	if(reagentes[1] != 0){
        		info_reag(reagentes[1]);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }


        else if(clickBotaoL(441, 560, 597, 712, &evento, gameFila) && reagentes[2] != 0){   // Reag3
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            inreag = reagentes[2];
            strcpy(inreagname, reagname[2]);
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(441, 560, 597, 712, &evento, gameFila)){   // Reag3
        	if(reagentes[2] != 0){
        		info_reag(reagentes[2]);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }

        else if(clickBotaoL(563, 679, 597, 712, &evento, gameFila) && reagentes[3] != 0){   // Reag4
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            inreag = reagentes[3];
            strcpy(inreagname, reagname[3]);
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(563, 679, 597, 712, &evento, gameFila)){   // Reag4
        	if(reagentes[3] != 0){
        		info_reag(reagentes[3]);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }


        else if(clickBotaoL(682, 802, 597, 712, &evento, gameFila) && reagentes[4] != 0){   // Reag5
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            inreag = reagentes[4];
            strcpy(inreagname, reagname[4]);
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(682, 802, 597, 712, &evento, gameFila)){   // Reag5
        	if(reagentes[4] != 0){
        		info_reag(reagentes[4]);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }



        else if(clickBotaoL(104, 298, 140, 190, &evento, gameFila) && in1 != 0){  // In1
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            in1 = 0;
            in1name[0] = '\0';
        }

        else if(clickBotaoR(104, 298, 140, 190, &evento, gameFila)){  // In1
        	if(in1 != 0){

        		lista *a;
        		a = menu.prox;

        		for(int i = 1; i < in1; i++){
        			a = a->prox;
        		}

        		info_elem(a->ElNum);

        		if(infoMenu() == 1){
                	gameFinish();
                	return 1;
            	}
        	}  
        }


        else if(clickBotaoL(424, 618, 140, 190, &evento, gameFila) && in2 != 0){  // In2
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            in2 = 0;
            in2name[0] = '\0';
        }

        else if(clickBotaoR(424, 618, 140, 190, &evento, gameFila)){  // In2
            if(in2 != 0){

        		lista *a;
        		a = menu.prox;
        		for(int i = 1; i < in2; i++){
        			a = a->prox;
        		}

        		info_elem(a->ElNum);

        		if(infoMenu() == 1){
                	gameFinish();
                	return 1;
            	}
        	}   
        }


        else if(clickBotaoL(267, 461, 210, 260, &evento, gameFila) && inreag != 0){  // InReag (Deveria ser 466 por grafico)
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            inreag = 0;
            inreagname[0] = '\0';
            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
                checagem (in1, in2, inreag, &menu);
        }

        else if(clickBotaoR(267, 461, 210, 260, &evento, gameFila)){  // InReag (Deveria ser 466 por grafico)
        	if(inreag != 0){
        		info_reag(inreag);

            	if(infoMenu() == 1){
            	    gameFinish();
            	    return 1;
            	}
            }
        }


        else if(clickBotaoL(133, 332, 333, 383, &evento, gameFila) && out1 != 0){  // Out1
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            if(out1 != 0)
                insert(out1, &menu, 1);

            out1 = 0;
            out1name[0] = '\0';
        }

        else if(clickBotaoR(133, 332, 333, 383, &evento, gameFila)){  // Out1
            if(out1 != 0){

        		lista *a;
        		a = menu.prox;
        		for(int i = 1; i < in2; i++){
        			a = a->prox;
        		}

        		info_elem(a->ElNum);

        		if(infoMenu() == 1){
                	gameFinish();
                	return 1;
            	}
        	}   
        }


        else if(clickBotaoL(383, 582, 333, 383, &evento, gameFila) && out2 != 0){  // Out2
            playSample(somClickBotao);
            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            if(out2 != 0)
                insert(out2, &menu, 1);

            out2 = 0;
            out2name[0] = '\0';
        }


        else if(clickBotaoR(383, 582, 333, 383, &evento, gameFila)){  // Out2
            if(out2 != 0){

        		lista *a;
        		a = menu.prox;
        		for(int i = 1; i < in2; i++){
        			a = a->prox;
        		}

        		info_elem(a->ElNum);

        		if(infoMenu() == 1){
                	gameFinish();
                	return 1;
            	}
        	}   
        }

    /*---------------------------------------*/
        if(checkBotao(201, 317, 597, 712, &evento, gameFila))   // Reag1
             al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 259, 637, ALLEGRO_ALIGN_CENTRE, "%s", reagname[0]);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 259, 637, ALLEGRO_ALIGN_CENTRE, "%s", reagname[0]);


        if(checkBotao(320, 438, 597, 712, &evento, gameFila))   // Reag2
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 379, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[1]);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 379, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[1]);

        if(checkBotao(441, 560, 597, 712, &evento, gameFila))   // Reag3
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 500.5, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[2]);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 500.5, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[2]);

        if(checkBotao(563, 679, 597, 712, &evento, gameFila))   // Reag4
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 621, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[3]);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 621, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[3]);

        if(checkBotao(682, 802, 597, 712, &evento, gameFila))   // Reag5
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 742, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[4]);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 742, 597, ALLEGRO_ALIGN_CENTRE, "%s", reagname[4]);


        if(checkBotao(104, 298, 140, 190, &evento, gameFila))  // In1
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 201, 140, ALLEGRO_ALIGN_CENTRE, "%s", in1name);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 201, 140, ALLEGRO_ALIGN_CENTRE, "%s", in1name);    


        if(checkBotao(424, 618, 140, 190, &evento, gameFila))  // In2
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 521, 140, ALLEGRO_ALIGN_CENTRE, "%s", in2name);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 521, 140, ALLEGRO_ALIGN_CENTRE, "%s", in2name);


        if(checkBotao(267, 461, 210, 260, &evento, gameFila))  // InReag (Deveria ser 466 por grafico)
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 364, 210, ALLEGRO_ALIGN_CENTRE, "%s", inreagname);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 364, 210, ALLEGRO_ALIGN_CENTRE, "%s", inreagname);


        if(checkBotao(133, 331, 333, 383, &evento, gameFila))  // Out1
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 232, 333, ALLEGRO_ALIGN_CENTRE, "%s", out1name);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 232, 333, ALLEGRO_ALIGN_CENTRE, "%s", out1name);

        if(checkBotao(384, 582, 333, 383, &evento, gameFila))  // Out2
            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 482, 333, ALLEGRO_ALIGN_CENTRE, "%s", out2name);
        else
            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 482, 333, ALLEGRO_ALIGN_CENTRE, "%s", out2name);

        //logtext1
        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 50, 493, ALLEGRO_ALIGN_LEFT, "%s", logtext1);
        
        //logtext2
        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 50, 545, ALLEGRO_ALIGN_LEFT, "%s", logtext2);


	//Gambiarra ahead!
        switch(page){
        	case 1:
        		if(checkBotao(856, 906, 57.5, 107.5, &evento, gameFila))
        			al_draw_tinted_bitmap(botao, al_map_rgba(128, 128, 128, 0), 856, 57.5, ALLEGRO_FLIP_HORIZONTAL);
	
        		else
        			al_draw_bitmap(botao, 856, 57.5, ALLEGRO_FLIP_HORIZONTAL);
	
        		if(clickBotaoL(856, 906, 57.5, 107.5, &evento, gameFila)){
        			playSample(somClickBotao);
        			page++;
        		}


        		if(menu.prox){
    				if(checkBotao(733, 930, 120, 160, &evento, gameFila))  // Struct1
    				    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->ElName);
    				else
    				    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->ElName);
				
    				if(clickBotaoL(733, 930, 120, 160, &evento, gameFila)){  // Struct1
    				    playSample(somClickBotao);
    				    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				
    				    useElement(1, &menu);
    				    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    				        checagem (in1, in2, inreag, &menu);
    				}
				
    				else if(clickBotaoR(733, 930, 120, 160, &evento, gameFila)){  // Struct1
    					if(menu.prox->ElNum != 0){
    						info_elem(menu.prox->ElNum);
		
    				    	if(infoMenu() == 1){
    				    	    gameFinish();
    				    	    return 1;
    				    	}
    					}
    				}
			
    			    if(menu.prox->prox){
    			        if(checkBotao(733, 930, 162, 208, &evento, gameFila))  // Struct2
    			            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 167, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->ElName);
    			        else
    			            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 167, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->ElName);
			
    			        if(clickBotaoL(733, 930, 162, 208, &evento, gameFila)){  // Struct2
    			            playSample(somClickBotao);
    			            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			            useElement(2, &menu);
    			            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                checagem (in1, in2, inreag, &menu);
    			        }
			
    			        else if(clickBotaoR(733, 930, 162, 208, &evento, gameFila)){  // Struct2
    			            if(menu.prox->prox->ElNum != 0){
    							info_elem(menu.prox->prox->ElNum);
    							
    				    		if(infoMenu() == 1){
    				    		    gameFinish();
    				    		    return 1;
    				    		}
    						}
    			        }
			
    			        if(menu.prox->prox->prox){
    			            if(checkBotao(733, 930, 210, 251, &evento, gameFila))  // Struct3
    			                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 215, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->ElName);
    			            else
    			                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 215, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->ElName);
			
    			            if(clickBotaoL(733, 930, 210, 251, &evento, gameFila)){  // Struct3
    			                playSample(somClickBotao);
    			                //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                useElement(3, &menu);
    			                if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                    checagem (in1, in2, inreag, &menu);
    			            }
			
    			            else if(clickBotaoR(733, 930, 210, 251, &evento, gameFila)){  // Struct3
    			                if(menu.prox->prox->prox->ElNum != 0){
    								info_elem(menu.prox->prox->prox->ElNum);
    								
    				    			if(infoMenu() == 1){
    				    			    gameFinish();
    				    			    return 1;
    				    			}
    							}
    			            }
			
    			            if(menu.prox->prox->prox->prox){
    			                if(checkBotao(733, 930, 253, 297, &evento, gameFila))  // Struct4
    			                    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->ElName);
    			                else
    			                    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->ElName);
			
    			                if(clickBotaoL(733, 930, 253, 297, &evento, gameFila)){  // Struct4
    			                    playSample(somClickBotao);
    			                    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                    useElement(4, &menu);
    			                    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                        checagem (in1, in2, inreag, &menu);
    			                }
			
    			                else if(clickBotaoR(733, 930, 253, 297, &evento, gameFila)){  // Struct4
    			                    if(menu.prox->prox->prox->prox->ElNum != 0){
    									info_elem(menu.prox->prox->prox->prox->ElNum);
    									
    				    				if(infoMenu() == 1){
    				    				    gameFinish();
    				    				    return 1;
    				    				}
    								}
    			                }
			
    			                if(menu.prox->prox->prox->prox->prox){
    			                    if(checkBotao(733, 930, 299, 342, &evento, gameFila))  // Struct5
    			                        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->ElName);
    			                    else
    			                        al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->ElName);
			
    			                    if(clickBotaoL(733, 930, 299, 342, &evento, gameFila)){  // Struct5
    			                        playSample(somClickBotao);
    			                        //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                        useElement(5, &menu);
    			                        if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                            checagem (in1, in2, inreag, &menu);
    			                    }
			
    			                    else if(clickBotaoR(733, 930, 299, 342, &evento, gameFila)){  // Struct5
    			                        if(menu.prox->prox->prox->prox->prox->ElNum != 0){
    										info_elem(menu.prox->prox->prox->prox->prox->ElNum);
    										
    				    					if(infoMenu() == 1){
    				    					    gameFinish();
    				    					    return 1;
    				    					}
    									}
    			                    }
			
    			                    if(menu.prox->prox->prox->prox->prox->prox){
    			                        if(checkBotao(733, 930, 344, 387, &evento, gameFila))  // Struct6
    			                            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->ElName);
    			                        else
    			                            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->ElName);
			
    			                        if(clickBotaoL(733, 930, 344, 387, &evento, gameFila)){  // Struct6
    			                            playSample(somClickBotao);
    			                            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                            useElement(6, &menu);
    			                            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                checagem (in1, in2, inreag, &menu);
    			                        }
			
    			                        else if(clickBotaoR(733, 930, 344, 387, &evento, gameFila)){  // Struct6
    			                        	if(menu.prox->prox->prox->prox->prox->prox->ElNum != 0){
    											info_elem(menu.prox->prox->prox->prox->prox->prox->ElNum);
    											
    				    						if(infoMenu() == 1){
    				    						    gameFinish();
    				    						    return 1;
    				    						}
    										}
    			                        }
			
    			                        if(menu.prox->prox->prox->prox->prox->prox->prox){
    			                            if(checkBotao(733, 930, 389, 432, &evento, gameFila))  // Struct7
    			                                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->ElName);
    			                            else
    			                                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                            if(clickBotaoL(733, 930, 389, 432, &evento, gameFila)){  // Struct7
    			                                playSample(somClickBotao);
    			                                //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                useElement(7, &menu);
    			                                if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                    checagem (in1, in2, inreag, &menu);
    			                            }
			
    			                            else if(clickBotaoR(733, 930, 389, 432, &evento, gameFila)){  // Struct7
    			                            	if(menu.prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    												info_elem(menu.prox->prox->prox->prox->prox->prox->prox->ElNum);
    												
    				    							if(infoMenu() == 1){
    				    							    gameFinish();
    				    							    return 1;
    				    							}
    											}
    			                            }
			
    			                            if(menu.prox->prox->prox->prox->prox->prox->prox->prox){
    			                                if(checkBotao(733, 930, 434, 477, &evento, gameFila))  // Struct8
    			                                    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                else
    			                                    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                if(clickBotaoL(733, 930, 434, 477, &evento, gameFila)){  // Struct8
    			                                    playSample(somClickBotao);
    			                                    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                    useElement(8, &menu);
    			                                    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                        checagem (in1, in2, inreag, &menu);
    			                                }
			
    			                                else if(clickBotaoR(733, 930, 434, 477, &evento, gameFila)){  // Struct8
    			                                	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    													info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    													
    				    								if(infoMenu() == 1){
    				    								    gameFinish();
    				    								    return 1;
    				    								}
    												}
    			                                }
			
    			                                if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                                    if(checkBotao(733, 930, 479, 524, &evento, gameFila))  // Struct9
    			                                        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                    else
    			                                        al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                    if(clickBotaoL(733, 930, 479, 524, &evento, gameFila)){  // Struct9
    			                                        playSample(somClickBotao);
    			                                        //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                        useElement(9, &menu);
    			                                        if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                            checagem (in1, in2, inreag, &menu);
    			                                    }
			
    			                                    else if(clickBotaoR(733, 930, 479, 524, &evento, gameFila)){  // Struct9
    			                                    	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    														info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    														
    				    									if(infoMenu() == 1){
    				    									    gameFinish();
    				    									    return 1;
    				    									}
    													}
    			                                    }
			
    			                                    if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                                        if(checkBotao(733, 930, 526, 564, &evento, gameFila))  // Struct10
    			                                            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                        else
    			                                            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                        if(clickBotaoL(733, 930, 526, 564, &evento, gameFila)){  // Struct10
    			                                            playSample(somClickBotao);
    			                                            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                            useElement(10, &menu);
    			                                            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                                checagem (in1, in2, inreag, &menu);
    			                                        }
			
    			                                        else if(clickBotaoR(733, 930, 526, 564, &evento, gameFila)){  // Struct10
    			                                        	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    															info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    															
    				    										if(infoMenu() == 1){
    				    										    gameFinish();
    				    										    return 1;
    				    										}
    														}
    			                                        }
    			                                    }
    			                                }
    			                            }
    			                        }
    			                    }
    			                }
    			            }
    			        }
    			    }
    			}
        		break;

        	case 2:
        		if(checkBotao(763, 813, 57.5, 107.5, &evento, gameFila))
        		al_draw_tinted_bitmap(botao, al_map_rgba(128, 128, 128, 0), 763, 57.5, 0);

        		else
        			al_draw_bitmap(botao, 763, 57.5, 0);
	
        		if(clickBotaoL(763, 813, 57.5, 107.5, &evento, gameFila)){
        			playSample(somClickBotao);
        			page--;
        		}

        		if(menu.prox &&
        			menu.prox->prox &&
        			menu.prox->prox->prox &&
        			menu.prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox &&
        			menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    				if(checkBotao(733, 930, 120, 160, &evento, gameFila))  // Struct1
    				    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    				else
    				    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
				
    				if(clickBotaoL(733, 930, 120, 160, &evento, gameFila)){  // Struct1
    				    playSample(somClickBotao);
    				    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				
    				    useElement(1, &menu);
    				    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    				        checagem (in1, in2, inreag, &menu);
    				}
				
    				else if(clickBotaoR(733, 930, 120, 160, &evento, gameFila)){  // Struct1
    					if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    						info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
		
    				    	if(infoMenu() == 1){
    				    	    gameFinish();
    				    	    return 1;
    				    	}
    					}
    				}
			
    			    if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			        if(checkBotao(733, 930, 162, 208, &evento, gameFila))  // Struct2
    			            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 167, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			        else
    			            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 167, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			        if(clickBotaoL(733, 930, 162, 208, &evento, gameFila)){  // Struct2
    			            playSample(somClickBotao);
    			            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			            useElement(2, &menu);
    			            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                checagem (in1, in2, inreag, &menu);
    			        }
			
    			        else if(clickBotaoR(733, 930, 162, 208, &evento, gameFila)){  // Struct2
    			            if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    							info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    							
    				    		if(infoMenu() == 1){
    				    		    gameFinish();
    				    		    return 1;
    				    		}
    						}
    			        }
			
    			        if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			            if(checkBotao(733, 930, 210, 251, &evento, gameFila))  // Struct3
    			                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 215, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			            else
    			                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 215, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			            if(clickBotaoL(733, 930, 210, 251, &evento, gameFila)){  // Struct3
    			                playSample(somClickBotao);
    			                //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                useElement(3, &menu);
    			                if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                    checagem (in1, in2, inreag, &menu);
    			            }
			
    			            else if(clickBotaoR(733, 930, 210, 251, &evento, gameFila)){  // Struct3
    			                if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    								info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    								
    				    			if(infoMenu() == 1){
    				    			    gameFinish();
    				    			    return 1;
    				    			}
    							}
    			            }
			
    			            if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                if(checkBotao(733, 930, 253, 297, &evento, gameFila))  // Struct4
    			                    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                else
    			                    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                if(clickBotaoL(733, 930, 253, 297, &evento, gameFila)){  // Struct4
    			                    playSample(somClickBotao);
    			                    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                    useElement(4, &menu);
    			                    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                        checagem (in1, in2, inreag, &menu);
    			                }
			
    			                else if(clickBotaoR(733, 930, 253, 297, &evento, gameFila)){  // Struct4
    			                    if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    									info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    									
    				    				if(infoMenu() == 1){
    				    				    gameFinish();
    				    				    return 1;
    				    				}
    								}
    			                }
			
    			                if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                    if(checkBotao(733, 930, 299, 342, &evento, gameFila))  // Struct5
    			                        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                    else
    			                        al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                    if(clickBotaoL(733, 930, 299, 342, &evento, gameFila)){  // Struct5
    			                        playSample(somClickBotao);
    			                        //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                        useElement(5, &menu);
    			                        if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                            checagem (in1, in2, inreag, &menu);
    			                    }
			
    			                    else if(clickBotaoR(733, 930, 299, 342, &evento, gameFila)){  // Struct5
    			                        if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    										info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    										
    				    					if(infoMenu() == 1){
    				    					    gameFinish();
    				    					    return 1;
    				    					}
    									}
    			                    }
			
    			                    if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                        if(checkBotao(733, 930, 344, 387, &evento, gameFila))  // Struct6
    			                            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                        else
    			                            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                        if(clickBotaoL(733, 930, 344, 387, &evento, gameFila)){  // Struct6
    			                            playSample(somClickBotao);
    			                            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                            useElement(6, &menu);
    			                            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                checagem (in1, in2, inreag, &menu);
    			                        }
			
    			                        else if(clickBotaoR(733, 930, 344, 387, &evento, gameFila)){  // Struct6
    			                        	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    											info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    											
    				    						if(infoMenu() == 1){
    				    						    gameFinish();
    				    						    return 1;
    				    						}
    										}
    			                        }
			
    			                        if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                            if(checkBotao(733, 930, 389, 432, &evento, gameFila))  // Struct7
    			                                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                            else
    			                                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                            if(clickBotaoL(733, 930, 389, 432, &evento, gameFila)){  // Struct7
    			                                playSample(somClickBotao);
    			                                //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                useElement(7, &menu);
    			                                if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                    checagem (in1, in2, inreag, &menu);
    			                            }
			
    			                            else if(clickBotaoR(733, 930, 389, 432, &evento, gameFila)){  // Struct7
    			                            	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    												info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    												
    				    							if(infoMenu() == 1){
    				    							    gameFinish();
    				    							    return 1;
    				    							}
    											}
    			                            }
			
    			                            if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                                if(checkBotao(733, 930, 434, 477, &evento, gameFila))  // Struct8
    			                                    al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                else
    			                                    al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                if(clickBotaoL(733, 930, 434, 477, &evento, gameFila)){  // Struct8
    			                                    playSample(somClickBotao);
    			                                    //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                    useElement(8, &menu);
    			                                    if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                        checagem (in1, in2, inreag, &menu);
    			                                }
			
    			                                else if(clickBotaoR(733, 930, 434, 477, &evento, gameFila)){  // Struct8
    			                                	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    													info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    													
    				    								if(infoMenu() == 1){
    				    								    gameFinish();
    				    								    return 1;
    				    								}
    												}
    			                                }
			
    			                                if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                                    if(checkBotao(733, 930, 479, 524, &evento, gameFila))  // Struct9
    			                                        al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                    else
    			                                        al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                    if(clickBotaoL(733, 930, 479, 524, &evento, gameFila)){  // Struct9
    			                                        playSample(somClickBotao);
    			                                        //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                        useElement(9, &menu);
    			                                        if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                            checagem (in1, in2, inreag, &menu);
    			                                    }
			
    			                                    else if(clickBotaoR(733, 930, 479, 524, &evento, gameFila)){  // Struct9
    			                                    	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    														info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    														
    				    									if(infoMenu() == 1){
    				    									    gameFinish();
    				    									    return 1;
    				    									}
    													}
    			                                    }
			
    			                                    if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox){
    			                                        if(checkBotao(733, 930, 526, 564, &evento, gameFila))  // Struct10
    			                                            al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
    			                                        else
    			                                            al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElName);
			
    			                                        if(clickBotaoL(733, 930, 526, 564, &evento, gameFila)){  // Struct10
    			                                            playSample(somClickBotao);
    			                                            //al_play_sample(somClickBotao, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			
    			                                            useElement(10, &menu);
    			                                            if(in1 > 0 && in2 > 0 && in1 < 10 && in2 <10)
    			                                                checagem (in1, in2, inreag, &menu);
    			                                        }
			
    			                                        else if(clickBotaoR(733, 930, 526, 564, &evento, gameFila)){  // Struct10
    			                                        	if(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum != 0){
    															info_elem(menu.prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->prox->ElNum);
    															
    				    										if(infoMenu() == 1){
    				    										    gameFinish();
    				    										    return 1;
    				    										}
    														}
    			                                        }
    			                                    }
    			                                }
    			                            }
    			                        }
    			                    }
    			                }
    			            }
    			        }
    			    }
    			}
        		break;
        }

        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            buttonPressed = true;
        }

        else
            buttonPressed = false;

        al_flip_display();
    }

    gameFinish();

    return 0;
}

void gameFinish(){
    int i;

	al_destroy_event_queue(gameFila);
	al_destroy_bitmap(inGameBackground);
    termina_lista(&menu);

    out1 = 0;
    out2 = 0;
    in1 = 0;
    in2 = 0;
    inreag = 0;
    target = 0;

    for(i=0; i<10; i++)
        reagentes[i] = 0;

    out1name[0] = '\0';
    out2name[0] = '\0';
    targetname[0] = '\0';

    for(i=0; i<10; i++)
        reagname[i][0] = '\0';

    in1name[0] = '\0';
    in2name[0] = '\0';
    inreagname[0] = '\0';
    confere[0] = '\0';

    logtext1[0] = '\0';
    logtext2[0] = '\0';

}

//opcaoMenu
/*bool opcaoInit(){

}

void opcaoFinish(){

}

int opcaoMenu(){

}*/

//creditos
bool creditoInit(){
	creditoBackground = al_load_bitmap("Imagem/creditos.png");
	if(!creditoBackground){
		fprintf(stderr, "Erro ao criar creditoBackground.\n");
		return false;
	}

	creditoFila = al_create_event_queue();
	if(!creditoFila){
		fprintf(stderr, "Erro ao criar creditoFila.\n");
		al_destroy_bitmap(creditoBackground);
		return false;
	}

	return true;
}

int creditos(){
	if(!creditoInit()){
		fprintf(stderr, "Erro ao iniciar créditos.\n");
		return -1;
	}

	while(1){
		ALLEGRO_EVENT evento;

        if(checkSair(&evento, creditoFila)){
            creditoFinish();
            return 1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(creditoBackground, 0, 0, 0);

        if(clickBotaoL(742, 915, 607, 663, &evento, creditoFila)){
        	playSample(somClickBotao);
        	break;
        }

        if(checkBotao(742, 915, 607, 663, &evento, creditoFila))
            al_draw_text(fonte, (al_map_rgb(128, 0, 0)), 828.5, 615, ALLEGRO_ALIGN_CENTRE, "Voltar");

        else
        	al_draw_text(fonte, (al_map_rgb(0, 0, 0)), 828.5, 615, ALLEGRO_ALIGN_CENTRE, "Voltar");

        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            buttonPressed = true;
        }

        else
            buttonPressed = false;

        al_flip_display();
	}

    creditoFinish();

	return 0;
}

void creditoFinish(){
	al_destroy_bitmap(creditoBackground);
	al_destroy_event_queue(creditoFila);
}