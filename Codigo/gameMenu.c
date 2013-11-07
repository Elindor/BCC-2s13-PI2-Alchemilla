int gameMenu(int NSNumeroDaFase){
    fase = NSNumeroDaFase;
    lista menu;
    filenamesgen();
    start_menu(*menu);

     while(1){

        ALLEGRO_EVENT evento;

        if(checkSair(&evento, selectFila)){
            break;
        }


        else if(clickBotao(201, 317, 597, 712, &evento)){   // Reag1
                    inreag = reagentes[0];
                    inreagname = reagname[0];
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(320, 438, 597, 712, &evento)){   // Reag2
                    inreag = reagentes[1];
                    inreagname = reagname[1];
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(441, 560, 597, 712, &evento)){   // Reag3
                    inreag = reagentes[2];
                    inreagname = reagname[2];
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(563, 679, 597, 712, &evento)){   // Reag4
                    inreag = reagentes[3];
                    inreagname = reagname[3];
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(682, 802, 597, 712, &evento)){   // Reag5
                    inreag = reagentes[4];
                    inreagname = reagname[4];
                    checagem (in1, in2, inreag);
                }


        else if(clickBotao(104, 298, 140, 190, &evento)){  // In1
                    in1 = 0;
                    in1name = NULL;
                }

        else if(clickBotao(424, 618, 140, 190, &evento)){  // In2
                    in2 = 0;
                    in2name = NULL
                }

        else if(clickBotao(267, 461, 210, 260, &evento)){  // InReag (Deveria ser 466 por grafico)
                    inreag = 0;
                    inreagname = NULL;
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(133, 332, 333, 383, &evento)){  // Out1
                    insert(out1, *menu);
                    out1 = 0;
                    out1name = NULL;
                }

        else if(clickBotao(383, 582, 333, 383, &evento)){  // Out2
                    insert(out2, *menu);
                    out2 = 0;
                    out2name = NULL;
                }


        else if(clickBotao(733, 930, 120, 160, &evento)){  // Struct1
                    useElement(1, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 162, 208, &evento)){  // Struct2
                    useElement(2, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 210, 251, &evento)){  // Struct3
                    useElement(3, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 253, 297, &evento)){  // Struct4
                    useElement(4, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 299, 342, &evento)){  // Struct5
                    useElement(5, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 344, 387, &evento)){  // Struct6
                    useElement(6, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 389, 432, &evento)){  // Struct7
                    useElement(7, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 434, 477, &evento)){  // Struct8
                    useElement(8, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 479, 524, &evento)){  // Struct9
                    useElement(9, *menu);
                    checagem (in1, in2, inreag);
                }

        else if(clickBotao(733, 930, 526, 564, &evento)){  // Struct10
                    useElement(10, *menu);
                    checagem (in1, in2, inreag);
                }

                /*---------------------------------------*/

        if(checkBotao(201, 317, 597, 712, &evento, selectFila))   // Reag1
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 259, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 259, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);


        if(checkBotao(320, 438, 597, 712, &evento, selectFila))   // Reag2
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 379, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 379, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);


        if(checkBotao(441, 560, 597, 712, &evento, selectFila))   // Reag3
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 500.5, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 500.5, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);


        if(checkBotao(563, 679, 597, 712, &evento, selectFila))   // Reag4
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 621, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 621, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);


        if(checkBotao(682, 802, 597, 712, &evento, selectFila))   // Reag5
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 742, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 742, 597, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);






        if(checkBotao(104, 298, 140, 190, &evento, selectFila))  // In1
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 201, 140, ALLEGRO_ALIGN_CENTRE, "%s", in1name);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 201, 140, ALLEGRO_ALIGN_CENTRE, "%s", in1name);    


        if(checkBotao(424, 618, 140, 190, &evento, selectFila))  // In2
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 521, 140, ALLEGRO_ALIGN_CENTRE, "%s", in2name);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 521, 140, ALLEGRO_ALIGN_CENTRE, "%s", in2name);


        if(checkBotao(267, 461, 210, 260, &evento, selectFila))  // InReag (Deveria ser 466 por grafico)
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 364, 210, ALLEGRO_ALIGN_CENTRE, "%s", inreagname);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 364, 210, ALLEGRO_ALIGN_CENTRE, "%s", inreagname);


        if(checkBotao(133, 331, 333, 383, &evento, selectFila))  // Out1
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 232, 333, ALLEGRO_ALIGN_CENTRE, "%s", out1name);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 232, 333, ALLEGRO_ALIGN_CENTRE, "%s", out1name);


        if(checkBotao(384, 582, 333, 383, &evento, selectFila))  // Out2
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 482, 333, ALLEGRO_ALIGN_CENTRE, "%s", out2name);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 482, 333, ALLEGRO_ALIGN_CENTRE, "%s", out2name);




        if(checkBotao(733, 930, 120, 160, &evento, selectFila))  // Struct1
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 120, ALLEGRO_ALIGN_CENTRE, "%s", menu -> ElName);


        if(checkBotao(733, 930, 162, 208, &evento, selectFila))  // Struct2
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 162, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 162, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> ElName);


        if(checkBotao(733, 930, 210, 251, &evento, selectFila))  // Struct3
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 210, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 210, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 253, 297, &evento, selectFila))  // Struct4
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 253, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 299, 342, &evento, selectFila))  // Struct5
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 299, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 344, 387, &evento, selectFila))  // Struct6
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 344, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 389, 432, &evento, selectFila))  // Struct7
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 389, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 434, 477, &evento, selectFila))  // Struct8
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 434, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 479, 524, &evento, selectFila))  // Struct9
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 479, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);


        if(checkBotao(733, 930, 526, 564, &evento, selectFila))  // Struct10
                al_draw_textf(fonte, (al_map_rgb(128, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);
            else
                al_draw_textf(fonte, (al_map_rgb(0, 0, 0)), 831.5, 526, ALLEGRO_ALIGN_CENTRE, "%s", menu -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> prox -> ElName);
    
    
    al_flip_display();

}
