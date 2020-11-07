#ifndef GAME_H
#define GAME_H 1

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

#define COL_BLACK   0x0000
#define COL_RED     0x001F
#define COL_LIME    0x03E0
#define COL_YELLOW  0x03FF
#define COL_BLUE    0x7C00
#define COL_MAG     0x7C1F
#define COL_CYAN    0x7FE0
#define COL_WHITE   0x7FFF

#define NUM_CELLS_X 22
#define NUM_CELLS_Y 14
#define SIZE_CELL 10
#define SIZE_FRAME 2
#define SIZE_PADDING 8

#define STATE_PLAYING 0
#define STATE_WON 1
#define STATE_LOST 2

int getGameState(void);
int getFinalScore(void);
void tickAndDrawGame(void);
void restartGame(void);

void handleGameInput();

uint8_t getCellValue(int x, int y);
void setCellValue(int x, int y, uint8_t value);

#endif
