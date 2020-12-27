vector<float> calNormal( vector<float> p1, vector<float> p2, vector<float> p3, vector<float> p4 )
{
    vector<float> v1 = { p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2] };
    vector<float> v2 = { p3[0] - p4[0], p3[1] - p4[1], p3[2] - p4[2] };

    vector<float> normal = { v1[1] * v2[2] - v1[2] * v2[1],
                             v1[2] * v2[0] - v1[0] * v2[2],
                             v1[0] * v2[1] - v1[1] * v2[0] };

    return normal;
}

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

    const vector<vector<float>> normals = 
    {
        calNormal( points[faces[0][0]], points[faces[0][1]], points[faces[0][1]], points[faces[0][2]]),
        calNormal( points[faces[1][0]], points[faces[1][1]], points[faces[1][1]], points[faces[1][2]]),
        calNormal( points[faces[2][0]], points[faces[2][1]], points[faces[2][1]], points[faces[2][2]]),
        calNormal( points[faces[3][0]], points[faces[3][1]], points[faces[3][1]], points[faces[3][2]]),
        calNormal( points[faces[4][0]], points[faces[4][1]], points[faces[4][1]], points[faces[4][2]]),
        calNormal( points[faces[5][0]], points[faces[5][1]], points[faces[5][1]], points[faces[5][2]])
    };

    int i, j;
    
    for( i = 0; i < 6; ++i )
    {
        glNormal3fv( &(normals[i][0]) );
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

    const vector<vector<float>> upwardNormals =
    {
        calNormal( upwardPoints[upwardFaces[0][0]], upwardPoints[upwardFaces[0][1]], upwardPoints[upwardFaces[0][1]], upwardPoints[upwardFaces[0][2]]),
        calNormal( upwardPoints[upwardFaces[1][0]], upwardPoints[upwardFaces[1][1]], upwardPoints[upwardFaces[1][1]], upwardPoints[upwardFaces[1][2]]),
        calNormal( upwardPoints[upwardFaces[2][0]], upwardPoints[upwardFaces[2][1]], upwardPoints[upwardFaces[2][1]], upwardPoints[upwardFaces[2][2]]),
        calNormal( upwardPoints[upwardFaces[3][0]], upwardPoints[upwardFaces[3][1]], upwardPoints[upwardFaces[3][1]], upwardPoints[upwardFaces[3][2]]),
        calNormal( upwardPoints[upwardFaces[4][0]], upwardPoints[upwardFaces[4][1]], upwardPoints[upwardFaces[4][1]], upwardPoints[upwardFaces[4][2]])
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

    const vector<vector<float>> downwardNormals =
    {
        calNormal( downwardPoints[downwardFaces[0][0]], downwardPoints[downwardFaces[0][1]], downwardPoints[downwardFaces[0][1]], downwardPoints[downwardFaces[0][2]]),
        calNormal( downwardPoints[downwardFaces[1][0]], downwardPoints[downwardFaces[1][1]], downwardPoints[downwardFaces[1][1]], downwardPoints[downwardFaces[1][2]]),
        calNormal( downwardPoints[downwardFaces[2][0]], downwardPoints[downwardFaces[2][1]], downwardPoints[downwardFaces[2][1]], downwardPoints[downwardFaces[2][2]]),
        calNormal( downwardPoints[downwardFaces[3][0]], downwardPoints[downwardFaces[3][1]], downwardPoints[downwardFaces[3][1]], downwardPoints[downwardFaces[3][2]]),
        calNormal( downwardPoints[downwardFaces[4][0]], downwardPoints[downwardFaces[4][1]], downwardPoints[downwardFaces[4][1]], downwardPoints[downwardFaces[4][2]])
    };

    vector<vector<float>> points;
    vector<vector<int>> faces;
    vector<vector<float>> normals;
    int i, j;

    if( upward )
    {
        points.assign( upwardPoints.begin(), upwardPoints.end() );
        faces.assign( upwardFaces.begin(), upwardFaces.end() );
        normals.assign( upwardNormals.begin(), upwardNormals.end() );
    }
    else
    {
        points.assign( downwardPoints.begin(), downwardPoints.end() );
        faces.assign( downwardFaces.begin(), downwardFaces.end() );
        normals.assign( downwardNormals.begin(), downwardNormals.end() );
    }

    for( i = 0; i < 4; ++i )
    {
        glNormal3fv( &(normals[i][0]) );
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

void drawFish( float posX, float posY, float posZ, 
               float angle, float size, 
               float colorR, float colorG, float colorB )
{
    static vector<vector<float>> color;
    color = 
    { 
        { colorR, colorG, colorB, 1.0 },
        { 0.0, 0.0, 0.0, 1.0 },
        { fabsf( colorR - 0.2 ), fabsf( colorG - 0.2 ), fabsf( colorB - 0.2), 1.0 }
    };

    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(color[0][0]) );

    glPushMatrix();

        glTranslatef( posX, posY, posZ );
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glScalef( size, size, size );

        glPushMatrix();
            glScalef( 0.25, 0.6, 1.0 );
            glutSolidCube( 1.0 );
        glPopMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(color[1][0]) );

        glPushMatrix();
            glTranslatef( 0.1251, 0.1, -0.3 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            gluDisk( circleObj, 0.0, 0.05, 12, 1 );
        glPopMatrix();

        glPushMatrix();
            glTranslatef( -0.1251, 0.1, -0.3 );
            glRotatef( -90.0, 0.0, 1.0, 0.0 );
            gluDisk( circleObj, 0.0, 0.05, 12, 1 );
        glPopMatrix();

        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(color[2][0]) );

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

void drawStone( float posX, float posZ, float sizeX, float sizeY, float sizeZ, float stoneColor )
{
    static vector<float> color;
    color = { stoneColor, stoneColor, stoneColor };

    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, &(color[0]) );

    glPushMatrix();
        glTranslatef( posX, sizeY * 3.23 / 2.0, posZ );
        glScalef( sizeX, sizeY, sizeZ );
        glutSolidDodecahedron();
    glPopMatrix();
}

void drawCup( float posX, float posZ, float angle, float size, float colorR, float colorG, float colorB )
{
    static float color[4];
    color[0] = colorR;
    color[1] = colorG;
    color[2] = colorB;

    static float specular[4] = { 0.3, 0.3, 0.3, 1.0 };
    static float shininess = 16.0;

    glPushMatrix();
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

        glTranslatef( posX, size / 2.0 + 2.0, posZ );
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glScalef( size, size, size );
        gluCylinder( cylinder, 2, 3, 5, 12, 3 );
        glPushMatrix();
            glTranslatef( 0.0, 0.0, 0.3 );
            glRotatef( 180.0, 0.0, 1.0, 0.0 );
            gluDisk( circleObj, 0.0, 2, 12, 1 );
        glPopMatrix();
    glPopMatrix();
}
