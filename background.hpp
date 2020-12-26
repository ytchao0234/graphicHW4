pair<int, int> floorSize = { 180, 180 };
int viewSize = 20;

vector<vector<vector<double>>> floorColor( floorSize.first + 1, 
                                           vector<vector<double>>( floorSize.second + 1 ));

vector<vector<double>> fishPara(15, vector<double>(8));
vector<vector<vector<double>>> fishBlock(15, vector<vector<double>>(3, vector<double>(8)));
vector<vector<double>> stonePara(15, vector<double>(6));
vector<vector<vector<double>>> stoneBlock(15, vector<vector<double>>(3, vector<double>(8)));
vector<vector<double>> seaweedPara(20, vector<double>(6));

void drawScene()
{
    drawWCS();
    drawFloor();
    drawFishes();
    drawStones();
    myROV->drawROV();
}

void drawWCS()
{
    glPushMatrix();

        glColor3f( 1.0, 1.0, 1.0 );
        gluSphere( sphere, 2.0, 12, 12 );

        glColor3f( 0.0, 1.0, 1.0 );
        gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );

        glPushMatrix();
            glColor3f( 1.0, 0.0, 1.0 );
            glRotatef( -90.0, 1.0, 0.0, 0.0 );
            gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );
        glPopMatrix();

        glPushMatrix();
            glColor3f( 1.0, 1.0, 0.0 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            gluCylinder( cylinder, 0.5, 0.5, 10, 12, 3 );
        glPopMatrix();

    glPopMatrix();
}

vector<double> randomColor( bool forFloor )
{
    static constexpr double colors[4][3] = 
        { { 0.15, 0.20, 0.10 },
          { 0.10, 0.22, 0.22 },
          { 0.10, 0.15, 0.10 },
          { 0.10, 0.12, 0.05 }};

    int r = (rand() / (RAND_MAX + 1.0)) * 4;
    
    vector<double> color;

    if( forFloor )
        color =  { colors[r][0], colors[r][1], colors[r][2] };
    else 
        color = { (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX };

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
                glColor3f( floorColor[fi][fj][0], floorColor[fi][fj][1], floorColor[fi][fj][2] );
                glVertex3f( i * 10, 0, j * 10 );

                glColor3f( floorColor[fi][fj + 1][0], floorColor[fi][fj + 1][1], floorColor[fi][fj + 1][2] );
                glVertex3f( i * 10, 0, (j + 1) * 10 );

                glColor3f( floorColor[fi + 1][fj + 1][0], floorColor[fi + 1][fj + 1][1], floorColor[fi + 1][fj + 1][2 ]);
                glVertex3f( (i + 1) * 10, 0, (j + 1) * 10 );

                glColor3f( floorColor[fi + 1][fj][0], floorColor[fi + 1][fj][1], floorColor[fi + 1][fj][2] );
                glVertex3f( (i + 1) * 10, 0, j * 10 );
            glEnd();
        }
    }
}

vector<double> randomPos()
{
    double rx = (rand() / (RAND_MAX + 1.0)) * 1700;
    double ry = (rand() / (RAND_MAX + 1.0)) * 200 + 30;
    double rz = (rand() / (RAND_MAX + 1.0)) * 1700;
    
    vector<double> position;

    if( rx > 850 ) rx = 850 - rx;
    if( rz > 850 ) rz = 850 - rz;

    if( rx > 0 && rx < 30 ) rx += 30;
    else if( rx < 0 && rx > -30 ) rx -= 30;

    if( rz > 0 && rz < 30 ) rz += 30;
    else if( rz < 0 && rz > -30 ) rz -= 30;

    position = { rx, ry, rz };

    return position;
}

void initFishBlock( int i )
{
    if( i < 0 ) return;

    fishBlock[i][0] = 
    {
        fishPara[i][0] + fishPara[i][4] * (0.7 * sin( fishPara[i][3] * PI / 180.0) + 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (0.7 * sin( fishPara[i][3] * PI / 180.0) - 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (-0.5 * sin( fishPara[i][3] * PI / 180.0) + 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (-0.5 * sin( fishPara[i][3] * PI / 180.0) - 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (0.7 * sin( fishPara[i][3] * PI / 180.0) + 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (0.7 * sin( fishPara[i][3] * PI / 180.0) - 0.125 * cos( fishPara[i][3] * PI / 180.0 )), 
        fishPara[i][0] + fishPara[i][4] * (-0.5 * sin( fishPara[i][3] * PI / 180.0) + 0.125 * cos( fishPara[i][3] * PI / 180.0 )),
        fishPara[i][0] + fishPara[i][4] * (-0.5 * sin( fishPara[i][3] * PI / 180.0) - 0.125 * cos( fishPara[i][3] * PI / 180.0 ))
    };

    fishBlock[i][1] = 
    {
        fishPara[i][1] + fishPara[i][4] * 0.3,
        fishPara[i][1] + fishPara[i][4] * 0.3,
        fishPara[i][1] + fishPara[i][4] * 0.3,
        fishPara[i][1] + fishPara[i][4] * 0.3,
        fishPara[i][1] + fishPara[i][4] * -0.3,
        fishPara[i][1] + fishPara[i][4] * -0.3,
        fishPara[i][1] + fishPara[i][4] * -0.3,
        fishPara[i][1] + fishPara[i][4] * -0.3
    };

    fishBlock[i][2] = 
    {
        fishPara[i][2] + fishPara[i][4] * (0.7 * cos( fishPara[i][3] * PI / 180.0 ) - 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (0.7 * cos( fishPara[i][3] * PI / 180.0 ) + 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (-0.5 * cos( fishPara[i][3] * PI / 180.0 ) - 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (-0.5 * cos( fishPara[i][3] * PI / 180.0 ) + 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (0.7 * cos( fishPara[i][3] * PI / 180.0 ) - 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (0.7 * cos( fishPara[i][3] * PI / 180.0 ) + 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (-0.5 * cos( fishPara[i][3] * PI / 180.0 ) - 0.125 * sin( fishPara[i][3] * PI / 180.0)),
        fishPara[i][2] + fishPara[i][4] * (-0.5 * cos( fishPara[i][3] * PI / 180.0 ) + 0.125 * sin( fishPara[i][3] * PI / 180.0))
    };
}

void initFishes()
{

    for( int i = 0; i < fishPara.size(); i++ )
    {
        vector<double> pos = randomPos();
        vector<double> color = randomColor( false );

        fishPara[i] = { pos[0], pos[1], pos[2], 
                        (rand()/ (RAND_MAX + 1.0) * 360), (rand()/ (RAND_MAX + 1.0)) * 10.0 + 5.0,
                        color[0], color[1], color[2]};

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

        vector<double> pos = { fishPara[i][0], fishPara[i][1], fishPara[i][2] };
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
        vector<double> pos = randomPos();

        stonePara[i] = { pos[0], pos[2], 
                        (rand()/ (RAND_MAX + 1.0)) * 20 + 5,(rand()/ (RAND_MAX + 1.0)) * 20 + 5,(rand()/ (RAND_MAX + 1.0)) * 20 + 5,
                        (rand()/ (RAND_MAX + 1.0) * 0.1 + 0.1)};

        stoneBlock[i][0] =
        {
            stonePara[i][0] + stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] - stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] + stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] - stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] + stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] - stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] + stonePara[i][2] * 3.23 / 2.0,
            stonePara[i][0] - stonePara[i][2] * 3.23 / 2.0
        };

        stoneBlock[i][1] =
        {
            stonePara[i][3] * 3.23,
            stonePara[i][3] * 3.23,
            stonePara[i][3] * 3.23,
            stonePara[i][3] * 3.23,
            0.0,
            0.0,
            0.0,
            0.0
        };

        stoneBlock[i][2] =
        {
            stonePara[i][1] + stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] + stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] - stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] - stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] + stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] + stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] - stonePara[i][4] * 3.23 / 2.0,
            stonePara[i][1] - stonePara[i][4] * 3.23 / 2.0
        };
    }
}

void drawStones()
{
    for( int i = 0; i < stonePara.size(); i++ )
    {
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
        vector<double> pos = { stonePara[i][0], stonePara[i][3] * 3.23 / 2.0, stonePara[i][1] };
        myROV -> collisionDetect( stoneBlock[i], pos );

        if( myROV->isCollision ) col = true;
    }

    return col;
}
