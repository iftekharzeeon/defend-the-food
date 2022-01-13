# include "iGraphics.h"
# include "gl.h"
# include <ctype.h>
# include <mmsystem.h>

    int antNum;
    double ant[110][3];
    double dr;
    double cen_x, cen_y, plate_rad;
    double mouse_x, mouse_y;

    double highest_rad;
    double time_to_call_ant;
    double rem_draw_ant1, rem_draw_ant2;

    int anim_time;
    int game_status = 3;
    int check;
    int score = 0;
    int option = 0;
    int menuSlide = 0;
    int menuAnime = 0;
    int shamitStop = 0;
    int resetNum = 1;

    char h_scre[10];
    char scre[10];
    char first[10];
    char second[10];
    char third[10];
    char fourth[10];
    char fifth[10];
    char player_name[13];
    char p_name_file[13];
    int i, len, mode, player_number, tn, counter;
    FILE *fp;
    char ts[13];

    char tempStringShamit[10];
        struct players
    {
        int scores;
        char name[50];
    };

    struct players p1;
    struct players p2[10];

void iBoldText(double LeftX, double LeftY, char ara[])
{
    iText(LeftX-.5, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(LeftX-.5, LeftY-.5, ara, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(LeftX, LeftY-.5, ara, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(LeftX, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
}

void iBoldHelveticaText(double LeftX, double LeftY, char ara[])
{
    iText(LeftX-.5, LeftY, ara, GLUT_BITMAP_HELVETICA_18);
    iText(LeftX-.5, LeftY-.5, ara, GLUT_BITMAP_HELVETICA_18);
    iText(LeftX, LeftY-.5, ara, GLUT_BITMAP_HELVETICA_18);
    iText(LeftX, LeftY, ara, GLUT_BITMAP_HELVETICA_18);
}

void file_input()
{
    fp = fopen("scores.txt", "a+");
    i = 0;
    while(1)
    {
        fscanf(fp, "%s %d", &p1.name, &p1.scores);
        strcpy(p2[i].name, p1.name);
        p2[i].scores = p1.scores;
        i++;
        if(fgetc(fp) == EOF)
            break;

    }

    player_number = i;
    for (i=0; i<player_number - 1; i++)
    {
       for (int j=i+1; j<player_number - 1; j++)
       {
           if(p2[j].scores >= p2[i].scores)
           {
                strcpy(ts, p2[i].name);
                strcpy(p2[i].name, p2[j].name);
                strcpy(p2[j].name, ts);

                tn = p2[i].scores;
                p2[i].scores = p2[j].scores;
                p2[j].scores = tn;
           }

       }
    }
    fclose(fp);

}

void create_an_ant()
{
    int random_num;
    double random_angle;

    //generates a random angle for the ant to come
    //srand((unsigned) time(NULL));
    random_num = rand();
    random_num = random_num%360;
    random_num++;
    random_angle = (random_num/180.0)*M_PI;

    //auto reset option to start the array again
    if ((score % 100 == 0) && (score > 0) && (resetNum != 0))
    {
        antNum = 0;
        resetNum = 0;
    }

    if(score % 100 > 1)
        resetNum = 1;

    //increase ants
    antNum++;
    ant[antNum-1][0] = 1;
    ant[antNum-1][1] = highest_rad;
    ant[antNum-1][2] = random_angle;
}

void increase_time_to_call_ant()
{
    // increases ant number
    if(time_to_call_ant > 800)
        time_to_call_ant -= 800;
}

void motion_of_ant()
{
    // loops through every ants to increase their motion
    for(int i = 0; i < antNum; i++)
    {
        if(ant[i][0] == 0) continue;
            ant[i][1] -= dr;

        // if the ant reaches food... game over
        if(ant[i][1] < plate_rad)
        {
            PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC );

            ant[i][0] = 0;

            game_status = -2;

            antNum = 0;

            break;
        }

        // call from game, if user clicks give up
        if(shamitStop)
        {
            shamitStop = 0;
            break;
        }
    }
}

void motion_increaser()
{
    // faster ants
    if (dr < 30)
        dr += 0.05;
}

void draw_ant(int ant_num, double rad, double theta)
{
    double x1 = 0, x2 = 0;
    double y1 = 0, y2 = 0;
    double a,b,c;
    iSetColor(0,0,0);
    rem_draw_ant1 = rad;
    rem_draw_ant2 = (int)rad % 2;
    if (((int)rad)%20 > 5) a =1,b=1.2, c=1;
    else if (((int)rad)%20 > 5 && ((int)rad)%25 < 10) a =1.2,b=1.1, c=1.05;
    else if (((int)rad)%20 > 10 && ((int)rad)%25 < 15) a = 1.3,b = 1, c=1.1;
    else a =1.2,b=1.1, c=1.05;

    // head
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 8);

    // minimum click range
    x1 = cen_x + rad*cos(theta);
    y1 = cen_y + rad*sin(theta);

    // antenna 1
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 25*cos(theta+M_PI_4), cen_y + rad*sin(theta) - 25*sin(theta+M_PI_4));
    iLine(cen_x + rad*cos(theta) - 25*cos(theta+M_PI_4), cen_y + rad*sin(theta) - 25*sin(theta+M_PI_4), cen_x + rad*cos(theta) - 25*cos(theta+M_PI_4) + 15*cos(theta+M_PI_4 + 1.2*M_PI_2) , cen_y + rad*sin(theta) - 25*sin(theta+M_PI_4) + 15*sin(theta+M_PI_4+ 1.2*M_PI_2));

    // antenna 2
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 25*cos(theta-M_PI_4), cen_y + rad*sin(theta) - 25*sin(theta-M_PI_4));
    iLine(cen_x + rad*cos(theta) - 25*cos(theta-M_PI_4), cen_y + rad*sin(theta) - 25*sin(theta-M_PI_4), cen_x + rad*cos(theta) - 25*cos(theta-M_PI_4) + 15*cos(theta-M_PI_4 - 1.2*M_PI_2) , cen_y + rad*sin(theta) - 25*sin(theta-M_PI_4) + 15*sin(theta-M_PI_4- 1.2*M_PI_2));

    // body 1
    rad += 10;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 7);

    // leg 1
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta+a*(M_PI_4+.3)), cen_y + rad*sin(theta) - 20*sin(theta+a*(M_PI_4+.3)));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta+a*(M_PI_4+.3)), cen_y + rad*sin(theta) - 20*sin(theta+a*(M_PI_4+.3)),cen_x + rad*cos(theta) - 20*cos(theta+a*(M_PI_4+.3)) + 10*cos(theta+a*(M_PI_4+.3) + 1.5*M_PI_2) , cen_y + rad*sin(theta) - 20*sin(theta+a*(M_PI_4+.3)) + 10*sin(theta+a*(M_PI_4+.3) + 1.5*M_PI_2));

    // leg 1
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta-a*(M_PI_4+.3)), cen_y + rad*sin(theta) - 20*sin(theta-a*(M_PI_4+.3)));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta-a*(M_PI_4+.3)), cen_y + rad*sin(theta) - 20*sin(theta-a*(M_PI_4+.3)),cen_x + rad*cos(theta) - 20*cos(theta-a*(M_PI_4+.3)) + 10*cos(theta-a*(M_PI_4+.3) - 1.5*M_PI_2) , cen_y + rad*sin(theta) - 20*sin(theta-a*(M_PI_4+.3)) + 10*sin(theta-a*(M_PI_4+.3) - 1.5*M_PI_2));

    //body 2
    rad += 8;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 5);

    //leg 2
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)));
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)));
    iLine(cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)),cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)) + 5*cos(theta+b*(M_PI_4+.8) + 1.9*M_PI_2), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)) + 5*sin(theta+b*(M_PI_4+.8) + 1.9*M_PI_2));
    iLine(cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)),cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)) + 5*cos(theta-b*(M_PI_4+.8) - 1.9*M_PI_2), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)) + 5*sin(theta-b*(M_PI_4+.8) - 1.9*M_PI_2));

    // body 3
    rad += 3;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 3);
    rad += 3;

    //leg 3
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)));
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)), cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)) + 15*cos(theta+c*(M_PI_4+1.2) + 2.2*M_PI_2), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)) + 15*sin(theta+c*(M_PI_4+1.2) + 2.2*M_PI_2));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)), cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)) + 15*cos(theta-c*(M_PI_4+1.2) - 2.2*M_PI_2), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)) + 15*sin(theta-c*(M_PI_4+1.2) - 2.2*M_PI_2));

    //body 4
    rad += 13;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 13);
    x2 = cen_x + rad*cos(theta);
    y2 = cen_y + rad*sin(theta);


    if(theta >= 0 && theta < M_PI_2) // 1st quadrant
    {
        if(mouse_x >= x1 - 8 && mouse_x <= x2 + 13 && mouse_y >= y1 - 8 && mouse_y <= y2 + 13)
             {
                PlaySound("smash.wav", NULL, SND_ASYNC);
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else if(theta >= M_PI_2 && theta < M_PI) // 2nd quadrant
    {
        if(mouse_x <= x1 + 8 && mouse_x >= x2 - 13 && mouse_y >= y1 - 8 && mouse_y <= y2 + 13)
             {
                PlaySound("smash.wav", NULL, SND_ASYNC);
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else if(theta >= M_PI && theta < 3*M_PI_2) // 3rd quadrant
    {
        if(mouse_x <= x1 + 8 && mouse_x >= x2 - 13 && mouse_y <= y1 + 8 && mouse_y >= y2 - 13)
             {
                PlaySound("smash.wav", NULL, SND_ASYNC);
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else // 4th quadrant
    {
        if(mouse_x >= x1 - 8 && mouse_x <= x2 + 13 && mouse_y <= y1 + 8 && mouse_y >= y2 - 13)
           {
                PlaySound("smash.wav", NULL, SND_ASYNC);
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
}

void iDraw()
{
    iClear();

    if(game_status == 3) // start up menu
    {
        //initial declaration
        {
            iClear();
            score = 0;
            time_to_call_ant = 1000;
            dr = 1;
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);
        }

        // sliding for opening options
        if (menuSlide == 1 && menuAnime < 1280)
        {
            menuAnime += 25;
        }

        // sliding back for main menu
        if (menuSlide == -1 && menuAnime > 0)
        {
            if(menuAnime < 30) option = 0; // so that main buttons works again
            menuAnime -= 25;
        }


        //background drawing
        if(option == 1) // high_score
        {
            iShowBMP(0,0,"High_score background.bmp");
            iSetColor(255, 255, 255);

            // shows score
            itoa(p2[0].scores, first, 10);
            itoa(p2[1].scores, second, 10);
            itoa(p2[2].scores, third, 10);
            itoa(p2[3].scores, fourth, 10);
            itoa(p2[4].scores, fifth, 10);

            iSetColor(255, 255, 255);

            iBoldHelveticaText(350, 500, "R A N K");
            iLine(350, 490, 415, 490);

            iBoldHelveticaText(465, 500, "N A M E");
            iLine(465, 490, 530, 490);

            iBoldHelveticaText(680, 500, "P O I N T S");
            iLine(680, 490, 774, 490);

            iBoldText(365, 440, "1.");
            iBoldText(461, 440, (strupr(p2[0].name)));
            iBoldText(710, 440, first);

            iBoldText(365, 390, "2.");
            iBoldText(461, 390, (strupr(p2[1].name)));
            iBoldText(710, 390, second);

            iBoldText(365, 340, "3.");
            iBoldText(461, 340, (strupr(p2[2].name)));
            iBoldText(710, 340, third);

            iBoldText(365, 290, "4.");
            iBoldText(461, 290, (strupr(p2[3].name)));
            iBoldText(710, 290, fourth);

            iBoldText(365, 240, "5.");
            iBoldText(461, 240, (strupr(p2[4].name)));
            iBoldText(710, 240, fifth);

            fclose(fp);

            if(mouse_x >= 1150 && mouse_x <= 1270 && mouse_y >= 470 && mouse_y <= 890 )
            {
                menuSlide = -1;
            }
        }

        if(option == 2) // credit
        {
            iShowBMP(0,0,"Credit.bmp");
            if(mouse_x >= 1150 && mouse_x <= 1270 && mouse_y >= 470 && mouse_y <= 890 )
            {
                menuSlide = -1;
            }

        }

        //foreground drawing
        iShowBMP(0 + menuAnime ,0,"Main menu.bmp");

        // option choosing
        if(mouse_x >= 400 && mouse_x <= 580 && mouse_y >= 530 && mouse_y <= 630 && option == 0) // play button
        {
            game_status = 2;
            anim_time = 0;
        }

        if(mouse_x >= 80 && mouse_x <= 365 && mouse_y >= 450 && mouse_y <= 550 && option == 0) // high score button
        {
            //High score
            option = 1;
            menuSlide = 1;
        }

        if(mouse_x >= 100 && mouse_x <= 270 && mouse_y >= 150 && mouse_y <= 250 && option == 0) // credit button
        {
            //Credit
            option = 2;
            menuSlide = 1;
        }

        if(mouse_x >= 20 && mouse_x <= 120 && mouse_y >= 600 && mouse_y <= 700 && option == 0) // exit game
        {
            exit(0);
        }

        //reset
        mouse_x = 0;
        mouse_y = 0;
    }

    if(game_status == 2) // start up animation
    {
        score = 0;
        anim_time += 3;

        if (anim_time < 100)
        {
            iSetColor(255,255,255);
            iFilledRectangle(0,0,1280,720);
            iShowBMP(100 - anim_time,  0, "1st Pitcure Background.bmp");
            iShowBMP2(0,0,"1st picture.bmp",255);
            iSetColor(0,0,0);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);
        }
        else if (anim_time < 200)
        {
            iSetColor(255,255,255);
            iFilledRectangle(0,0,1280,720);
            iShowBMP(100 - anim_time/2, 0, "1st Pitcure Background.bmp");
            iShowBMP2(0,0,"2nd picture.bmp",255);
            iSetColor(0,0,0);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);
        }
        else if (anim_time < 300)
        {
            PlaySound("ant.wav", NULL, SND_ASYNC );
            iSetColor(255,255,255);
            iFilledRectangle(0,0,1280,720);
            iShowBMP(150 - (anim_time/3), 80, "3rd picture.bmp");
            iSetColor(0,0,0);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);
        }
        else if (anim_time < 450)
        {
            iSetColor(255,255,255);
            iFilledRectangle(0,0,1280,720);
            iShowBMP(200 - (++anim_time/4), 80, "4th picture.bmp");
            iSetColor(0,0,0);
            iFilledRectangle(0,520,1280,200);
            iFilledRectangle(0,0,1280,230);
            iSetColor(0,0,0);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);

        }
        else
        {
            game_status = 1;
            anim_time = 0;

            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            iResumeTimer(4);

            dr = 1;
            time_to_call_ant = 1000;
            resetNum = 1;
        }
    }

    if(game_status == 1) // actual game
    {
        iShowBMP(0,0,"Game_background.bmp");

        //draws ant
        for(int i = 0; i < antNum; i++)
        {
            if(ant[i][0] == 0) continue;
            draw_ant(i, ant[i][1], ant[i][2]);
        }

        iShowBMP(0,0,"element.bmp");

        //showing if someone points 100% == 0
        if(score%100 < 3 && score%100 >= 0 && score > 6)
            iShowBMP(cen_x - 61, cen_y - 25,"element-100.bmp");

        //score highsore
        itoa(score, scre, 10);
        iText(290, 48.5, scre, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(p2[0].scores, tempStringShamit, 10);
        iText(290, 91, tempStringShamit, GLUT_BITMAP_TIMES_ROMAN_24);


        //iFilledRectangle(65,610,300,75); // pause button
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 610 && mouse_y <= 685)
        {
            game_status = -1;

            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);
        }

        //iFilledRectangle(65,510,300,75);// exit to main button
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 510 && mouse_y <= 585)
        {
            PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC);
            game_status = 3;

            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);

            score = 0;

            antNum = 0;
        }

        //iFilledRectangle(65,410,300,75); // give up button, function in draw ant
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 410 && mouse_y <= 485 && (game_status == 1 || game_status == -1))
        {
            PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC);

            game_status = -2;

            antNum = 0;

            shamitStop = 1;

        }

        //resets
        mouse_x = 0;
        mouse_y = 0;
    }

    if(game_status == -1) // pause menu
    {
        iShowBMP(0,0,"Game_background_pause_Menu.bmp");

        //score high score
        itoa(score, scre, 10);
        iText(290, 48.5, scre, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(p2[0].scores, tempStringShamit, 10);
        iText(290, 91, tempStringShamit, GLUT_BITMAP_TIMES_ROMAN_24);

        //iFilledRectangle(65,610,300,75); // resume button
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 610 && mouse_y <= 685)
        {
            game_status = 1;

            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            iResumeTimer(4);
        }

        //iFilledRectangle(65,510,300,75);// exit to main button
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 510 && mouse_y <= 585)
        {
            PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC);
            game_status = 3;

            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);

            ant[i][0] = 0;

            score = 0;

            antNum = 0;
        }

        //iFilledRectangle(65,410,300,75); // give up button, function in ant motion
        if(mouse_x >= 65 && mouse_x <= 365 && mouse_y >= 410 && mouse_y <= 485 && (game_status == 1 || game_status == -1))
        {
            PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC);
            ant[i][0] = 0;

            game_status = -2;

            antNum = 0;

            shamitStop = 1;

        }

        mouse_x = 0;
        mouse_y = 0;
    }

    if(game_status == -2) //  end path (old : end animation)
    {
        time_to_call_ant = 1000;
        dr = 1;
        antNum = 0;
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);
        iPauseTimer(4);

        game_status = -3;
    }

    if(game_status == -3) // game over menu
    {
        iShowBMP(0,0,"Game over.bmp");
        iText(280, 278, scre, GLUT_BITMAP_TIMES_ROMAN_24);
        mode = 1;
        iText(280, 400, player_name, GLUT_BITMAP_TIMES_ROMAN_24);
        mouse_x = 0;
        mouse_y = 0;
    }


}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_x = mx;
        mouse_y = my;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

void iKeyboard(unsigned char key)
{
    if(key == ' ' && (game_status == 1 || game_status == -1) )
    {
        game_status = -game_status;
        if (game_status > 0)
        {
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            iResumeTimer(4);
        }
        if (game_status < 0)
        {
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);
        }
    }

    if((key == 'S' || key == 's') && game_status == 2)
    {
        PlaySound("ant.wav", NULL, SND_ASYNC );
        game_status = 1;
        anim_time = 0;

        iResumeTimer(1);
        iResumeTimer(2);
        iResumeTimer(3);
        iResumeTimer(4);

        dr = 1;
        time_to_call_ant = 1000;
    }

    if((key == 'S' || key == 's') && game_status == -2)
    {
        game_status = -3;
        anim_time = 0;

        dr = 1;
        time_to_call_ant = 1000;
    }

    if(key == 'b' && game_status == 3)
    {
        menuSlide = -1;
    }

    if (mode == 1 && game_status == -3)
    {
		if (key == '\r')
		{
		    file_input();
		    fp = fopen("scores.txt", "a");
			mode = 0;
			strcpy(p_name_file, player_name);
			if(score > p2[4].scores)
            {
                FILE *fp;
                fp = fopen("scores.txt", "w");
                fprintf(fp, "%s %d\n", p2[0].name, p2[0].scores);
                fprintf(fp, "%s %d\n", p2[1].name, p2[1].scores);
                fprintf(fp, "%s %d\n", p2[2].name, p2[2].scores);
                fprintf(fp, "%s %d\n", p2[3].name, p2[3].scores);
                fprintf(fp, "%s %d\n", p_name_file, score);
                fclose(fp);
            }
			score = 0;
			printf("%s\n", p_name_file);
			for (i = 0; i < len; i++)
                player_name[i] = 0;
			len = 0;
			//player_number++;
			fclose(fp);
			game_status = 3;
			file_input();
		}
		else if (key == 8)
        {
            if(len>0){
                len--;
                player_name[len] = 0;
            }
        }
		else if(key != ' ' && len < 12)
		{
			player_name[len] = toupper(key);
			len++;
		}
	}

}

void iSpecialKeyboard(unsigned char key)
{

}

int main()
{
    PlaySound("sound.wav", NULL, SND_LOOP | SND_ASYNC);

    srand((unsigned)time(NULL));
    antNum = 0;
    time_to_call_ant = 1000;
    highest_rad = 450;
    cen_x = 938;
    cen_y = 363.9;
    plate_rad = 110;
    dr = 1;

    file_input(); //sorting

    iSetTimer(1000, motion_increaser);
    iSetTimer(10, motion_of_ant);
    iSetTimer(10, increase_time_to_call_ant);
    iSetTimer(time_to_call_ant, create_an_ant);
    iInitialize(1280, 720, "Game");

    return 0;
}

