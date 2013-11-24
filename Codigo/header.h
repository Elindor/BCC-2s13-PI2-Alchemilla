#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_memfile.h>
//#include <allegro5/allegro_physfs.h>
//#include <allegro5/allegro_native_dialog.h>

#include "allegroFuncoes.h"
#include "struct.h"
#include "leitura.h"

#define al_init() (al_install_system(ALLEGRO_VERSION_INT, atexit))
