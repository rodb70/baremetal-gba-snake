#include "title.h"
#include "text.h"
#include "drawing.h"
#include "input.h"

uint8_t state = TITLE_PLAYING;

int getTitleScreenState()
{
    return state;
}

void beginTitleScreeen()
{
    state = TITLE_PLAYING;
    drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COL_LIME);
    drawString("GBA SNAKE", COL_BLACK, 40,40);
}


void handleTitleInput(void)
{
    if (key_curr_state() != key_prev_state())
    {
        if (key_is_down(KEY_START))
        {
            state = TITLE_END;
        }
    }
}

void tickTitleScreen(void)
{
}

void drawTitleScreen(void)
{

}
