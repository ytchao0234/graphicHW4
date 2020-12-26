void changeLookAt( int viewMode )
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    switch( viewMode )
    {
        case OrthoX:
            gluLookAt( 1.0, 0.0, 0.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;
        case OrthoY:
            gluLookAt( 0.0, 1.0, 0.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 0.0, 1.0 ); // v up
            break;
        case OrthoZ:
            gluLookAt( 0.0, 0.0, 1.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;
        case FIRST_VIEW:
            gluLookAt( myROV->pos[0] + myROV->facing[0] * 20.0, // eye position
                       myROV->pos[1] + myROV->facing[1] * 20.0,
                       myROV->pos[2] + myROV->facing[2] * 20.0,

                       myROV->pos[0] + myROV->facing[0] * 21.0, // look position
                       myROV->pos[1] + myROV->facing[1] * 21.0,
                       myROV->pos[2] + myROV->facing[2] * 21.0,

                       0.0, 1.0, 0.0 ); // v up
            break;
        case THIRD_VIEW:
            gluLookAt( myROV->pos[0] + myROV->facing[0] * -120.0, // eye position
                       myROV->pos[1] + myROV->facing[1] * -120.0 + 50.0,
                       myROV->pos[2] + myROV->facing[2] * -120.0,

                       myROV->pos[0], myROV->pos[1], myROV->pos[2], // look position
                       
                       0.0, 1.0, 0.0 ); // v up
            break;
        case GOD_VIEW:
            gluLookAt( -75.0, 120.0, -120.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;

        default: break;
    }
}

void makeProjection( int viewMode )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    float w =  (float)windowWidth;
    float h =  (float)windowHeight;

    if( viewMode <= OrthoZ ) // OrthoX, OrthoY, OrthoZ
    {
        if( w > h )
        {
            glOrtho(-orthoNum, orthoNum,
                    -orthoNum * h/w, orthoNum * h/w,
                    -orthoNum, orthoNum);
        }
        else
        {
            glOrtho(-orthoNum * w/h, orthoNum * w/h,
                    -orthoNum, orthoNum, 
                    -orthoNum, orthoNum);
        }
    }
    else // FIRST_VIEW, THIRD_VIEW, GOD_VIEW
    {
        gluPerspective( perspectiveEye, w/h, perspectiveNear, perspectiveFar);
    }

    glMatrixMode( GL_MODELVIEW );
}

void zoomIn( bool forOrho )
{
    if( forOrho )
    {
        orthoNum -= 10.0;
        if( orthoNum < 300.0 ) orthoNum = 300.0;
    }
    else
    {
        perspectiveEye -= 1.0;
        if( perspectiveEye < 45.0 ) perspectiveEye = 45.0;
    }
}

void zoomOut( bool forOrho )
{
    if( forOrho )
    {
        orthoNum += 10.0;
        if( orthoNum > 700.0 ) orthoNum = 700.0;
    }
    else
    {
        perspectiveEye += 1.0;
        if( perspectiveEye > 90.0 ) perspectiveEye = 90.0;
    }
}