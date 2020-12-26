#ifndef _INCLUDES
#define _INCLUDES
    #include "includes.h"
#endif

#ifndef _FUNCTIONS
#define _FUNCTIONS
    #include "functions.h"
#endif

int main(int argc, char **argv)
{
    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowPosition( ( SCREEN_WIDTH  - windowWidth  ) / 2, 
                            ( SCREEN_HEIGHT - windowHeight ) / 2 );
    
    glutInitWindowSize( windowWidth, windowHeight );
    glutCreateWindow( "My ROV" );

    // glShadeModel( GL_SMOOTH );
    glutIgnoreKeyRepeat( 1 );

    initWindow();

    glutDisplayFunc( display );

    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyCtrl );
    glutKeyboardUpFunc( keyUpCtrl );
    glutMouseFunc( mouseCtrl );

    glutIdleFunc( display );

    glutMainLoop();

    return 0;
}