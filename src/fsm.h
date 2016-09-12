/* 
 * File:   fsm.h
 * Author: isyq
 *
 * Created on September 11, 2016, 12:21 PM
 */

#ifndef FSM_H
#define FSM_H
    
#include "cytypes.h"

    #define MAX_STATE_SIZE          (32)
    #define MAX_EVENT_SIZE          (32)
    #define MAX_TRANSFER_SIZE       (32)
   
    typedef uint8 fsm_state_code;
    typedef uint8 fsm_event_t;

    typedef void (*fsm_state_cb)(void);
    typedef struct {
        fsm_state_code  code;
        fsm_state_cb    action;
    } fsm_state_t;

    typedef struct {
        fsm_state_t curr;
        fsm_event_t event;
        fsm_state_t next;
    } fsm_transfer_t;
    
    void fsm_init(fsm_state_t init_state);
    void fsm_addState(fsm_state_t state);    
    void fsm_addEvent(fsm_event_t event);
    void fsm_addTransfer(fsm_transfer_t transfer);
    void fsm_run(fsm_event_t event);
    

#endif /* FSM_H */

