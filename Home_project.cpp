# include "iGraphics.h"

double ball_x, ball_y, ball_r;
double ball_red, ball_green, ball_blue;
double ball_dx, ball_dy;
double box_x, box_y, box_len, box_wid;
double box_red, box_green, box_blue;
int color_change;
double temp_x, temp_y;
double ang;
double poly_x[3];
double poly_y[3];

void angle();
void ball_motion();

void iDraw()
{
    iClear();

    //The background white
    iSetColor(255,255,255);
    iFilledRectangle(0,0,1280,720);

    //collision color change mechanism
    if(color_change > 0)
    {
        box_red =  ball_blue = ball_green = 0;
        box_blue = ball_red = box_green = 255;
    }
    else
    {
        box_red =  ball_blue = ball_green = 255;
        box_blue = ball_red = box_green = 0;
    }

    //background for the moving box
    iSetColor(0,0,0);
    iFilledRectangle(box_x, box_y, box_len, box_wid);

    //moving box
    iSetColor(box_red, box_green, box_blue);
    int i = 20;
    while(i--)
    {
        iRectangle(box_x-i, box_y-i, box_len+i+i, box_wid+i+i);
    }

    //moving ball
    iSetColor(ball_red,ball_green,ball_blue);
    iFilledCircle(ball_x,ball_y,ball_r - 2);

    //overly complicated math for arrow
    iSetColor(255,255,0);
    iLine(ball_x - (ball_r- 19)*cos(ang),ball_y - (ball_r-19)*sin(ang),ball_x + (ball_r-10)*cos(ang),ball_y + (ball_r-10)*sin(ang));
    poly_x[0] = ball_x + (ball_r - 10)*cos(ang);
    poly_y[0] = ball_y + (ball_r - 10)*sin(ang);
    poly_x[1] = ball_x + (ball_r - 19)*cos(ang)*.5 + (ball_r - 19)*sin(ang)*.866025;
    poly_y[1] = ball_y + (ball_r - 19)*sin(ang)*.5 - (ball_r - 19)*cos(ang)*.866025;
    poly_x[2] = ball_x + (ball_r - 19)*cos(ang)*.5 - (ball_r - 19)*sin(ang)*.866025;
    poly_y[2] = ball_y + (ball_r - 19)*sin(ang)*.5 + (ball_r - 19)*cos(ang)*.866025;
    iFilledPolygon(poly_x,poly_y,3);

    //sample text
    iSetColor(0,0,0);
    iText(10,80,"Move the box using W(Up)-A(Left)-S(Down)-D(Right).",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(10,50,"Press right key to rotate the ball clockwise.",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(10,20,"Press left key to rotate the ball counter clockwise",GLUT_BITMAP_TIMES_ROMAN_24);

}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{
    //move up
	if(key == 'w')
	{
	    if(box_y + box_wid < 700)
            box_y ++;
	}

    //move left
	if(key == 'a')
	{
	    if(box_x > 20)
            box_x --;
	}

    //move down
	if(key == 's')
	{
	    if(box_y > 120)
            box_y --;
	}

    //move right
	if(key == 'd')
	{
	    if(box_x + box_len < 1260)
            box_x ++;
	}
}

void iSpecialKeyboard(unsigned char key)
{
    //clock wise movement
    if(key == GLUT_KEY_RIGHT)
    {
        ang -= 0.05;
        temp_x = (sqrt(ball_dx*ball_dx + ball_dy*ball_dy))*cos(ang);
        temp_y = (sqrt(ball_dx*ball_dx + ball_dy*ball_dy))*sin(ang);
        ball_dx = temp_x;
        ball_dy = temp_y;

    }

    //anti clock wise movement
    if(key == GLUT_KEY_LEFT)
    {
        ang += 0.05;
        temp_x = (sqrt(ball_dx*ball_dx + ball_dy*ball_dy))*cos(ang);
        temp_y = (sqrt(ball_dx*ball_dx + ball_dy*ball_dy))*sin(ang);
        ball_dx = temp_x;
        ball_dy = temp_y;
    }
}

int main()
{
	ball_x = 600;
	ball_y = 350;
	ball_r = 50;
	ball_red = 255;
	ball_green = 0;
	ball_blue = 0;
	ball_dx = 2;
	ball_dy = 1;

    box_x = 350;
    box_y = 150;
    box_len = 500;
    box_wid = 500;
    box_red = 0;
    box_green = 0;
    box_blue = 255;

    ang = M_PI_4;

    color_change = 1;

    iSetTimer(1,angle);
    iSetTimer(1,ball_motion);

	iInitialize(1280,720, "1805055_Home_Project");
	return 0;
}

void angle()
{
    if(ball_dx == 0)
    {
        if(ball_dy >= 0) ang = M_PI_2;
        else ang = -M_PI_2;
    }
    else
    {
        ang = atan2(ball_dy,ball_dx);
    }
}

void ball_motion()
{

    //collision to change color
    if((ball_x < (ball_r + box_x))||(ball_x > (box_len - ball_r + box_x))||(ball_y < (ball_r + box_y))||(ball_y > (box_wid - ball_r + box_y)))
    {
        color_change = -color_change;
    }

    //collision to reflect the ball
    if((ball_x < (ball_r + box_x))||(ball_x > (box_len - ball_r + box_x)))
    {
        ball_dx = -ball_dx;
    }

    if((ball_y < (ball_r + box_y))||(ball_y > (box_wid - ball_r + box_y)))
    {
        ball_dy = -ball_dy;
    }

    //glitch fixation
    if((ball_x < (ball_r + box_x))||(ball_x > (box_len - ball_r + box_x)))
    {
        if(ball_x < (ball_r + box_x))
        {
            ball_x += 10;
        }
        if(ball_x > (box_len - ball_r + box_x))
        {
             ball_x -= 10;
        }
    }
    if((ball_y < (ball_r + box_y))||(ball_y > (box_wid - ball_r + box_y)))
    {
        if(ball_y < (ball_r + box_y))
        {
            ball_y += 10;
        }
        if(ball_y > (box_wid - ball_r + box_y))
        {
             ball_y -= 10;
        }
    }

    //actual movement
    ball_x += ball_dx;
    ball_y += ball_dy;
}

