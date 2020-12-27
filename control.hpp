void keyCtrl( unsigned char keyValue, int x, int y )
{
    switch( tolower(keyValue) )
    {
        case ESC:
            exit(0);
            break;

        case SPACE:
            delete myROV;
            myROV = new ROV();
            break;
            
        case 'b':
            if( myROV->toDrawBlock )
                myROV->toDrawBlock = false;
            else
                myROV->toDrawBlock = true;
            break;

        case 'q':
            if( graspFish() )
            {
                myROV->grasping = true;
                myROV->armLength = 1.0;
            }
            else
            {
                pressingKey.emplace_back( keyValue );
            }
            break;
            
        case 'e':
            if( myROV->grasping )myROV->armLength = 1.0;
            myROV->grasping = false;
            initFishBlock( myROV->graspingFish );
            myROV->graspingFish = -1;
            break;

        case 'm':
            sunMove = !sunMove;
            if( !sunMove )
                mySun->angle = 0.0;
                mySun->time = 43200;
            break;

        case 'n':
            myFish->changeColor();
            break;

        case ',':
            sunOn = !sunOn;
            break;
        
        case '.':
            fishOn = !fishOn;
            break;

        case '/':
            armOn = !armOn;
            break;

        case '1':
            viewing = OrthoX;
            break;
            
        case '2':
            viewing = OrthoY;
            break;

        case '3':
            viewing = OrthoZ;
            break;

        case '4':
            viewing = FIRST_VIEW;
            break;
            
        case '5':
            viewing = THIRD_VIEW;
            break;

        case '6':
            viewing = GOD_VIEW;
            break;

        case '7':
            viewing = EACH_VIEW;
            break;

        case '8':
            viewing = MY_VIEW;
            break;

        default: 
            pressingKey.emplace_back( keyValue );
    }
}

void keyUpCtrl( unsigned char keyValue, int posX, int posY )
{
    auto it = find( pressingKey.begin(), pressingKey.end(), keyValue );
    
    if( it != pressingKey.end() )
    {
        if( tolower(*it) == 'q' && myROV->graspingFish == -1 ) myROV->grasping = false;
        pressingKey.erase( it );
    }
}

void mouseCtrl( int button, int state, int posX, int posY )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        myROV->speedUpDown( true );
    }
    else if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        myROV->speedUpDown( false );
    }
}