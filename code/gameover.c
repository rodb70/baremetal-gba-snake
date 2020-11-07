#include "gameover.h"

#include "drawing.h"
#include "text.h"
#include "input.h"
#include "gba.h"
static int state = END_PLAYING;
static int result = 0;
void SetMatchResult(int didPlayerWin)
{
    result = didPlayerWin;
}


void beginGameOverScreen()
{
    state = END_PLAYING;

    if (result)
    {
        drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_BLACK);
        drawString("A WINNER IS YOU", COL_LIME, 25, 25);
        drawString("Press Start To Retry ", COL_LIME, 13, 35);

    }
    else
    {
        drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_RED);
        drawString("You Lost", COL_BLACK, 25, 25);
        drawString("Press Start To Retry ", COL_BLACK, 13, 35);

    }
}

void handleGameOverInput()
{
    if (key_curr_state() != key_prev_state())
    {
        if (key_is_down(KEY_START))
        {
            state = END_RESTART;
        }
    }

}

int getGameOverState()
{
    return state;
}
