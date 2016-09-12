#include <stdio.h>
#include <stdlib.h>
#include "../src/fsm.h"
#include "../src/logger.h"


void door_opened(void)
{
    i("The door has opened...\n");
}

void door_closed(void)
{
    i("The door has closed...\n");
}

typedef enum {
    DOOR_STATE_OPENED,
    DOOR_STATE_CLOSED,
} door_state_t;

fsm_state_t state_opened   = {DOOR_STATE_OPENED,  door_opened};
fsm_state_t state_closed   = {DOOR_STATE_CLOSED,  door_closed};

typedef enum {
    DOOR_EVENT_OPEN,
    DOOR_EVENT_CLOSE, 
} door_event_t;

void init_door_fsm(void)
{
    fsm_init(state_closed);
    
    fsm_addState(state_opened);
    fsm_addState(state_closed);
    
    fsm_addEvent((fsm_event_t) DOOR_EVENT_OPEN);
    fsm_addEvent((fsm_event_t) DOOR_EVENT_CLOSE);
    
    fsm_transfer_t door_state_transfer_list[] = {
        {state_closed, DOOR_EVENT_OPEN, state_opened},
        {state_opened, DOOR_EVENT_CLOSE, state_closed},
    };
    
    uint8 door_state_transfer_list_count = sizeof(door_state_transfer_list) / sizeof(fsm_transfer_t);
    uint8 i;
    for (i = 0; i < door_state_transfer_list_count; i++) {
        fsm_addTransfer(door_state_transfer_list[i]);    
    }
}

int main(void) 
{
    CyGlobalIntEnable;
    
    logger_start(LOGGER_LEVEL_DEBUG, UART_BAUD_RATE_115200);
    i("A demo of finite state machine library.\n");
      
    init_door_fsm();
    
    fsm_run(DOOR_EVENT_OPEN);
    fsm_run(DOOR_EVENT_CLOSE);
    fsm_run(DOOR_EVENT_OPEN);
    fsm_run(DOOR_EVENT_OPEN);
    fsm_run(DOOR_EVENT_OPEN);
    
    while (1);
}

