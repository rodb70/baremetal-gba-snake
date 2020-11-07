#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game.h"
#include <string.h>
#include <assert.h>
#include "input.h"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint16_t tft_fb[ SCREEN_HEIGHT ][ SCREEN_WIDTH ];

} monitor_t;

uint16_t *vid_mem;
uint32_t buttons = ~( 0 );
uint16_t key_cur;
uint16_t key_prev;


static monitor_t monitor = { 0 };
monitor_t *m = &monitor;

int quit_filter(void *userdata, SDL_Event *event)
{
    (void) userdata;

    if( SDL_WINDOWEVENT == event->type )
    {
        if( SDL_WINDOWEVENT_CLOSE == event->window.event )
        {
            exit( 0 );
        }
    }
    else if( SDL_QUIT == event->type )
    {
        exit( 0 );
    }

    return 1;
}

volatile uint16_t* frame_buffer_init(void)
{
    buttons = ~( 0 );
    /* Initialise the SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialise! SDL_Error: %s\n", SDL_GetError() );
        exit( -1 );
    }

    SDL_SetEventFilter( quit_filter, NULL );

    m->window = SDL_CreateWindow( "Donkey Kong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH*3, SCREEN_HEIGHT*3, 0 );
    assert( m->window );

    m->renderer = SDL_CreateRenderer( m->window, -1, SDL_RENDERER_SOFTWARE );
    assert( m->renderer );

    m->texture = SDL_CreateTexture( m->renderer, SDL_PIXELFORMAT_BGR555, SDL_TEXTUREACCESS_STATIC,
                                    SCREEN_WIDTH, SCREEN_HEIGHT );
    assert( m->texture );

    SDL_SetTextureBlendMode( m->texture, SDL_BLENDMODE_BLEND );

    vid_mem = &m->tft_fb[0][0];

    return (void*) m->tft_fb;
}

int frame_buffer_switch(int offset)
{
    (void) offset;

    int rslt = SDL_UpdateTexture( m->texture, NULL, m->tft_fb, SCREEN_WIDTH * sizeof( uint16_t ));
    assert( 0 == rslt );
    rslt = SDL_RenderClear( m->renderer );
    assert( 0 == rslt );

    /* Update the renderer with the texture containing the rendered image */
    rslt = SDL_RenderCopy( m->renderer, m->texture, NULL, NULL );
    assert( 0 == rslt );

    SDL_RenderPresent( m->renderer );

    return 0;
}

uint32_t poll_controller(uint32_t delay)
{
    SDL_Event event;
    uint32_t mask = 0;
    int keyPressed = 0;

    while( SDL_PollEvent( &event ))
    {
        switch( event.key.keysym.sym )
        {
        case SDLK_a :
            mask |= KEY_A;
            break;

        case SDLK_b :
            mask |= KEY_B;
            break;

        case SDLK_q :
            mask |= KEY_L;
            break;

        case SDLK_w :
            mask |= KEY_R;
            break;

        case SDLK_SPACE :
            mask |= KEY_SELECT;
            break;

        case SDLK_RETURN2 :
        case SDLK_RETURN :
            mask |= KEY_START;
            break;

        case SDLK_KP_0 :
        case SDLK_0 :
            break;

        case SDLK_RIGHT:
        case SDLK_KP_PLUS:
            mask |= KEY_RIGHT;
            break;

        case SDLK_LEFT:
        case SDLK_KP_MINUS:
            mask |= KEY_LEFT;
            break;

        case SDLK_UP:
            mask |= KEY_UP;
            break;

        case SDLK_DOWN:
            mask |= KEY_DOWN;
            break;

        case SDLK_ESCAPE:
            exit( 1 );
            break;
        }

        switch( event.type )
        {
        case SDL_KEYDOWN:
            keyPressed = 1;
            break;

        case SDL_KEYUP:
            keyPressed = 0;
            break;

        default:
            break;

        }
    }

    if( keyPressed )
    {
        buttons |= mask;
    }
    else
    {
        buttons &= ~( mask );
    }

    SDL_Delay( delay ); /* Sleep for 5 millisecond */

    return buttons;
}

uint16_t key_poll( void )
{
    key_prev = key_cur;
    key_cur = buttons;
    return key_cur;
}

void vsync(void)
{
    poll_controller(16);
    frame_buffer_switch(0);
}
