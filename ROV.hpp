class ROV
{
    public:
        vector<double> pos;
        vector<pair<double, double>> limitPos;
        vector<double> rotation;
        vector<double> facing;
        vector<double> acceleration;
        vector<double> speed;
        vector<bool> isMoving;
        double maxSpeed, bladeAngle, armLength;
        pair<double, double> limitArmLength;
        vector<vector<double>> blockPoints;
        vector<double> handPos;
        vector<vector<double>> handBlockPoints;
        vector<double> collisionVector;
        bool grasping, toDrawBlock, isCollision;
        int graspingFish;
        vector<vector<double>> colors;

        ROV(): pos( { 20.0, 25.0, 20.0 } ),
               limitPos( {{ -900.0, 900.0 }, 
                          { 25.0, 400.0 },
                          { -900.0, 900.0 }} ),
               rotation( { 0.0, 0.0, 1.0, 0.0 } ),
               facing( { 0.0, 0.0, 1.0 } ),
               acceleration( { 0.0, 0.0, 0.0 } ),
               speed( { 0.0, 0.0, 0.0 } ),
               isMoving( { false, false, false } ),
               maxSpeed( 2.0 ),
               bladeAngle( 0.0 ),
               armLength( 1.0 ),
               limitArmLength( { 1.0, 200.0 } ),
               blockPoints(3, vector<double>(8)),
               handPos(3),
               handBlockPoints(3, vector<double>(8)),
               grasping( false ),
               graspingFish( -1 ),
               toDrawBlock( false ),
               isCollision( false )
        { 
            colors = 
            { 
                { 0.0, 0.0, 0.0 },
                { 1.0, 1.0, 1.0 },
                { 0.3, 0.3, 0.3 },
                { 0.5, 0.5, 0.5 },
                { 0.6, 0.6, 0.6 },
                { 0.1, 0.5, 0.7 }
            };
        }

        void setBlockPoint();

        void drawBlock();
        void drawROV();
        void drawMainBody();
        void drawCamera();
        void drawPropeller( bool );
        void drawBlades();
        void drawArm();

        void drawViewVolume();

        void boundAcc();
        void boundSpeed();
        void boundPos();
        void boundBladeAngle();
        void boundArmLength();
        void speedUpDown( bool );
        void moving();

        void turnLeftRight( bool );
        void setFacing();

        bool collision( vector<vector<double>>, vector<vector<double>> );
        void collisionDetect( vector<vector<double>>, vector<double> );
};

void ROV::setBlockPoint()
{
    blockPoints[0] = 
    {
        pos[0] + 22 * facing[0] + 24.071 * facing[2],
        pos[0] + 22 * facing[0] - 24.071 * facing[2],
        pos[0] - 22 * facing[0] + 24.071 * facing[2],
        pos[0] - 22 * facing[0] - 24.071 * facing[2],
        pos[0] + 22 * facing[0] + 24.071 * facing[2],
        pos[0] + 22 * facing[0] - 24.071 * facing[2],
        pos[0] - 22 * facing[0] + 24.071 * facing[2],
        pos[0] - 22 * facing[0] - 24.071 * facing[2],
    };

    blockPoints[1] = 
    {
        pos[1] + 15,
        pos[1] + 15,
        pos[1] + 15,
        pos[1] + 15,
        pos[1] - 12,
        pos[1] - 12,
        pos[1] - 12,
        pos[1] - 12
    };

    blockPoints[2] = 
    {
        pos[2] + 22 * facing[2] - 24.071 * facing[0],
        pos[2] + 22 * facing[2] + 24.071 * facing[0],
        pos[2] - 22 * facing[2] - 24.071 * facing[0],
        pos[2] - 22 * facing[2] + 24.071 * facing[0],
        pos[2] + 22 * facing[2] - 24.071 * facing[0],
        pos[2] + 22 * facing[2] + 24.071 * facing[0],
        pos[2] - 22 * facing[2] - 24.071 * facing[0],
        pos[2] - 22 * facing[2] + 24.071 * facing[0]
    };

    handPos = { pos[0] + (23 + armLength) * facing[0] - 5.0 * facing[2],
                pos[1] - 5.0,
                pos[2] + (23 + armLength) * facing[2] + 5.0 * facing[0] };

    handBlockPoints[0] = 
    {
        handPos[0] + 2.5 * facing[0] + 2.5 * facing[2],
        handPos[0] + 2.5 * facing[0] - 2.5 * facing[2],
        handPos[0] - 2.5 * facing[0] + 2.5 * facing[2],
        handPos[0] - 2.5 * facing[0] - 2.5 * facing[2],
        handPos[0] + 2.5 * facing[0] + 2.5 * facing[2],
        handPos[0] + 2.5 * facing[0] - 2.5 * facing[2],
        handPos[0] - 2.5 * facing[0] + 2.5 * facing[2],
        handPos[0] - 2.5 * facing[0] - 2.5 * facing[2],
    };

    handBlockPoints[1] = 
    {
        handPos[1] + 2.5,
        handPos[1] + 2.5,
        handPos[1] + 2.5,
        handPos[1] + 2.5,
        handPos[1] - 2.5,
        handPos[1] - 2.5,
        handPos[1] - 2.5,
        handPos[1] - 2.5
    };

    handBlockPoints[2] = 
    {
        handPos[2] + 2.5 * facing[2] - 2.5 * facing[0],
        handPos[2] + 2.5 * facing[2] + 2.5 * facing[0],
        handPos[2] - 2.5 * facing[2] - 2.5 * facing[0],
        handPos[2] - 2.5 * facing[2] + 2.5 * facing[0],
        handPos[2] + 2.5 * facing[2] - 2.5 * facing[0],
        handPos[2] + 2.5 * facing[2] + 2.5 * facing[0],
        handPos[2] - 2.5 * facing[2] - 2.5 * facing[0],
        handPos[2] - 2.5 * facing[2] + 2.5 * facing[0]
    };
}

void ROV::drawBlock()
{
    glColor3f( 1.0, 1.0, 1.0 );

    for( int i = 0; i < blockPoints[0].size(); i++ )
    {
        glPushMatrix();
            glTranslatef( blockPoints[0][i], blockPoints[1][i], blockPoints[2][i] );
            glutSolidCube( 1.0 );
        glPopMatrix();
    }

    for( int i = 0; i < handBlockPoints[0].size(); i++ )
    {
        glPushMatrix();
            glTranslatef( handBlockPoints[0][i], handBlockPoints[1][i], handBlockPoints[2][i] );
            glutSolidCube( 1.0 );
        glPopMatrix();
    }
}

void ROV::drawROV()
{
    setBlockPoint();
    if( toDrawBlock )
    {
        // drawBlock();
        drawViewVolume();
    }

    glPushMatrix();
        glTranslatef( pos[0], pos[1], pos[2] );
        glRotatef( rotation[0], rotation[1], rotation[2], rotation[3] );

        drawMainBody();
        drawCamera();
        drawPropeller( true );
        drawPropeller( false );
        drawArm();
        
    glPopMatrix();
}

void ROV::drawMainBody()
{
    glPushMatrix();
        glColor3f( colors[2][0], colors[2][1], colors[2][2] );
        glScalef( 20.0, 20.0, 40.0 );
        glutSolidCube( 1.0 );
    glPopMatrix();
}

void ROV::drawCamera()
{
    glPushMatrix();
        glTranslatef( 0.0, 10.0, 20.0 );

        glPushMatrix();
            glColor3f( colors[4][0], colors[4][1], colors[4][2] );
            glScalef( 10.0, 5.0, 5.0);
            drawTrapezoidalCube();
        glPopMatrix();

        glPushMatrix();
            glColor3f( colors[0][0], colors[0][1], colors[0][2] );
            glTranslatef( 0.0, 2.5, 0.25 );
            gluDisk( circleObj, 0.0, 1.5, 12, 1 );
        glPopMatrix();

        glPushMatrix();
            glColor3f( colors[1][0], colors[1][1], colors[1][2] );
            glTranslatef( 0.0, 2.5, 0.251 );
            gluDisk( circleObj, 0.0, 0.25, 12, 1 );
        glPopMatrix();

    glPopMatrix();
}

void ROV::drawPropeller( bool left )
{
    glPushMatrix();

        if( left )
        {
            glTranslatef( 10.0, 0.0, 0.0 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            glRotatef( 45.0, 1.0, 0.0, 0.0 );

            glColor3f( colors[3][0], colors[3][1], colors[3][2] );
            gluCylinder( cylinder, 1, 1, 10, 12, 3 );
        }
        else
        {
            glTranslatef( -10.0, 0.0, 0.0 );
            glRotatef( -90.0, 0.0, 1.0, 0.0 );
            glRotatef( 45.0, 1.0, 0.0, 0.0 );
            
            glColor3f( colors[3][0], colors[3][1], colors[3][2] );
            gluCylinder( cylinder, 1, 1, 10, 12, 3 );
        }

        glPushMatrix();
            glTranslatef( 0.0, 0.0, 10.0 );
            gluSphere( sphere, 3, 12, 12 );

            glPushMatrix();
                if( left )
                    glRotatef( 90.0, 0.0, 1.0, 0.0 );
                else
                    glRotatef( -90.0, 0.0, 1.0, 0.0 );

                gluCylinder( cylinder, 3, 3, 10, 12, 3 );

                glPushMatrix();
                    glTranslatef( 0.0, 0.0, 10.0 );
                    gluSphere( sphere, 3, 12, 12 );

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glColor3f( colors[2][0], colors[2][1], colors[2][2] );
                        gluSphere( sphere, 1, 12, 12 );

                        if( !left )
                            glRotatef( 180.0, 0.0, 0.0, 1.0);
                        drawBlades();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

void ROV::boundBladeAngle()
{
    if( bladeAngle >= 360.0 || bladeAngle <= -360.0 ) bladeAngle = 0.0;
}

void ROV::drawBlades()
{
    glPushMatrix();
        glRotatef( 90.0, 0.0, 1.0, 0.0 );

        bladeAngle += speed[0] + speed[1] + speed[2];

        boundBladeAngle();

        glRotatef( bladeAngle, 1.0, 0.0, 0.0 );

        glScalef( 1.0, 5.0, 5.0 );
        glColor3f( colors[5][0], colors[5][1], colors[5][2] );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );
    glPopMatrix();
}

void ROV::drawArm()
{
    double angle;

    if( grasping )
        angle = -60.0;
    else
        angle = -45.0;

    boundArmLength();

    glPushMatrix();
        glTranslatef( -5.0, -5.0, 20.0 );
        glColor3f( colors[4][0], colors[4][1], colors[4][2] );
        gluCylinder( cylinder, 1, 1, armLength, 12, 3 );

        glPushMatrix();
            glTranslatef( 0.0, 0.0, armLength );
            gluSphere( sphere, 1, 12, 12 );

            glColor3f( colors[5][0], colors[5][1], colors[5][2] );
            glPushMatrix();
                glRotatef( 90.0, 0.0, 1.0, 0.0 );

                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();

                glRotatef( 120.0, 1.0, 0.0, 0.0 );
                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();

                glRotatef( 120.0, 1.0, 0.0, 0.0 );
                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void ROV::drawViewVolume()
{
    double near = perspectiveNear * tan( perspectiveEye / 2.0 * PI / 180.0 );
    double far = perspectiveFar * tan( perspectiveEye / 2.0 * PI / 180.0 );
    double wh = (double) windowWidth / windowHeight;

    double camera[3] = { pos[0] + facing[0] * 20.0, 
                         pos[1] + facing[1] * 20.0,
                         pos[2] + facing[2] * 20.0 };
    
    double xln = camera[0] + facing[0] * perspectiveNear + facing[2] * near * wh,
           xrn = camera[0] + facing[0] * perspectiveNear - facing[2] * near * wh,
           yun = camera[1] + near,
           ydn = camera[1] - near,
           zln = camera[2] + facing[2] * perspectiveNear - facing[0] * near * wh,
           zrn = camera[2] + facing[2] * perspectiveNear + facing[0] * near * wh;
    
    double xlf = camera[0] + facing[0] * perspectiveFar + facing[2] * far * wh,
           xrf = camera[0] + facing[0] * perspectiveFar - facing[2] * far * wh,
           yuf = camera[1] + far,
           ydf = camera[1] - far,
           zlf = camera[2] + facing[2] * perspectiveFar - facing[0] * far * wh,
           zrf = camera[2] + facing[2] * perspectiveFar + facing[0] * far * wh;

    double nearLeftHigh[3]  = { xln, yun, zln },
           nearLeftLow[3]   = { xln, ydn, zln },
           nearRightHigh[3] = { xrn, yun, zrn },
           nearRightLow[3]  = { xrn, ydn, zrn },
           farLeftHigh[3]   = { xlf, yuf, zlf },
           farLeftLow[3]    = { xlf, ydf, zlf },
           farRightHigh[3]  = { xrf, yuf, zrf },
           farRightLow[3]   = { xrf, ydf, zrf };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f( 0.0, 1.0, 1.0 );
    glBegin( GL_LINES );
        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farLeftHigh[0], farLeftHigh[1], farLeftHigh[2] );

        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farLeftLow[0], farLeftLow[1], farLeftLow[2] );

        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farRightLow[0], farRightLow[1], farRightLow[2] );

        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farRightHigh[0], farRightHigh[1], farRightHigh[2] );
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    glColor4f( 1.0, 1.0, 0.0, 0.2 );
    glBegin( GL_POLYGON );
        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farLeftHigh[0], farLeftHigh[1], farLeftHigh[2] );
        glVertex3f( farLeftLow[0], farLeftLow[1], farLeftLow[2] );
    glEnd();

    glBegin( GL_POLYGON );
        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farLeftLow[0], farLeftLow[1], farLeftLow[2] );
        glVertex3f( farRightLow[0], farRightLow[1], farRightLow[2] );
    glEnd();

    glBegin( GL_POLYGON );
        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farRightLow[0], farRightLow[1], farRightLow[2] );
        glVertex3f( farRightHigh[0], farRightHigh[1], farRightHigh[2] );
    glEnd();

    glBegin( GL_POLYGON );
        glVertex3f( camera[0], camera[1], camera[2] );
        glVertex3f( farRightHigh[0], farRightHigh[1], farRightHigh[2] );
        glVertex3f( farLeftHigh[0], farLeftHigh[1], farLeftHigh[2] );
    glEnd();

    glDisable( GL_BLEND );

    glColor3f( 1.0, 0.0, 0.0 );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin( GL_POLYGON );
        glVertex3f( nearLeftHigh[0], nearLeftHigh[1], nearLeftHigh[2] );
        glVertex3f( nearLeftLow[0], nearLeftLow[1], nearLeftLow[2] );
        glVertex3f( nearRightLow[0], nearRightLow[1], nearRightLow[2] );
        glVertex3f( nearRightHigh[0], nearRightHigh[1], nearRightHigh[2] );
    glEnd();

    glBegin( GL_POLYGON );
        glVertex3f( farLeftHigh[0], farLeftHigh[1], farLeftHigh[2] );
        glVertex3f( farLeftLow[0], farLeftLow[1], farLeftLow[2] );
        glVertex3f( farRightLow[0], farRightLow[1], farRightLow[2] );
        glVertex3f( farRightHigh[0], farRightHigh[1], farRightHigh[2] );
    glEnd();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ROV::boundAcc()
{
    if( speed[0] > 0.01 ) acceleration[0] = -0.05;
    else if( speed[0] < -0.01 ) acceleration[0] = 0.05;
    else acceleration[0] = 0.0;

    if( speed[1] > 0.01 ) acceleration[1] = -0.05;
    else if( speed[1] < -0.01 ) acceleration[1] = 0.05;
    else acceleration[1] = 0.0;

    if( speed[2] > 0.01 ) acceleration[2] = -0.05;
    else if( speed[2] < -0.01 ) acceleration[2] = 0.05;
    else acceleration[2] = 0.0;
}

void ROV::boundSpeed()
{
         if(  acceleration[0] > 0  && speed[0] >  maxSpeed ) speed[0] =  maxSpeed;
    else if(  acceleration[0] < 0  && speed[0] < -maxSpeed ) speed[0] = -maxSpeed;
    else if( !isMoving[0] && fabs(speed[0]) < 0.03 ) speed[0] = 0.0;

         if(  acceleration[1] > 0  && speed[1] >  maxSpeed ) speed[1] =  maxSpeed;
    else if(  acceleration[1] < 0  && speed[1] < -maxSpeed ) speed[1] = -maxSpeed;
    else if( !isMoving[1] && fabs(speed[1]) < 0.03 ) speed[1] = 0.0;

         if(  acceleration[2] > 0  && speed[2] >  maxSpeed ) speed[2] =  maxSpeed;
    else if(  acceleration[2] < 0  && speed[2] < -maxSpeed ) speed[2] = -maxSpeed;
    else if( !isMoving[2] && fabs(speed[2]) < 0.03 ) speed[2] = 0.0;
}

void ROV::boundPos()
{
    if( pos[0] < limitPos[0].first )       pos[0] = limitPos[0].first;
    else if( pos[0] > limitPos[0].second ) pos[0] = limitPos[0].second;

    if( pos[1] < limitPos[1].first)        pos[1] = limitPos[1].first;
    else if( pos[1] > limitPos[1].second ) pos[1] = limitPos[1].second;

    if( pos[2] < limitPos[2].first )       pos[2] = limitPos[2].first;
    else if( pos[2] > limitPos[2].second ) pos[2] = limitPos[2].second;
}

void ROV::boundArmLength()
{
    if( armLength < limitArmLength.first ) armLength = limitArmLength.first;
    else if( armLength > limitArmLength.second ) armLength = limitArmLength.second;
}

void ROV::speedUpDown( bool faster )
{
    if( faster )
    {
        maxSpeed += 0.3;
        if( maxSpeed >= 4.0 ) maxSpeed = 4.0;
    }
    else
    {
        maxSpeed -= 0.3;
        if( maxSpeed <= 1.0 ) maxSpeed = 1.0;
    }
}

void ROV::moving()
{
    speed[0] += acceleration[0];
    speed[1] += acceleration[1];
    speed[2] += acceleration[2];

    boundSpeed();

    pos[0] += speed[0] * facing[0];
    pos[2] += speed[0] * facing[2];

    pos[0] += speed[1] * facing[2];
    pos[2] -= speed[1] * facing[0];

    pos[1] += speed[2];

    boundPos();
}

void ROV::turnLeftRight( bool left )
{
    if( left )
    {
        rotation[0] += 1.0;

        if( rotation[0] >= 360.0 )
            rotation[0] = 0.0;
    }
    else
    {
        rotation[0] -= 1.0;

        if( rotation[0] <= -360.0 )
            rotation[0] = 0.0;
    }
    
    setFacing();
}

void ROV::setFacing()
{
    facing[0] = sin( rotation[0] * PI / 180 );
    facing[2] = cos( rotation[0] * PI / 180 );
}

bool ROV::collision( vector<vector<double>> theOtherBlock, vector<vector<double>> Block )
{
    int i;

    double myXmin, myXmax, myYmin, myYmax, myZmin, myZmax, 
           thatXmin, thatXmax, thatYmin, thatYmax, thatZmin, thatZmax;
    
    myXmin = thatXmin = limitPos[0].second;
    myYmin = thatYmin = limitPos[1].second;
    myZmin = thatZmin = limitPos[2].second;

    myXmax = thatXmax = limitPos[0].first;
    myYmax = thatYmax = limitPos[1].first;
    myZmax = thatZmax = limitPos[2].first;

    for( i = 0; i < 8; i++ )
    {
        if( Block[0][i] < myXmin ) myXmin = Block[0][i];
        else if( Block[0][i] > myXmax ) myXmax = Block[0][i];

        if( Block[1][i] < myYmin ) myYmin = Block[1][i];
        else if( Block[1][i] > myYmax ) myYmax = Block[1][i];

        if( Block[2][i] < myZmin ) myZmin = Block[2][i];
        else if( Block[2][i] > myZmax ) myZmax = Block[2][i];
        
        if( theOtherBlock[0][i] < thatXmin ) thatXmin = theOtherBlock[0][i];
        else if( theOtherBlock[0][i] > thatXmax ) thatXmax = theOtherBlock[0][i];

        if( theOtherBlock[1][i] < thatYmin ) thatYmin = theOtherBlock[1][i];
        else if( theOtherBlock[1][i] > thatYmax ) thatYmax = theOtherBlock[1][i];

        if( theOtherBlock[2][i] < thatZmin ) thatZmin = theOtherBlock[2][i];
        else if( theOtherBlock[2][i] > thatZmax ) thatZmax = theOtherBlock[2][i];
    }

    bool XnotCol = ( thatXmin > myXmax ) || ( myXmin > thatXmax );
    bool YnotCol = ( thatYmin > myYmax ) || ( myYmin > thatYmax );
    bool ZnotCol = ( thatZmin > myZmax ) || ( myZmin > thatZmax );

    return !( XnotCol || YnotCol || ZnotCol );
}

void ROV::collisionDetect( vector<vector<double>> theOtherBlock, vector<double> theOtherPos )
{
    isCollision = collision( theOtherBlock, this->blockPoints );

    if( isCollision )
    {
        double a = pos[0] - theOtherPos[0], b = pos[1] - theOtherPos[1], c = pos[2] - theOtherPos[2];
        double norm = sqrt( a*a + b*b + c*c );

        collisionVector = { a / norm * 2.5, b / norm * 2.5, c / norm * 2.5 };
    }
}
