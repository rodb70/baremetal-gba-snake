#ifndef HOST_HARDWARE_H_
#define HOST_HARDWARE_H_
#include <stdbool.h>
#include <stdint.h>

extern uint16_t *vid_mem;

static inline void HardwareInit( void )
{
    static bool inited = false;
    extern volatile uint16_t* frame_buffer_init(void);

    if( false == inited )
    {
        inited = true;
        (void)frame_buffer_init();
    }
}

void vsync(void);
uint16_t key_poll( void );

#endif /* HOST_HARDWARE_H_ */
