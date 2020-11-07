#ifndef HOST_HARDWARE_H_
#define HOST_HARDWARE_H_

extern uint16_t *videoBuffer;
uint32_t button_get( void );

#define BUTTONS button_get()

static inline void hardware_video_init( uint16_t *bgcolor )
{
    static bool inited = false;
    extern volatile uint32_t* frame_buffer_init(void);
    extern void background(int height, int width, unsigned short color);

    if( false == inited )
    {
        inited = true;
        (void)frame_buffer_init();
    }
    background( 149, 240, *bgcolor );
}

void waitForVblank(void);

#endif /* HOST_HARDWARE_H_ */
