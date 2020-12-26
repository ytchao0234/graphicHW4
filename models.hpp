void drawTrapezoidalCube()
{
    const vector<vector<float>> points = 
    {
        {-0.5, 0, -1.0}, { 0.5, 0.0, -1.0}, 
        { 0.25,  1.0, -0.5}, {-0.25,  1.0, -0.5}, 

        {-0.5, 0.0, 0.0}, { 0.5, 0.0, 0.0},
        { 0.25, 1.0, 0.0}, {-0.25, 1.0, 0.0}
    };

    const vector<vector<int>> faces = 
    {
        {4, 5, 6, 7}, {0, 1, 5, 4}, {1, 2, 6, 5},
        {2, 3, 7, 6}, {0, 4, 7, 3}, {0, 3, 2, 1}
    };

    int i, j;
    
    for( i = 0; i < 6; ++i )
    {
        glBegin(GL_POLYGON); 
            for( j = 0; j < 4; ++j )
            {

                glVertex3f( 
                    points[ faces[i][j] ][0], 
                    points[ faces[i][j] ][1], 
                    points[ faces[i][j] ][2] 
                );
            }
        glEnd();
    }
}

void drawPyramid( bool upward )
{
    const vector<vector<float>> upwardPoints =
    {
        {0.0, 0.0, 1.0},

        {-0.5, 0.5, 0.0}, {-0.5, -0.5, 0.0}, {0.5, -0.5, 0.0}, {0.5, 0.5, 0.0}
    };

    const vector<vector<int>> upwardFaces =
    {
        {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1}, {4, 3, 2, 1}
    };

    const vector<vector<float>> downwardPoints =
    {
        {0.0, 0.0, 0.0},

        {0.5, 0.5, 1.0}, {0.5, -0.5, 1.0}, {-0.5, -0.5, 1.0}, {-0.5, 0.5, 1.0}
    };

    const vector<vector<int>> downwardFaces =
    {
        {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1}, {4, 3, 2, 1}
    };

    vector<vector<float>> points;
    vector<vector<int>> faces;
    int i, j;

    if( upward )
    {
        points.assign( upwardPoints.begin(), upwardPoints.end() );
        faces.assign( upwardFaces.begin(), upwardFaces.end() );
    }
    else
    {
        points.assign( downwardPoints.begin(), downwardPoints.end() );
        faces.assign( downwardFaces.begin(), downwardFaces.end() );
    }

    for( i = 0; i < 4; ++i )
    {
        glBegin(GL_POLYGON); 
            for( j = 0; j < 3; ++j )
            {
                glVertex3f( 
                    points[ faces[i][j] ][0], 
                    points[ faces[i][j] ][1], 
                    points[ faces[i][j] ][2] 
                );
            }
        glEnd();
    }

    glBegin(GL_POLYGON); 
        for( j = 0; j < 4; ++j )
        {
            glVertex3f( 
                points[ faces[4][j] ][0], 
                points[ faces[4][j] ][1], 
                points[ faces[4][j] ][2] 
            );
        }
    glEnd();
}

void drawFish( double posX, double posY, double posZ, 
               double angle, double size, 
               double colorR, double colorG, double colorB )
{
    glColor3f( colorR, colorG, colorB );

    glPushMatrix();

        glTranslatef( posX, posY, posZ );
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glScalef( size, size, size );

        glPushMatrix();
            glScalef( 0.25, 0.6, 1.0 );
            glutSolidCube( 1.0 );
        glPopMatrix();

        glColor3f( 0.0, 0.0, 0.0 );

        glPushMatrix();
            glTranslatef( 0.1251, 0.1, -0.3 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            gluDisk( circleObj, 0.0, 0.05, 12, 1 );
        glPopMatrix();

        glPushMatrix();
            glTranslatef( -0.1251, 0.1, -0.3 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            gluDisk( circleObj, 0.0, 0.05, 12, 1 );
        glPopMatrix();

        glColor3f( fabs( colorR - 0.2 ), fabs( colorG - 0.2 ), fabs( colorB - 0.2) );

        glPushMatrix();
            glTranslatef( 0.14, 0.0, 0.0 );
            glScalef( 0.05, 0.25, 0.25 );
            drawPyramid( false );
        glPopMatrix();

        glPushMatrix();
            glTranslatef( -0.14, 0.0, 0.0 );
            glScalef( 0.05, 0.25, 0.25 );
            drawPyramid( false );
        glPopMatrix();

        glPushMatrix();
            glTranslatef( 0.0, 0.0, 0.3 );
            glScalef( 0.1, 0.5, 0.5 );
            drawPyramid( false );
        glPopMatrix();

    glPopMatrix();
}

void drawStone( double posX, double posZ, double sizeX, double sizeY, double sizeZ, double color )
{
    glColor3f( color, color, color );

    glPushMatrix();
        glTranslatef( posX, sizeY * 3.23 / 2.0, posZ );
        glScalef( sizeX, sizeY, sizeZ );
        glutSolidDodecahedron();
    glPopMatrix();
}