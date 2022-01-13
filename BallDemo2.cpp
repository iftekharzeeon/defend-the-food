# include "iGraphics.h"
# include "gl.h"

    int antNum;
    double ant[1000][3];
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

    char h_scre[50];
    char scre[50];
    char first[50];
    char second[50];
    char third[50];
    char fourth[50];
    char fifth[50];
    char player_name[100];
    char p_name_file[100];
    int i, len, mode, player_number, tn, counter;
    FILE *fp;
    char ts[100];
    int score_array[100];

    struct players
    {
        int scores;
        char name[50];
    };

    struct players p1;
    struct players p2[100];

void create_an_ant()
{
    int random_num;
    double random_angle;

    //srand((unsigned) time(NULL));
    random_num = rand();
    random_num = random_num%360;
    random_num++;
    random_angle = (random_num/180.0)*M_PI;

    if (antNum > 900)
        antNum = 0;

    antNum++;
    ant[antNum-1][0] = 1;
    ant[antNum-1][1] = highest_rad;
    ant[antNum-1][2] = random_angle;
}

void increase_time_to_call_ant()
{
    if(time_to_call_ant > 1000)
        time_to_call_ant -= 150;
}

void motion_of_ant()
{
   for(int i = 0; i < antNum; i++)
    {
        if(ant[i][0] == 0) continue;
            ant[i][1] -= dr;
        if(ant[i][1] < plate_rad)
        {
            ant[i][0] = 0;

            game_status = -2;

            antNum = 0;

            break;
        }
    }
}

void motion_increaser()
{

    if (dr < 10)
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
    rad += 8;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 5);
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)));
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)));
    iLine(cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)),cen_x + rad*cos(theta) - 12*cos(theta+b*(M_PI_4+.8)) + 5*cos(theta+b*(M_PI_4+.8) + 1.9*M_PI_2), cen_y + rad*sin(theta) - 12*sin(theta+b*(M_PI_4+.8)) + 5*sin(theta+b*(M_PI_4+.8) + 1.9*M_PI_2));
    iLine(cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)),cen_x + rad*cos(theta) - 12*cos(theta-b*(M_PI_4+.8)) + 5*cos(theta-b*(M_PI_4+.8) - 1.9*M_PI_2), cen_y + rad*sin(theta) - 12*sin(theta-b*(M_PI_4+.8)) + 5*sin(theta-b*(M_PI_4+.8) - 1.9*M_PI_2));

    rad += 3;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 3);
    rad += 3;
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)));
    iLine(cen_x + rad*cos(theta), cen_y + rad*sin(theta),cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)), cen_x + rad*cos(theta) - 20*cos(theta+c*(M_PI_4+1.2)) + 15*cos(theta+c*(M_PI_4+1.2) + 2.2*M_PI_2), cen_y + rad*sin(theta) - 20*sin(theta+c*(M_PI_4+1.2)) + 15*sin(theta+c*(M_PI_4+1.2) + 2.2*M_PI_2));
    iLine(cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)), cen_x + rad*cos(theta) - 20*cos(theta-c*(M_PI_4+1.2)) + 15*cos(theta-c*(M_PI_4+1.2) - 2.2*M_PI_2), cen_y + rad*sin(theta) - 20*sin(theta-c*(M_PI_4+1.2)) + 15*sin(theta-c*(M_PI_4+1.2) - 2.2*M_PI_2));
    rad += 13;
    iFilledCircle(cen_x + rad*cos(theta), cen_y + rad*sin(theta), 13);
    x2 = cen_x + rad*cos(theta);
    y2 = cen_y + rad*sin(theta);

    if(theta >= 0 && theta < M_PI_2)
    {
        if(mouse_x >= x1 - 8 && mouse_x <= x2 + 13 && mouse_y >= y1 - 8 && mouse_y <= y2 + 13)
             {
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else if(theta >= M_PI_2 && theta < M_PI)
    {
        if(mouse_x <= x1 + 8 && mouse_x >= x2 - 13 && mouse_y >= y1 - 8 && mouse_y <= y2 + 13)
             {
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else if(theta >= M_PI && theta < 3*M_PI_2)
    {
        if(mouse_x <= x1 + 8 && mouse_x >= x2 - 13 && mouse_y <= y1 + 8 && mouse_y >= y2 - 13)
             {
                ant[ant_num][0] = 0;
                mouse_x = 0;
                mouse_y = 0;
                score ++;
                itoa(score, scre, 10);
           }
    }
    else
    {
        if(mouse_x >= x1 - 8 && mouse_x <= x2 + 13 && mouse_y <= y1 + 8 && mouse_y >= y2 - 13)
           {
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
            time_to_call_ant = 2000;
            dr = 1;
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);
        }

        if (menuSlide == 1 && menuAnime < 1280)
        {
            menuAnime += 10;
        }
        if (menuSlide == -1 && menuAnime > 0)
        {
            if(menuAnime < 20) option = 0; // so that main buttons works again
            menuAnime -= 10;
        }


        //background drawing
        if(option == 1) // high_score
        {
            iSetColor(0, 0, 0);
            iFilledRectangle(0, 0, 1280, 720);
            iSetColor(255, 255, 255);
            iFilledRectangle(50, 50, 1000, 600);
            iSetColor(0, 0, 0);
            fp = fopen("scores.txt", "a+");
            i = 0;
            while(1)
            {
                counter = fgetc(fp);
                if(counter == EOF)
                    break;
                fscanf(fp, "%s %d", &p1.name, &p1.scores);
                strcpy(p2[i].name, p1.name);
                p2[i].scores = p1.scores;
                i++;
            }

            player_number = i;
            for (i=0; i<player_number-1; i++)
            {
               for (int j=i+1; j<player_number; j++)
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

            for (i=0; i<5; i++)
            {
                printf("%s %d\n", p2[i].name, p2[i].scores);
            }

            itoa(p2[0].scores, first, 10);
            itoa(p2[1].scores, second, 10);
            itoa(p2[2].scores, third, 10);
            itoa(p2[3].scores, fourth, 10);
            itoa(p2[4].scores, fifth, 10);

            iText(200, 600, p2[0].name);
            iText(200, 560, p2[1].name);
            iText(200, 520, p2[2].name);
            iText(200, 480, p2[3].name);
            iText(200, 440, p2[4].name);
            iText(250, 600, first);
            iText(250, 560, second);
            iText(250, 520, third);
            iText(250, 480, fourth);
            iText(250, 440, fifth);

            fclose(fp);
        }

        if(option == 2)
        {
            iShowBMP(0,0,"Credit.bmp");
            if(mouse_x >= 1150 && mouse_x <= 1270 && mouse_y >= 470 && mouse_y <= 890 )
            {
                menuSlide = -1;
            }

        } // credit

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
        anim_time++;

        if (anim_time < 100)
        {
            iShowBMP(150 - anim_time,  0, "1st Pitcure Background.bmp");
            iShowBMP2(0,0,"1st picture.bmp",255);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);
        }
        else if (anim_time < 200)
        {
            iShowBMP(150 - anim_time/2, 0, "1st Pitcure Background.bmp");
            iShowBMP2(0,0,"2nd picture.bmp",255);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip", GLUT_BITMAP_HELVETICA_18);
        }
        else if (anim_time < 300)
        {
            iSetColor(255,255,0);
            iFilledRectangle(150 - anim_time/3 , 0, 1000, 680);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if (anim_time < 400)
        {
            iSetColor(0,255,255);
            iFilledRectangle(150 - anim_time/4 , 0,1000, 680);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip",GLUT_BITMAP_TIMES_ROMAN_24);
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
            time_to_call_ant = 2000;
        }
    }

    if(game_status == 1) // actual game
    {
        iShowBMP(0,0,"Game_background.bmp");

        for(int i = 0; i < antNum; i++)
        {
            if(ant[i][0] == 0) continue;
            draw_ant(i, ant[i][1], ant[i][2]);
        }

        iShowBMP(0,0,"element.bmp");
        printf("%d\n", score);
        mouse_x = 0;
        mouse_y = 0;
        itoa(score, scre, 10);
        //itoa(p2[0].scores, h_scre, 10);
        iText(200, 50, scre);
        //iText(400, 50, h_scre);
        printf("%d\n", score);

    }

    if(game_status == -1) // pause menu
    {
        iShowBMP(0,0,"Game_background_pause_Menu.bmp");
        iShowBMP(0,0,"element.bmp");
    }

    if(game_status == -2) // end animation
    {
        score = 0;
        time_to_call_ant = 2000;
        dr = 1;
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);
        iPauseTimer(4);

        anim_time++;

       if (anim_time < 10000/2)
        {
            iSetColor(255,255,255);
            iFilledRectangle(200 - anim_time/(100/2) ,20,1000, 680);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip");
        }
        else if (anim_time < 20000/2)
        {
            iSetColor(255,0,255);
            iFilledRectangle(300 - anim_time/(100/2) ,20,1000, 680);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip");
        }
        else if (anim_time < 30000/2)
        {
            iSetColor(255,255,0);
            iFilledRectangle(400 - anim_time/(100/2) ,20,1000, 680);
            iSetColor(255,255,255);
            iText(1000,10,"Press S to skip");
        }
        else
        {
            game_status = -3;
            anim_time = 0;

            dr = 1;
            time_to_call_ant = 2000;
        }
    }

    if(game_status == -3) // game over menu
    {
        iSetColor(255,255,255);
        iFilledRectangle(0,0,1280,720);
        iSetColor(255,0,0);
        iFilledRectangle(640,360,40,40);
        iSetColor(0,0,0);
        iText(640,360,"Game Over");
        iText(580, 350, "Your Score: "); // zeeon's scoring
        iText(680, 350, scre);           // zeeon's scoring
        iRectangle(300, 300, 350, 80);
        mode = 1;
        iText(305, 303, player_name);


         if(mouse_x >= 640 && mouse_x <= 680 && mouse_y >= 360 && mouse_y <= 400 )
        {
            score = 0;
            game_status = 1;

            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            iResumeTimer(4);
        }
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
        game_status = 1;
        anim_time = 0;

        iResumeTimer(1);
        iResumeTimer(2);
        iResumeTimer(3);
        iResumeTimer(4);

        dr = 1;
        time_to_call_ant = 2000;
    }

    if((key == 'S' || key == 's') && game_status == -2)
    {
        game_status = -3;
        anim_time = 0;

        dr = 1;
        time_to_call_ant = 2000;
    }

    if(key == 'b' && game_status == 3)
    {
        menuSlide = -1;
    }

    if (mode == 1 && game_status == -3)
    {
		if (key == '\r')
		{
		    fp = fopen("scores.txt", "a");
			mode = 0;
			strcpy(p_name_file, player_name);
			fprintf(fp, "%s %d\n", p_name_file, score);
			printf("%s\n", p_name_file);
			for (i = 0; i < len; i++)
				player_name[i] = 0;
			len = 0;
			//player_number++;
			fclose(fp);
			game_status = 3;
		}
		/*else if (key == '8')
        {
            if(len>0){
                player_name[len-1] = '\0';
                len--;
            }
        }*/
		else
		{
			player_name[len] = key;
			len++;
		}
	}

}

void iSpecialKeyboard(unsigned char key)
{

}

int main()
{
    srand((unsigned)time(NULL));
    antNum = 0;
    time_to_call_ant = 2000;
    highest_rad = 450;
    cen_x = 938;
    cen_y = 363.9;
    plate_rad = 110;
    dr = 1;

    iSetTimer(1000, motion_increaser);
    iSetTimer(10, motion_of_ant);
    iSetTimer(100, increase_time_to_call_ant);
    iSetTimer(time_to_call_ant, create_an_ant);
    iInitialize(1280, 720, "Game");

    return 0;
}

