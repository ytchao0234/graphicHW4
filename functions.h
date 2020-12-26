#ifndef _INCLUDES
#define _INCLUDES
    #include "includes.h"
#endif

class ROV;
class Info;

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
void drawFish( bool );
void drawStone();

void drawScene();
void drawWCS();
vector<double> randomColor( bool = true );
vector<double> randomPos();
void initFloor();
void drawFloor();
void initFishes();
void initFishBlock( int );
void drawFishes();
bool fishCollision();
bool graspFish();
void initStones();
void drawStones();
bool stoneCollision();

ROV *myROV = NULL;
Info *myInfo1 = NULL, *myInfo2 = NULL;
vector<unsigned char> pressingKey;

#include "models.hpp"
#include "ROV.hpp"
#include "background.hpp"
#include "Info.hpp"
#include "control.hpp"
#include "view.hpp"
#include "render.hpp"