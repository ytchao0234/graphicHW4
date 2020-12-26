class SunLight
{
    public:
        float position[4];
        float ambient[4];
        float diffuse[4];
        float specular[4];

    SunLight():
        position{ -0.5, 1.0, -0.5, 0.0 },
        ambient { 0.2, 0.2, 0.2, 1.0 },
        diffuse { 0.5, 0.5, 0.5, 1.0 },
        specular{ 0.4, 0.4, 0.4, 1.0 }
    {}
};

void setLight()
{
    glLightfv( GL_LIGHT0, GL_POSITION, mySun->position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, mySun->ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, mySun->diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, mySun->specular );
}