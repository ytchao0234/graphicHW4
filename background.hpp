pair<int, int> floorSize = { 400, 400 };
int viewSize = 20;

vector<vector<vector<float>>> floorColor( floorSize.first + 1, 
                                           vector<vector<float>>( floorSize.second + 1 ));

vector<vector<float>> fishPara(20, vector<float>(8));
vector<vector<vector<float>>> fishBlock(20, vector<vector<float>>(3, vector<float>(8)));
vector<vector<float>> stonePara(20, vector<float>(6));
vector<vector<vector<float>>> stoneBlock(20, vector<vector<float>>(3, vector<float>(8)));
vector<vector<float>> cupPara(5, vector<float>(7));
vector<vector<float>> seaweedPara(20, vector<float>(6));

float WCSambient[4][4] = 
{
    { 1.0, 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 }
};

void drawScene()
{
    glMaterialfv( GL_FRONT, GL_SPECULAR, noSpecular );
    glMaterialf( GL_FRONT, GL_SHININESS, noShininess );
    drawWCS();
    drawFloor();
    drawCave();
    drawFishes();
    drawStones();
    drawCups();
    myROV->drawROV();
}

void drawWCS()
{
    glPushMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WCSambient[0] );

        gluSphere( sphere, 2.0, 12, 12 );

        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WCSambient[1] );
        gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );

        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WCSambient[2] );
            glRotatef( -90.0, 1.0, 0.0, 0.0 );
            gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );
        glPopMatrix();

        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WCSambient[3] );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );
        glPopMatrix();

    glPopMatrix();
}

vector<float> randomColor( bool forFloor )
{
    static constexpr float colors[4][4] = 
        { { 0.25, 0.30, 0.20, 1.0 },
          { 0.20, 0.32, 0.32, 1.0 },
          { 0.20, 0.25, 0.20, 1.0 },
          { 0.20, 0.22, 0.15, 1.0 }};

    int r = (rand() / (RAND_MAX + 1.0)) * 4;
    
    vector<float> color;

    if( forFloor )
        color =  { colors[r][0], colors[r][1], colors[r][2] };
    else 
        color = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };

    return color;
}

void initFloor()
{
    for( int i = 0; i < floorSize.first + 1; ++i )
    { 
        for( int j = 0; j < floorSize.second + 1; ++j )
        {
            floorColor[i][j] = randomColor();
        }
    }
}

void drawFloor()
{
    pair<int, int> x = { max( -floorSize.first / 2, (int) myROV -> pos[0] / 10 - viewSize ),
                         min(  floorSize.first / 2, (int) myROV -> pos[0] / 10 + viewSize ) };

    pair<int, int> z = { max( -floorSize.first / 2, (int) myROV -> pos[2] / 10 - viewSize ),
                         min(  floorSize.first / 2, (int) myROV -> pos[2] / 10 + viewSize ) };

    for( int i = x.first; i < x.second ; i ++ )
    {
        for( int j = z.first; j < z.second; j ++ )
        {
            int fi = i + floorSize.first / 2;
            int fj = j + floorSize.second / 2;
            
            glBegin(GL_POLYGON);
                glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(floorColor[fi][fj][0]) );
                glVertex3f( i * 10, 0, j * 10 );

                glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(floorColor[fi][fj + 1][0]) );
                glVertex3f( i * 10, 0, (j + 1) * 10 );

                glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(floorColor[fi + 1][fj + 1][0]) );
                glVertex3f( (i + 1) * 10, 0, (j + 1) * 10 );

                glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(floorColor[fi + 1][fj][0]) );
                glVertex3f( (i + 1) * 10, 0, j * 10 );
            glEnd();
        }
    }
}

void drawCave()
{
    glDisable(GL_CULL_FACE);
    static float caveColor[4] = { 0.2, 0.2, 0.2, 1.0 };
    glPushMatrix();
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caveColor );
        glTranslatef( 528, 0.0, 687 );
        gluCylinder( cylinder, 100, 100, 1000, 50, 3 );
        gluCylinder( cylinder, 85, 85, 1000, 50, 3 );
        gluDisk( circleObj, 85, 100, 50, 1 );
        glTranslatef( 0.0, 0.0, 1000 );
        gluDisk( circleObj, 85, 100, 50, 1 );
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

vector<float> randomPos()
{
    float rx = (rand() / (RAND_MAX + 1.0)) * 3800;
    float ry = (rand() / (RAND_MAX + 1.0)) * 150 + 30;
    float rz = (rand() / (RAND_MAX + 1.0)) * 3800;
    
    vector<float> position;

    if( rx > 1900 ) rx = 1900 - rx;
    if( rz > 1900 ) rz = 1900 - rz;

    if( rx > 0 && rx < 75 ) rx += 75;
    else if( rx < 0 && rx > -75 ) rx -= 75;

    if( rz > 0 && rz < 75 ) rz += 75;
    else if( rz < 0 && rz > -75 ) rz -= 75;

    position = { rx, ry, rz };

    return position;
}

void initFishBlock( int i )
{
    if( i < 0 ) return;

    fishBlock[i][0] = 
    {
        fishPara[i][0] + fishPara[i][4] * ((float)0.7  * sinf( fishPara[i][3] * PI / 180.0) + (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)0.7  * sinf( fishPara[i][3] * PI / 180.0) - (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)-0.5 * sinf( fishPara[i][3] * PI / 180.0) + (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)-0.5 * sinf( fishPara[i][3] * PI / 180.0) - (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)0.7  * sinf( fishPara[i][3] * PI / 180.0) + (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)0.7  * sinf( fishPara[i][3] * PI / 180.0) - (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )), 
        fishPara[i][0] + fishPara[i][4] * ((float)-0.5 * sinf( fishPara[i][3] * PI / 180.0) + (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * ((float)-0.5 * sinf( fishPara[i][3] * PI / 180.0) - (float)0.125 * cosf( fishPara[i][3] * PI / 180.0 ))
    };

    fishBlock[i][1] = 
    {
        fishPara[i][1] + fishPara[i][4] * (float)0.3,
        fishPara[i][1] + fishPara[i][4] * (float)0.3,
        fishPara[i][1] + fishPara[i][4] * (float)0.3,
        fishPara[i][1] + fishPara[i][4] * (float)0.3,
        fishPara[i][1] + fishPara[i][4] * (float)-0.3,
        fishPara[i][1] + fishPara[i][4] * (float)-0.3,
        fishPara[i][1] + fishPara[i][4] * (float)-0.3,
        fishPara[i][1] + fishPara[i][4] * (float)-0.3
    };

    fishBlock[i][2] = 
    {
        fishPara[i][2] + fishPara[i][4] * ((float)0.7  * cosf( fishPara[i][3] * PI / 180.0 ) - (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)0.7  * cosf( fishPara[i][3] * PI / 180.0 ) + (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)-0.5 * cosf( fishPara[i][3] * PI / 180.0 ) - (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)-0.5 * cosf( fishPara[i][3] * PI / 180.0 ) + (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)0.7  * cosf( fishPara[i][3] * PI / 180.0 ) - (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)0.7  * cosf( fishPara[i][3] * PI / 180.0 ) + (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)-0.5 * cosf( fishPara[i][3] * PI / 180.0 ) - (float)0.125 * sinf( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * ((float)-0.5 * cosf( fishPara[i][3] * PI / 180.0 ) + (float)0.125 * sinf( fishPara[i][3] * PI / 180.0))
    };
}

void initFishes()
{

    for( int i = 0; i < fishPara.size(); i++ )
    {
        vector<float> pos = randomPos();
        vector<float> color = randomColor( false );

        fishPara[i] = { pos[0], pos[1], pos[2], 
                        (rand()/ (RAND_MAX + (float)1.0) * 360), (rand()/ (RAND_MAX + (float)1.0)) * (float)10.0 + (float)5.0,
                        color[0], color[1], color[2]};

        if( i == 0 )
        {
            fishPara[i][0] = -67.0;
            fishPara[i][1] = 100.0;
            fishPara[i][2] = -75.0;
        }

        initFishBlock( i );
    }
}

void drawFishes()
{
    if( myROV->grasping && myROV->graspingFish != -1 )
    {
        fishPara[myROV->graspingFish][0] = myROV->handPos[0];
        fishPara[myROV->graspingFish][1] = myROV->handPos[1];
        fishPara[myROV->graspingFish][2] = myROV->handPos[2];
        fishPara[myROV->graspingFish][3] = myROV->rotation[0] + 225.0;
    }

    for( int i = 0; i < fishPara.size(); i++ )
    {
        if( i == 0 && fishOn )
        {
            myFish->position[0] = fishPara[0][0], 
            myFish->position[1] = fishPara[0][1], 
            myFish->position[2] = fishPara[0][2];
            float emission[4] = { (float)0.2 + myFish->diffuse[0], 
                                  (float)0.2 + myFish->diffuse[1],
                                  (float)0.2 + myFish->diffuse[2],
                                  1.0 };

            glMaterialfv( GL_FRONT, GL_EMISSION, emission );
        }
        else if( i == 1 )
        {
            glMaterialfv( GL_FRONT, GL_EMISSION, noEmission );
        }

        if( myROV->distance( fishPara[i][0], myROV->pos[1], fishPara[i][2] ) > 200.0 )
            continue;
        
        drawFish( fishPara[i][0], 
                  fishPara[i][1],
                  fishPara[i][2], 
                  fishPara[i][3],
                  fishPara[i][4], 
                  fishPara[i][5],
                  fishPara[i][6],
                  fishPara[i][7] );

        // if( myROV->toDrawBlock )
        // {
        //     glColor3f( 1.0, 1.0, 1.0 );

        //     for( int j = 0; j < fishBlock[i][0].size(); j++ )
        //     {
        //         glPushMatrix();
        //             glTranslatef( fishBlock[i][0][j], fishBlock[i][1][j], fishBlock[i][2][j]);
        //             glutSolidCube( 1.0 );
        //         glPopMatrix();
        //     }
        // }
    }
}

bool fishCollision()
{
    bool col = false;

    for( int i = 0; i < fishPara.size(); i++ )
    {
        if( myROV->graspingFish == i ) continue;

        vector<float> pos = { fishPara[i][0], fishPara[i][1], fishPara[i][2] };
        myROV -> collisionDetect( fishBlock[i], pos );

        if( myROV->isCollision ) col = true;
    }

    return col;
}

bool graspFish()
{
    if( myROV->graspingFish != -1 ) return false;

    for( int i = 0; i < fishPara.size(); i++ )
    {
        if( myROV->collision( fishBlock[i], myROV->handBlockPoints ) ) 
        {
            myROV->graspingFish = i;
            return true;
        }  
    }
    return false;
}

void initStones()
{
    for( int i = 0; i < stonePara.size(); i++ )
    {
        vector<float> pos = randomPos();

        stonePara[i] = { pos[0], pos[2], 
                        (rand()/ (RAND_MAX + (float)1.0)) * 20 + 5,(rand()/ (RAND_MAX + (float)1.0)) * 20 + 5,(rand()/ (RAND_MAX + (float)1.0)) * 20 + 5,
                        (rand()/ (RAND_MAX + (float)1.0) * (float)0.1 + (float)0.1)};

        stoneBlock[i][0] =
        {
            stonePara[i][0] + stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] - stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] + stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] - stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] + stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] - stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] + stonePara[i][2] * (float)3.23 / (float)2.0,
            stonePara[i][0] - stonePara[i][2] * (float)3.23 / (float)2.0
        };

        stoneBlock[i][1] =
        {
            stonePara[i][3] * (float)3.23,
            stonePara[i][3] * (float)3.23,
            stonePara[i][3] * (float)3.23,
            stonePara[i][3] * (float)3.23,
            (float)0.0,
            (float)0.0,
            (float)0.0,
            (float)0.0
        };

        stoneBlock[i][2] =
        {
            stonePara[i][1] + stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] + stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] - stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] - stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] + stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] + stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] - stonePara[i][4] * (float)3.23 / (float)2.0,
            stonePara[i][1] - stonePara[i][4] * (float)3.23 / (float)2.0
        };
    }
}

void drawStones()
{
    for( int i = 0; i < stonePara.size(); i++ )
    {
        if( myROV->distance( stonePara[i][0], myROV->pos[1], stonePara[i][1] ) > 200.0 )
            continue;

        drawStone( stonePara[i][0], 
                   stonePara[i][1],
                   stonePara[i][2], 
                   stonePara[i][3],
                   stonePara[i][4], 
                   stonePara[i][5]);

        // if( myROV->toDrawBlock )
        // {
        //     glColor3f( 1.0, 1.0, 1.0 );
        //     for( int j = 0; j < stoneBlock[i][0].size(); j++ )
        //     {
        //         glPushMatrix();
        //             glTranslatef( stoneBlock[i][0][j], stoneBlock[i][1][j], stoneBlock[i][2][j] );
        //             glutSolidCube( 1.0 );
        //         glPopMatrix();
        //     }
        // }
    }
}

bool stoneCollision()
{
    bool col = false;

    for( int i = 0; i < stonePara.size(); i++ )
    {
        vector<float> pos = { stonePara[i][0], stonePara[i][3] * (float)3.23 / (float)2.0, stonePara[i][1] };
        myROV -> collisionDetect( stoneBlock[i], pos );

        if( myROV->isCollision ) col = true;
    }

    return col;
}

void initCups()
{
    for( int i = 0; i < cupPara.size(); i++ )
    {
        vector<float> pos = randomPos();
        pos[0] = pos[0] / (floorSize.first * 10.0 / (float)2.0) * (float)100.0;
        pos[2] = pos[2] / (floorSize.second * 10.0 / (float)2.0) * (float)100.0;

        if( pos[0] > 0 && pos[0] < 20.0 ) pos[0] += 20.0;
        else if(  pos[0] < 0 && pos[0] > -20.0 ) pos[0] -= 20.0;

        if( pos[1] > 0 && pos[1] < 20.0 ) pos[1] += 20.0;
        else if( pos[1] < 0 && pos[1] > -20.0 ) pos[1] -= 20.0;

        vector<float> color = randomColor( false );

        cupPara[i] = { pos[0], pos[2], (rand()/ (RAND_MAX + (float)1.0) * 360),
                      (rand()/ (RAND_MAX + (float)1.0)) * 3 + 1, color[0], color[1], color[2] };
    }
}

void drawCups()
{
    glDisable( GL_CULL_FACE );
    for( int i = 0; i < cupPara.size(); i++ )
    {
        if( myROV->distance( cupPara[i][0], myROV->pos[1], cupPara[i][1] ) > 200.0 )
            continue;

        drawCup( cupPara[i][0], 
                 cupPara[i][1],
                 cupPara[i][2], 
                 cupPara[i][3],
                 cupPara[i][4], 
                 cupPara[i][5], 
                 cupPara[i][6] );
    }
    glEnable( GL_CULL_FACE );
}
