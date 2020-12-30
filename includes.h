#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <tuple>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ------------------------------------------------

#define SCREEN_WIDTH  glutGet( GLUT_SCREEN_WIDTH  )
#define SCREEN_HEIGHT glutGet( GLUT_SCREEN_HEIGHT )
#define PI 3.14
#define INIT_W 1200
#define INIT_H 800

int windowWidth = 1200, windowHeight = 800;
GLUquadric *sphere = NULL, *cylinder = NULL, *circleObj = NULL;
float global_ambient[4] = {0.2, 0.2, 0.2, 1.0};
float noEmission[4] = { 0.0, 0.0, 0.0, 1.0 };
float noSpecular[4] = { 0.0, 0.0, 0.0, 1.0 };
float noAmbient[4] = { 0.0, 0.0, 0.0, 1.0 };
float noDiffuse[4] = { 0.0, 0.0, 0.0, 1.0 };
float noShininess = 0.0;

float orthoNum = 300;
float perspectiveEye = 90.0;
float perspectiveNear = 1.5, perspectiveFar = 400.0;
bool sunOn = true, fishOn = true, armOn = true;
bool sunMove = true;
vector<float> caveDirect = { sinf( (float)56.0 * PI / (float)180.0 ),
                             0.0,
                             cosf( (float)56.0 * PI / (float)180.0 ) };

float m[16];
enum KEYBOARD
{
    ESC = 27, SPACE = 32
};

enum PERSPECTIVE
{
    OrthoX, OrthoY, OrthoZ,
    FIRST_VIEW, THIRD_VIEW, GOD_VIEW,
    EACH_VIEW, MY_VIEW
};

int viewing = MY_VIEW;