/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"

#define N_PLANETS 2
#define N_SATELLITES 5

int g_sunX, g_sunY, g_sunR;

typedef struct _Planet {
    int majorAxisLen;
    int minorAxixLen;
    int radius;
    int sweepAngle;
    int delSweepAngle;
    int nSatellites;
    //Satellite satellite[N_SATELLITES];
} Planet;

Planet g_planet[N_PLANETS] = {
    { 160, 120, 7, 0, 5, 0 },
    { 200, 150, 10, 0, 1, 0 }
};

int g_satelliteOrbitR, g_satelliteR, g_satelliteSweepAngle;

void drawStar(int x, int y, int r) {
    iSetColor(255, 255, 0);
    iFilledCircle(x, y, r);
}

void drawOrbit(int x, int y, int a, int b) {
    iSetColor(255, 255, 255);
    iEllipse(x, y, a, b);
}

void drawPlanet(int x, int y, int orbitA, int orbitB, int planetR, int sweepAngle) {
    double pi = 2*acos(0);
    double sweepRadian = sweepAngle * pi / 180;
    int planetX = x + orbitA * cos(sweepRadian);
    int planetY = y + orbitB * sin(sweepRadian);

    iSetColor(125, 125, 125);
    iFilledCircle(planetX, planetY, planetR);
}

void drawSatellite(
    int x,
    int y,
    int planetOrbitA,
    int planetOrbitB,
    int planetSweepAngle,
    int satelliteOrbitR,
    int satelliteR,
    int satelliteSweepAngle) {
    double pi = 2*acos(0);
    double planetSweepRadian = planetSweepAngle * pi / 180;
    double satelliteSweepRadian = satelliteSweepAngle * pi / 180 + planetSweepRadian;

    int planetX = x + planetOrbitA * cos(planetSweepRadian);
    int planetY = y + planetOrbitB * sin(planetSweepRadian);

    int satelliteX = planetX + satelliteOrbitR * cos(satelliteSweepRadian);
    int satelliteY = planetY + satelliteOrbitR * sin(satelliteSweepRadian);

    iSetColor(62, 62, 62);
    iFilledCircle(satelliteX, satelliteY, satelliteR);
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	double centerX, centerY;
	int i;

	iClear();

	//
	// The sun is at the left focal point of the eliptical orbit. So, the center of orbit
	// needs to be translated appropriately.
	//

	drawStar(g_sunX, g_sunY, g_sunR);

	for (i = 0; i < N_PLANETS; i++) {
        centerX = g_sunX + sqrt(pow(g_planet[i].majorAxisLen, 2) - pow(g_planet[i].minorAxixLen, 2));
        centerY = g_sunY;
        drawOrbit(centerX, centerY, g_planet[i].majorAxisLen, g_planet[i].minorAxixLen);
        drawPlanet(
            centerX,
            centerY,
            g_planet[i].majorAxisLen,
            g_planet[i].minorAxixLen,
            g_planet[i].radius,
            g_planet[i].sweepAngle
            );
//        drawSatellite(
//            centerX,
//            centerY,
//            g_planetOrbitA,
//            g_planetOrbitB,
//            g_planetSweepAngle,
//            g_satelliteOrbitR,
//            g_satelliteR,
//            g_satelliteSweepAngle
//            );
	}
	iSetColor(255, 255, 255);
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

void movePlanets(){
    const int g_dSatelliteSweepAngle = 10;

    int i;

    for (i = 0; i < N_PLANETS; i++) {
        g_planet[i].sweepAngle = (g_planet[i].sweepAngle + g_planet[i].delSweepAngle)%360;
        g_satelliteSweepAngle = (g_satelliteSweepAngle + g_dSatelliteSweepAngle)%360;
    }
}

int main()
{
    const int CX_MAX = 1366;
    const int CY_MAX = 768;

    // Initialize Sun's position and size.
    g_sunX = 150;
    g_sunY = CY_MAX/2;
    g_sunR = 40;

    // Initialize moon's orbit and radius
    g_satelliteOrbitR = 20;
    g_satelliteR = 5;

	//place your own initialization codes here.
	iSetTimer(20, movePlanets);
	iInitialize(CX_MAX, CY_MAX, "Solar system!");

	return 0;
}

