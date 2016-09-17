#include <stdio.h>
#include <stdlib.h>
#include "../src/fsm.h"
#include "../src/logger.h"


void door_opened(void)
{
    i("The door has opened...\r\n");
}

void door_closed(void)
{
    i("The door has closed...\r\n");
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

void init_door_fsm(fsm_t* fsm)
{
    fsm_addState(fsm, state_opened);
    fsm_addState(fsm, state_closed);
    
    fsm_addEvent(fsm, (fsm_event_t)DOOR_EVENT_OPEN);
    fsm_addEvent(fsm, (fsm_event_t)DOOR_EVENT_CLOSE);
    
    fsm_transition_t door_state_transition_list[] = {
        {state_closed, DOOR_EVENT_OPEN,  state_opened},
        {state_opened, DOOR_EVENT_CLOSE, state_closed},
    };
    
    uint8 door_state_transition_list_count = sizeof(door_state_transition_list) / sizeof(fsm_transition_t);
    uint8 i;
    for (i = 0; i < door_state_transition_list_count; i++) {
        fsm_addTransition(fsm, door_state_transition_list[i]);    
    }
}

int main(void) 
{
    CyGlobalIntEnable;
    
    logger_start(LOGGER_LEVEL_DEBUG, UART_BAUD_RATE_115200);

    fsm_t* fsm = fsm_create(state_closed);	
    init_door_fsm(fsm);
    
    fsm_run(fsm, DOOR_EVENT_OPEN);
    fsm_run(fsm, DOOR_EVENT_CLOSE);
    fsm_run(fsm, DOOR_EVENT_OPEN);
    fsm_run(fsm, DOOR_EVENT_OPEN);
    fsm_run(fsm, DOOR_EVENT_OPEN);
    
    while (1);
}

