// First demo. You are not expected to understand it
// (don't spend too much time trying and read on).
// But if you do understand (as a newbie): wow!

#include "gba.h"
#include "game.h"
#include "title.h"
#include "text.h"
#include "gameover.h"
#include "input.h"

#define STATE_JUST_LAUNCHED 0
#define STATE_TITLE 1
#define STATE_GAME 2
#define STATE_END 3

uint8_t AppState = STATE_JUST_LAUNCHED;
uint8_t TargetState = STATE_TITLE;

int main()
{
    HardwareInit();

    while( 1 )
    {
        //this is awful, but it works for snake
        for( int i = 0; i < 4; ++i )
        {
            vsync();
            key_poll();
            switch( AppState )
            {
            case STATE_TITLE:
                handleTitleInput();
                break;
            case STATE_GAME:
                handleGameInput();
                break;
            case STATE_END:
                handleGameOverInput();
                break;
            }
        }

        if( TargetState == AppState )
        {
            switch( AppState )
            {
            case STATE_TITLE:
            {
                tickTitleScreen();
                int state = getTitleScreenState();

                if( state == TITLE_END )
                {
                    TargetState = STATE_GAME;
                }
            }
                break;
            case STATE_GAME:
            {
                int gameState = getGameState();
                if( gameState == STATE_WON )
                {
                    TargetState = STATE_END;
                }
                else if( gameState == STATE_LOST )
                {
                    TargetState = STATE_END;
                }
                else
                {
                    tickAndDrawGame();
                }
            }
                break;
            case STATE_END:
            {
                int gameOverState = getGameOverState();
                if( gameOverState == END_RESTART )
                {
                    TargetState = STATE_GAME;
                }
            }
                break;

            }
        }
        else
        {
            AppState = TargetState;
            switch( AppState )
            {
            case STATE_TITLE:
                beginTitleScreeen();
                break;
            case STATE_GAME:
                restartGame();
                break;
            case STATE_END:
                beginGameOverScreen();
                break;
            default:
                break;
            }
        }
    }

    return 0;
}
