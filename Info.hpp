class Info
{
    public:
        vector<string> infos;
        int width;
        int height;
        double initX;
        double initY;
        int lines;
        double step;
        bool toDrawMap;

    Info(): width( windowWidth / 2 ),
            height( windowHeight / 2 ),
            initX( 15.0 ),
            initY( 15.0 ),
            lines( 1 ),
            step( 18.0 ),
            toDrawMap( true )
    {}


    Info( int w, int h ): width( w ),
                          height( h ),
                          initX( 15.0 ),
                          initY( 15.0 ),
                          lines( 1 ),
                          step( 18.0 ),
                          toDrawMap( false )
    {}

    void showInfo();
    void drawBackground();
    void drawText();
    void drawMap();
};

void Info::showInfo()
{
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D( 0.0, (double)width, 0.0, (double)height );

        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();

            // ---------------------------------------------------------

            lines = 1;
            
            infos.clear();
            drawText();
            if( toDrawMap ) drawMap();
            drawBackground();

            // ---------------------------------------------------------

        glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
}

void Info::drawBackground()
{
    glColor3f( 0.2, 0.2, 0.2 );

    glBegin( GL_POLYGON );

        glVertex2f( 0, height );
        glVertex2f( 0, 0 );
        glVertex2f( width, 0 );
        glVertex2f( width, height );

    glEnd();
}

void Info::drawText()
{
    glColor3f( 1.0, 1.0, 1.0 );

    glRasterPos2i( initX, height - initY );

    // ---------------------------------------

    infos.emplace_back( "Info: " );

    string strData;

    string position = "Position: ";
    strData = to_string( myROV->pos[0] );
    position += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->pos[1] );
    position += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->pos[2] );
    position += strData.substr( 0, strData.find( "." ) + 2 );
    infos.emplace_back( position );

    string angle = "Angle: ";
    strData = to_string( myROV->rotation[0] );
    angle += strData.substr( 0, strData.find( "." ) + 2 );
    infos.emplace_back( angle );

    string facing = "Facing: ";
    strData = to_string( myROV->facing[0] );
    facing += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->facing[1] );
    facing += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->facing[2] );
    facing += strData.substr( 0, strData.find( "." ) + 2 );
    infos.emplace_back( facing );

    string speed = "Speed: ";
    strData = to_string( myROV->speed[0] );
    speed += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->speed[1] );
    speed += strData.substr( 0, strData.find( "." ) + 2 ) + ", ";
    strData = to_string( myROV->speed[2] );
    speed += strData.substr( 0, strData.find( "." ) + 2 );
    infos.emplace_back( speed );

    string maxSpeed = "Max Speed: ";
    strData = to_string( myROV->maxSpeed );
    maxSpeed += strData.substr( 0, strData.find( "." ) + 2 );
    infos.emplace_back( maxSpeed );

    // ---------------------------------------

    void *font = GLUT_BITMAP_9_BY_15;

    for( auto const str: infos )
    {
        for( auto const text: str )
        {
            glutBitmapCharacter( font, text );
        }

        glRasterPos2i( initX + 20.0, height - (initY + lines * step ) );
        lines++;
    }
}

void Info::drawMap()
{
    // origin point
    glColor3f( 1.0, 1.0, 1.0 );
    glPointSize( 5.0 );

    glBegin( GL_POINTS );
        glVertex2f( width / 2.0, ( height - lines * step ) / 2.0 );
    glEnd();

    // x-axis
    glColor3f( 0.0, 1.0, 1.0 );
    glBegin( GL_LINES );
        glVertex2f( width / 2.0, (height - lines * step) / 2.0 );
        glVertex2f( width / 2.0, height - lines * step );
    glEnd();

    // x-axis
    glColor3f( 1.0, 1.0, 0.0 );
    glBegin( GL_LINES );
        glVertex2f( lines * step / 2.0, (height - lines * step) / 2.0 );
        glVertex2f( width / 2.0, (height - lines * step) / 2.0 );
    glEnd();

    // ROV
    double x = (myROV->pos[0] - myROV->limitPos[0].first) / ( myROV->limitPos[0].second - myROV->limitPos[0].first );
    double z = (myROV->pos[2] - myROV->limitPos[2].first) / ( myROV->limitPos[2].second - myROV->limitPos[2].first );

    double facingx = (myROV->pos[0] + myROV->facing[0] * 50.0 - myROV->limitPos[0].first) / ( myROV->limitPos[0].second - myROV->limitPos[0].first );
    double facingz = (myROV->pos[2] + myROV->facing[2] * 50.0 - myROV->limitPos[2].first) / ( myROV->limitPos[2].second - myROV->limitPos[2].first );

    glColor3f( 1.0, 0.0, 0.0 );
    glPointSize( 5.0 );
    glBegin( GL_POINTS );
        glVertex2d( (width - lines * step / 2.0) - (width - lines * step) * x, (height - lines * step) * z );
    glEnd();

    glColor3f( 1.0, 0.5, 0.0 );
    glBegin( GL_LINES );
        glVertex2d( (width - lines * step / 2.0) - (width - lines * step) * x, (height - lines * step) * z );
        glVertex2d( (width - lines * step / 2.0) - (width - lines * step) * facingx, (height - lines * step) * facingz );
    glEnd();

    // fishes
    glColor3f( 1.0, 0.0, 1.0 );
    glPointSize( 5.0 );

    for( auto fish : fishPara )
    {
        double x = (fish[0] - myROV->limitPos[0].first) / ( myROV->limitPos[0].second - myROV->limitPos[0].first );
        double z = (fish[2] - myROV->limitPos[2].first) / ( myROV->limitPos[2].second - myROV->limitPos[2].first );

        glBegin( GL_POINTS );
            glVertex2d( (width - lines * step / 2.0) - (width - lines * step) * x, (height - lines * step) * z );
        glEnd();
    }

    // stones
    glColor3f( 0.3, 0.3, 0.3 );
    glPointSize( 5.0 );

    for( auto stone : stonePara )
    {
        double x = (stone[0] - myROV->limitPos[0].first) / ( myROV->limitPos[0].second - myROV->limitPos[0].first );
        double z = (stone[1] - myROV->limitPos[2].first) / ( myROV->limitPos[2].second - myROV->limitPos[2].first );

        glBegin( GL_POINTS );
            glVertex2d( (width - lines * step / 2.0) - (width - lines * step) * x, (height - lines * step) * z );
        glEnd();
    }

    //background
    glColor3f( 0.0, 0.0, 0.0 );

    glBegin( GL_POLYGON );
        glVertex2f( lines * step / 2.0, height - lines * step );
        glVertex2f( lines * step / 2.0, 0.0 );
        glVertex2f( ( width - lines * step / 2.0 ), 0.0 );
        glVertex2f( ( width - lines * step / 2.0 ), height - lines * step );
    glEnd();
}