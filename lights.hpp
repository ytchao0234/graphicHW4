class SunLight
{
    public:
        float position[4];
        float ambient[4];
        float diffuse[4];
        float specular[4];

    SunLight():
        position{ 0.0, 1.0, 0.0, 0.0 },
        ambient { 0.2, 0.2, 0.2, 1.0 },
        diffuse { 0.3, 0.3, 0.3, 1.0 },
        specular{ 0.3, 0.3, 0.3, 1.0 }
    {}

    void move()
    {
        static float angle = 0.0;

        position[0] = cosf( (90.0-angle) * PI / 180.0 );
        position[1] = sinf( (90.0-angle) * PI / 180.0 );

        angle += 0.1;

        if( angle > 90.0 || angle > 270.0 )
        {
            angle += 0.2;
        }

        if( angle >= 360.0 )
        {
            angle = 0.0;
        }
    }
};

class FishLight
{
    public:
        float position[4];
        float ambient[4];
        float diffuse[4];
        float specular[4];

    FishLight():
        position{ -75.0, 100.0, -75.0, 1.0 },
        ambient { 0.2, 0.2, 0.2, 1.0 },
        diffuse { 0.3, 0.3, 0.3, 1.0 },
        specular{ 0.4, 0.4, 0.4, 1.0 }
    {}
};

class ArmLight
{
    public:
        float position[4];
        float direction[4];
        float cutoff;
        float diffuse[4];
        float specular[4];
        float exponent;

    ArmLight():
        position{ myROV->handPos[0], myROV->handPos[1], myROV->handPos[2], 1.0 },
        direction{ myROV->facing[0], myROV->facing[1], myROV->facing[2], 0.0 },
        cutoff   ( 60.0 ),
        diffuse  { 1.0, 1.0, 1.0, 1.0 },
        specular { 0.6, 0.6, 0.6, 1.0 },
        exponent ( 2.0 )
    {}

    void setPos()
    {
        position[0] = myROV->handPos[0];
        position[1] = myROV->handPos[1];
        position[2] = myROV->handPos[2];
    }

    void setDir()
    {
        direction[0] = myROV->facing[0];
        direction[1] = myROV->facing[1];
        direction[2] = myROV->facing[2];
    }
};

void setLight()
{
    glShadeModel( GL_SMOOTH );
    glEnable( GL_NORMALIZE );
    glEnable( GL_LIGHTING );

    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );

    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_LIGHT2 );

    if( sunOn )
    {
        if( sunMove )
            mySun->move();
        else
        {
            mySun->position[0] = 0.0;
            mySun->position[1] = 1.0;
            mySun->position[2] = 0.0;
        }

        glLightfv( GL_LIGHT0, GL_POSITION, mySun->position );
        glLightfv( GL_LIGHT0, GL_AMBIENT, mySun->ambient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, mySun->diffuse );
        glLightfv( GL_LIGHT0, GL_SPECULAR, mySun->specular );
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_POSITION, mySun->position );
        glLightfv( GL_LIGHT0, GL_AMBIENT, noAmbient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, noDiffuse );
        glLightfv( GL_LIGHT0, GL_SPECULAR, noSpecular );
    }
    

    if( fishOn )
    {
        glLightfv( GL_LIGHT1, GL_POSITION, myFish->position );
        glLightfv( GL_LIGHT1, GL_AMBIENT, myFish->ambient );
        glLightfv( GL_LIGHT1, GL_DIFFUSE, myFish->diffuse );
        glLightfv( GL_LIGHT1, GL_SPECULAR, myFish->specular );
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_POSITION, myFish->position );
        glLightfv( GL_LIGHT1, GL_AMBIENT, noAmbient );
        glLightfv( GL_LIGHT1, GL_DIFFUSE, noDiffuse );
        glLightfv( GL_LIGHT1, GL_SPECULAR, noSpecular );
    }
    

    if( armOn )
    {
        armLight->setPos();
        armLight->setDir();
        glLightfv(GL_LIGHT2, GL_POSITION, armLight->position );
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, armLight->direction );
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, armLight->cutoff );
        glLightfv(GL_LIGHT2, GL_DIFFUSE, armLight->diffuse );
        glLightfv(GL_LIGHT2, GL_SPECULAR, armLight->specular );
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, armLight->exponent );
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_POSITION, armLight->position );
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, armLight->direction );
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 0.0 );
        glLightfv(GL_LIGHT2, GL_DIFFUSE, noDiffuse );
        glLightfv(GL_LIGHT2, GL_SPECULAR, noSpecular );
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0 );
    }
    
}