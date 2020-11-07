#ifndef TITLE_H
#define TITLE_H

#define TITLE_PLAYING 0
#define TITLE_END 1

void beginTitleScreeen(void);
void tickTitleScreen(void);
void drawTitleScreen(void);
int getTitleScreenState(void);
void handleTitleInput(void);

#endif
