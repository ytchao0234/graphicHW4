class SunLight
{
    public:
        float position[4];
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float angle;
        int time;

    SunLight():
        position{ 0.0, 1.0, 0.0, 0.0 },
        ambient { 0.2, 0.2, 0.2, 1.0 },
        diffuse { 0.5, 0.5, 0.5, 1.0 },
        specular{ 0.3, 0.3, 0.3, 1.0 },
        angle( 0.0 ),
        time( 43200 )
    {}

    void move()
    {
        position[0] = cosf( (90.0-angle) * PI / 180.0 );
        position[1] = sinf( (90.0-angle) * PI / 180.0 );

        angle += 0.1;
        time += 24; // 86400 / 3600

        if( angle > 90.0 && angle < 270.0 )
        {
            angle += 0.1;
            time += 24;
        }

        if( angle >= 360.0 )
        {
            angle = 0.0;
        }

        if( time >= 86400 )
        {
            time = 0;
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
        float quadratic;
        float linear;
        float constant;
        enum COLOR { W, R, G, B };
        int color;

    FishLight():
        position{ -75.0, 100.0, -75.0, 1.0 },
        ambient { 0.2, 0.2, 0.2, 1.0 },
        diffuse { 0.6, 0.6, 0.6, 1.0 },
        specular{ 0.4, 0.4, 0.4, 1.0 },
        quadratic( 0.0001 ),
        linear( 0.01 ),
        constant( 1.0 ),
        color(W)
    {}

    void changeColor()
    {
        switch( color )
        {
            case W:
                ambient[0] = 0.2, ambient[1] = 0.0, ambient[2] =  0.0;
                diffuse[0] = 0.3, diffuse[1] = 0.0, diffuse[2] =  0.0;
                specular[0] = 0.4, specular[1] = 0.0, specular[2] =  0.0;
                color = R;
                break;
            case R:
                ambient[0] = 0.0, ambient[1] = 0.2, ambient[2] =  0.0;
                diffuse[0] = 0.0, diffuse[1] = 0.3, diffuse[2] =  0.0;
                specular[0] = 0.0, specular[1] = 0.4, specular[2] =  0.0;
                color = G;
                break;
            case G:
                ambient[0] = 0.0, ambient[1] = 0.0, ambient[2] =  0.2;
                diffuse[0] = 0.0, diffuse[1] = 0.0, diffuse[2] =  0.3;
                specular[0] = 0.0, specular[1] = 0.0, specular[2] =  0.4;
                color = B;
                break;
            case B:
                ambient[0] = 0.2, ambient[1] = 0.2, ambient[2] = 0.2;
                diffuse[0] = 0.3, diffuse[1] = 0.3, diffuse[2] = 0.3;
                specular[0] = 0.4, specular[1] = 0.4, specular[2] = 0.4;
                color = W;
                break;
        }
    }
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
        float angle;
        float quadratic;
        float linear;
        float constant;

    ArmLight():
        position{ myROV->handPos[0], myROV->handPos[1], myROV->handPos[2], 1.0 },
        direction{ myROV->facing[0], myROV->facing[1], myROV->facing[2], 0.0 },
        cutoff   ( 75.0 ),
        diffuse  { 1.0, 1.0, 1.0, 1.0 },
        specular { 1.0, 1.0, 1.0, 1.0 },
        exponent ( 3.0 ),
        angle( 0.0 ),
        quadratic( 0.0000001 ),
        linear( 0.0000001 ),
        constant( 0.5 )
    {}

    void setPos()
    {
        position[0] = myROV->handPos[0];
        position[1] = myROV->handPos[1] + (float)5.0;
        position[2] = myROV->handPos[2];
    }
    
    void setDir()
    {
        direction[0] = myROV->handFacing[0];
        direction[1] = myROV->handFacing[1];
        direction[2] = myROV->handFacing[2];
    }
};

void setLight()
{
    glShadeModel( GL_SMOOTH );
    glEnable( GL_NORMALIZE );
    glEnable( GL_LIGHTING );

    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
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
        glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, myFish->quadratic );
        glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, myFish->linear );
        glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, myFish->constant );
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_POSITION, myFish->position );
        glLightfv( GL_LIGHT1, GL_AMBIENT, noAmbient );
        glLightfv( GL_LIGHT1, GL_DIFFUSE, noDiffuse );
        glLightfv( GL_LIGHT1, GL_SPECULAR, noSpecular );
        glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, myFish->quadratic );
        glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, myFish->linear );
        glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, myFish->constant );
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
        glLightf( GL_LIGHT2, GL_QUADRATIC_ATTENUATION, armLight->quadratic );
        glLightf( GL_LIGHT2, GL_LINEAR_ATTENUATION, armLight->linear );
        glLightf( GL_LIGHT2, GL_CONSTANT_ATTENUATION, armLight->constant );
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_POSITION, armLight->position );
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, armLight->direction );
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 0.0 );
        glLightfv(GL_LIGHT2, GL_DIFFUSE, noDiffuse );
        glLightfv(GL_LIGHT2, GL_SPECULAR, noSpecular );
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0 );
        glLightf( GL_LIGHT2, GL_QUADRATIC_ATTENUATION, armLight->quadratic );
        glLightf( GL_LIGHT2, GL_LINEAR_ATTENUATION, armLight->linear );
        glLightf( GL_LIGHT2, GL_CONSTANT_ATTENUATION, armLight->constant );
    }
    
}