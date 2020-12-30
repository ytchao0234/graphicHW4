#ifndef _INCLUDES
#define _INCLUDES
    #include "includes.h"
#endif

class ROV;
class Info;
class SunLight;
class FishLight;
class ArmLight;

void display();
void reshape( int, int );
void initWindow();
void pressing();

void keyCtrl( unsigned char, int, int );
void keyUpCtrl( unsigned char, int, int );
void mouseCtrl( int, int, int, int );

void changeLookAt( int );
void makeProjection( int );
void zoomIn( bool = true );
void zoomOut( bool = true );

void drawTrapezoidalCube();
void drawPyramid( bool );
void drawFish( float, float, float, float, float, float, float, float );
void drawStone( float, float, float, float, float, float );
void drawCup( float, float, float, float, float, float, float );

void drawScene();
void drawWCS();
vector<float> randomColor( bool = true );
vector<float> randomPos();
void initFloor();
void drawFloor();
void drawCave();
void initFishes();
void initFishBlock( int );
void drawFishes();
bool fishCollision();
bool graspFish();
void initStones();
void drawStones();
bool stoneCollision();
void drawCups();

void setLight();

ROV *myROV = NULL;
Info *myInfo1 = NULL, *myInfo2 = NULL;
SunLight *mySun = NULL;
FishLight *myFish = NULL;
ArmLight *armLight = NULL;
vector<unsigned char> pressingKey;

#include "models.hpp"
#include "ROV.hpp"
#include "lights.hpp"
#include "background.hpp"
#include "Info.hpp"
#include "control.hpp"
#include "view.hpp"
#include "render.hpp"