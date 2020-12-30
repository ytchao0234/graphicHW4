class ROV
{
    public:
        vector<float> pos;
        vector<pair<float, float>> limitPos;
        vector<float> rotation;
        vector<float> facing;
        vector<float> handFacing;
        vector<float> handAngle;
        vector<float> acceleration;
        vector<float> speed;
        vector<bool> isMoving;
        float maxSpeed, bladeAngle, armLength;
        pair<float, float> limitArmLength;
        vector<vector<float>> blockPoints;
        vector<float> handPos;
        vector<vector<float>> handBlockPoints;
        vector<float> collisionVector;
        bool grasping, toDrawBlock, isCollision;
        int graspingFish;
        vector<vector<float>> colors;
        vector<vector<float>> ambient;
        vector<vector<float>> diffuse;
        vector<vector<float>> specular;
        vector<float> shininess;
        vector<float> armEmission;

        ROV(): pos( { 20.0, 25.0, 20.0 } ),
               limitPos( {{ -2000.0, 2000.0 }, 
                          { 25.0, 300.0 },
                          { -2000.0, 2000.0 }} ),
               rotation( { 0.0, 0.0, 1.0, 0.0 } ),
               facing( { 0.0, 0.0, 1.0 } ),
               handFacing( { 0.0, 0.0, 1.0 } ),
               handAngle( { 0.0, 0.0, 0.0 } ),
               acceleration( { 0.0, 0.0, 0.0 } ),
               speed( { 0.0, 0.0, 0.0 } ),
               isMoving( { false, false, false } ),
               maxSpeed( 2.0 ),
               bladeAngle( 0.0 ),
               armLength( 1.0 ),
               limitArmLength( { 1.0, 200.0 } ),
               blockPoints(3, vector<float>(8)),
               handPos(3),
               handBlockPoints(3, vector<float>(8)),
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

            ambient = 
            {
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.6, 0.6, 0.6, 1.0 },
                { 0.0, 0.0, 0.0, 1.0 },
                { 1.0, 1.0, 1.0, 1.0 },
                { 0.5, 0.5, 0.5, 1.0 },
                { 0.5, 0.5, 0.5, 1.0 },
                { 0.3, 0.3, 0.3, 1.0 },
                { 0.3, 0.7, 0.9, 1.0 },
                { 0.6, 0.6, 0.6, 1.0 },
                { 0.3, 0.7, 0.9, 1.0 }
            };

            diffuse = 
            {
               { 0.5, 0.5, 0.5, 1.0 },
               { 0.7, 0.7, 0.7, 1.0 },
               { 0.1, 0.1, 0.1, 1.0 },
               { 1.0, 1.0, 1.0, 1.0 },
               { 0.5, 0.5, 0.5, 1.0 },
               { 0.5, 0.5, 0.5, 1.0 },
               { 0.3, 0.3, 0.3, 1.0 },
               { 0.3, 0.7, 0.9, 1.0 },
               { 0.7, 0.7, 0.7, 1.0 },
               { 0.3, 0.7, 0.9, 1.0 }
            };

            specular = 
            {
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.7, 0.7, 0.7, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 },
                { 0.4, 0.4, 0.4, 1.0 }
            };

            shininess =
            {
                64.0, 64.0, 64.0, 64.0, 64.0, 64.0, 64.0, 64.0, 64.0, 64.0
            };

            armEmission = { 0.5, 0.5, 0.5, 1.0 };
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

        float distance( float, float, float );
        bool collision( vector<vector<float>>, vector<vector<float>> );
        void collisionDetect( vector<vector<float>>, vector<float> );
};

void ROV::setBlockPoint()
{
    blockPoints[0] = 
    {
        pos[0] + 22 * facing[0] + (float)24.071 * facing[2],
        pos[0] + 22 * facing[0] - (float)24.071 * facing[2],
        pos[0] - 22 * facing[0] + (float)24.071 * facing[2],
        pos[0] - 22 * facing[0] - (float)24.071 * facing[2],
        pos[0] + 22 * facing[0] + (float)24.071 * facing[2],
        pos[0] + 22 * facing[0] - (float)24.071 * facing[2],
        pos[0] - 22 * facing[0] + (float)24.071 * facing[2],
        pos[0] - 22 * facing[0] - (float)24.071 * facing[2],
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
        pos[2] + 22 * facing[2] - (float)24.071 * facing[0],
        pos[2] + 22 * facing[2] + (float)24.071 * facing[0],
        pos[2] - 22 * facing[2] - (float)24.071 * facing[0],
        pos[2] - 22 * facing[2] + (float)24.071 * facing[0],
        pos[2] + 22 * facing[2] - (float)24.071 * facing[0],
        pos[2] + 22 * facing[2] + (float)24.071 * facing[0],
        pos[2] - 22 * facing[2] - (float)24.071 * facing[0],
        pos[2] - 22 * facing[2] + (float)24.071 * facing[0]
    };

    handPos = { pos[0] + (23 + armLength) * facing[0] - (float)5.0 * facing[2],
                pos[1] - (float)5.0,
                pos[2] + (23 + armLength) * facing[2] + (float)5.0 * facing[0] };

    handBlockPoints[0] = 
    {
        handPos[0] + (float)2.5 * facing[0] + (float)2.5 * facing[2],
        handPos[0] + (float)2.5 * facing[0] - (float)2.5 * facing[2],
        handPos[0] - (float)2.5 * facing[0] + (float)2.5 * facing[2],
        handPos[0] - (float)2.5 * facing[0] - (float)2.5 * facing[2],
        handPos[0] + (float)2.5 * facing[0] + (float)2.5 * facing[2],
        handPos[0] + (float)2.5 * facing[0] - (float)2.5 * facing[2],
        handPos[0] - (float)2.5 * facing[0] + (float)2.5 * facing[2],
        handPos[0] - (float)2.5 * facing[0] - (float)2.5 * facing[2],
    };

    handBlockPoints[1] = 
    {
        handPos[1] + (float)2.5,
        handPos[1] + (float)2.5,
        handPos[1] + (float)2.5,
        handPos[1] + (float)2.5,
        handPos[1] - (float)2.5,
        handPos[1] - (float)2.5,
        handPos[1] - (float)2.5,
        handPos[1] - (float)2.5
    };

    handBlockPoints[2] = 
    {
        handPos[2] + (float)2.5 * facing[2] - (float)2.5 * facing[0],
        handPos[2] + (float)2.5 * facing[2] + (float)2.5 * facing[0],
        handPos[2] - (float)2.5 * facing[2] - (float)2.5 * facing[0],
        handPos[2] - (float)2.5 * facing[2] + (float)2.5 * facing[0],
        handPos[2] + (float)2.5 * facing[2] - (float)2.5 * facing[0],
        handPos[2] + (float)2.5 * facing[2] + (float)2.5 * facing[0],
        handPos[2] - (float)2.5 * facing[2] - (float)2.5 * facing[0],
        handPos[2] - (float)2.5 * facing[2] + (float)2.5 * facing[0]
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
        glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[0][0]) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[0][0]) );
        glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[0][0]) );
        glMaterialf( GL_FRONT, GL_SHININESS, shininess[0] );
        
        glScalef( 20.0, 20.0, 40.0 );
        glutSolidCube( 1.0 );
    glPopMatrix();
}

void ROV::drawCamera()
{
    glPushMatrix();
        glTranslatef( 0.0, 10.0, 20.0 );

        glPushMatrix();
            glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[1][0]) );
            glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[1][0]) );
            glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[1][0]) );
            glMaterialf( GL_FRONT, GL_SHININESS, shininess[1] );
            
            glScalef( 10.0, 5.0, 5.0);
            drawTrapezoidalCube();
        glPopMatrix();

        glPushMatrix();
            glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[2][0]) );
            glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[2][0]) );
            glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[2][0]) );
            glMaterialf( GL_FRONT, GL_SHININESS, shininess[2] );

            glTranslatef( 0.0, 2.5, -0.5 );
            // gluDisk( circleObj, 0.0, 1.5, 12, 1 );

            gluSphere( sphere, 1.5, 12, 12 );
        glPopMatrix();

        // glPushMatrix();
        //     glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[3][0]) );
        //     glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[3][0]) );
        //     glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[3][0]) );
        //     glMaterialf( GL_FRONT, GL_SHININESS, shininess[3] );

        //     glTranslatef( 0.0, 2.5, 0.251 );
        //     gluDisk( circleObj, 0.0, 0.25, 12, 1 );
        // glPopMatrix();

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

            glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[4][0]) );
            glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[4][0]) );
            glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[4][0]) );
            glMaterialf( GL_FRONT, GL_SHININESS, shininess[4] );

            gluCylinder( cylinder, 1, 1, 10, 12, 3 );
        }
        else
        {
            glTranslatef( -10.0, 0.0, 0.0 );
            glRotatef( -90.0, 0.0, 1.0, 0.0 );
            glRotatef( 45.0, 1.0, 0.0, 0.0 );
            
            glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[5][0]) );
            glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[5][0]) );
            glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[5][0]) );
            glMaterialf( GL_FRONT, GL_SHININESS, shininess[5] );

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
                        glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[6][0]) );
                        glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[6][0]) );
                        glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[6][0]) );
                        glMaterialf( GL_FRONT, GL_SHININESS, shininess[6] );
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
        glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[7][0]) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[7][0]) );
        glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[7][0]) );
        glMaterialf( GL_FRONT, GL_SHININESS, shininess[7] );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );
    glPopMatrix();
}

void ROV::drawArm()
{
    float angle;

    if( grasping )
        angle = -60.0;
    else
        angle = -45.0;

    boundArmLength();

    glPushMatrix();
        glTranslatef( -5.0, -5.0, 20.0 );
        glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[8][0]) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[8][0]) );
        glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[8][0]) );
        glMaterialf( GL_FRONT, GL_SHININESS, shininess[8] );
        gluCylinder( cylinder, 1, 1, armLength, 12, 3 );

        glPushMatrix();
            glTranslatef( 0.0, 0.0, armLength );
            glPushMatrix();
                gluSphere( sphere, 1, 12, 12 );
                glRotatef( -90.0, 1.0, 0.0, 0.0 );
                gluCylinder( cylinder, 1, 1, 5, 12, 3 );
                glTranslatef( 0.0, 0.0, 5.0 );
                glRotatef( 90.0, 1.0, 0.0, 0.0 );
                glRotatef( handAngle[2], 0.0, 1.0, 0.0 );
                glRotatef( -handAngle[1], 1.0, 0.0, 0.0 );
                gluSphere( sphere, 1, 12, 12 );
                if( armOn )
                    glMaterialfv( GL_FRONT, GL_EMISSION, &(armEmission[0]) );
                glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[3][0]) );
                glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[3][0]) );
                glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[3][0]) );
                glMaterialf( GL_FRONT, GL_SHININESS, shininess[3] );
                glTranslatef( 0.0, 0.0, 0.5 );
                gluSphere( sphere, 1, 12, 12 );
                glMaterialfv( GL_FRONT, GL_EMISSION, noEmission );
            glPopMatrix();

            glMaterialfv( GL_FRONT, GL_AMBIENT, &(ambient[9][0]) );
            glMaterialfv( GL_FRONT, GL_DIFFUSE, &(diffuse[9][0]) );
            glMaterialfv( GL_FRONT, GL_SPECULAR, &(specular[9][0]) );
            glMaterialf( GL_FRONT, GL_SHININESS, shininess[9] );
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
    float near = perspectiveNear * tanf( perspectiveEye / 2.0 * PI / 180.0 );
    float far = perspectiveFar * tanf( perspectiveEye / 2.0 * PI / 180.0 );
    float wh = (float) windowWidth / windowHeight;

    float camera[3] = { pos[0] + facing[0] * (float)20.0, 
                         pos[1] + facing[1] * (float)20.0,
                         pos[2] + facing[2] * (float)20.0 };
    
    float xln = camera[0] + facing[0] * perspectiveNear + facing[2] * near * wh,
           xrn = camera[0] + facing[0] * perspectiveNear - facing[2] * near * wh,
           yun = camera[1] + near,
           ydn = camera[1] - near,
           zln = camera[2] + facing[2] * perspectiveNear - facing[0] * near * wh,
           zrn = camera[2] + facing[2] * perspectiveNear + facing[0] * near * wh;
    
    float xlf = camera[0] + facing[0] * perspectiveFar + facing[2] * far * wh,
           xrf = camera[0] + facing[0] * perspectiveFar - facing[2] * far * wh,
           yuf = camera[1] + far,
           ydf = camera[1] - far,
           zlf = camera[2] + facing[2] * perspectiveFar - facing[0] * far * wh,
           zrf = camera[2] + facing[2] * perspectiveFar + facing[0] * far * wh;

    float nearLeftHigh[3]  = { xln, yun, zln },
           nearLeftLow[3]   = { xln, ydn, zln },
           nearRightHigh[3] = { xrn, yun, zrn },
           nearRightLow[3]  = { xrn, ydn, zrn },
           farLeftHigh[3]   = { xlf, yuf, zlf },
           farLeftLow[3]    = { xlf, ydf, zlf },
           farRightHigh[3]  = { xrf, yuf, zrf },
           farRightLow[3]   = { xrf, ydf, zrf };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    static float cyan[4] = { 0.0, 1.0, 1.0, 1.0 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan );
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
    
    static float yellow[4] = { 1.0, 1.0, 0.0, 0.5 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow );
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

    static float red[4] = { 1.0, 0.0, 0.0, 1.0 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red );
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

    if( pos[0] <= 600 && pos[0] >= 450 && pos[1] < 110 && pos[2] <= 1680 && pos[2] >= 690 )
    {
        if( pos[0] < 470 )      pos[0] = 470;
        else if( pos[0] > 580 ) pos[0] = 580;

        if( pos[1] > 55 )       pos[1] = 55;
    }
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
    facing[0] = sinf( rotation[0] * PI / 180 );
    facing[2] = cosf( rotation[0] * PI / 180 );

    glPushMatrix();
        glLoadIdentity();
        glRotatef( rotation[0] + handAngle[2], 0.0, 1.0, 0.0 );
        glRotatef( handAngle[1], -1.0, 0.0, 0.0 );

        glGetFloatv( GL_MODELVIEW_MATRIX, m );
    glPopMatrix();

    handFacing[0] = m[8];
    handFacing[1] = m[9];
    handFacing[2] = m[10];
}

float ROV::distance( float x, float y, float z )
{
    return sqrt((x-pos[0])*(x-pos[0]) + (y-pos[1])*(y-pos[1]) + (z-pos[2])*(z-pos[2]));
}

bool ROV::collision( vector<vector<float>> theOtherBlock, vector<vector<float>> Block )
{
    int i;

    float myXmin, myXmax, myYmin, myYmax, myZmin, myZmax, 
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

void ROV::collisionDetect( vector<vector<float>> theOtherBlock, vector<float> theOtherPos )
{
    isCollision = collision( theOtherBlock, this->blockPoints );

    if( isCollision )
    {
        float a = pos[0] - theOtherPos[0], b = pos[1] - theOtherPos[1], c = pos[2] - theOtherPos[2];
        float norm = sqrt( a*a + b*b + c*c );

        collisionVector = { a / norm * (float)2.5, b / norm * (float)2.5, c / norm * (float)2.5 };
    }
}
