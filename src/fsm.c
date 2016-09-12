/* 
 * File:   fsm.h
 * Author: isyq
 *
 * Created on September 11, 2016, 12:21 PM
 */

#include <stdlib.h>
#include <string.h>
#include "fsm.h"

static fsm_state_t      state_list[MAX_STATE_SIZE];
static fsm_event_t      event_list[MAX_EVENT_SIZE];
static fsm_transfer_t   transfer_list[MAX_TRANSFER_SIZE];
static uint8 state_count;
static uint8 event_count;
static uint8 transfer_count;

static fsm_state_code current_state_code;

void fsm_init(fsm_state_t init_state)
{
    memset(state_list, 0, MAX_STATE_SIZE);
    memset(event_list, 0, MAX_EVENT_SIZE);
    
    state_count = 0;
    event_count = 0;
    
    current_state_code = init_state.code;
}

void fsm_addState(fsm_state_t state)
{
    if (state_count > MAX_STATE_SIZE) {
        return;
    }
    
    state_list[state_count] = state;
    state_count++;
}

void fsm_addEvent(fsm_event_t event)
{
    if (event_count > MAX_EVENT_SIZE) {
        return;
    }
    
    event_list[event_count] = event;
    event_count++;
}

void fsm_addTransfer(fsm_transfer_t transfer)
{
    if (transfer_count > MAX_TRANSFER_SIZE) {
        return;
    }
    
    transfer_list[transfer_count] = transfer;
    transfer_count++;
}

void fsm_run(fsm_event_t event)
{
    uint8 i;
    for (i = 0; i < transfer_count; i++) {
        if (event == transfer_list[i].event && current_state_code == transfer_list[i].curr.code) {
            transfer_list[i].next.action();
            current_state_code = transfer_list[i].next.code;

            return;
        }
    }
}