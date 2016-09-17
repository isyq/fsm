/* 
 * File:   fsm.h
 * Author: isyq
 *
 * A Finite-State-Machine(FSM) library.
 *
 */

#ifndef __FSM_H__
#define __FSM_H__
    
#include "cytypes.h"

#define MAX_STATE_SIZE          (8)
#define MAX_EVENT_SIZE          (8)
#define MAX_TRANSITION_SIZE       (8)

typedef uint8 fsm_state_code;			/* State code */
typedef uint8 fsm_event_t;				/* Event code */

typedef void (*fsm_state_cb)(void);		/* State callback function */
typedef struct {
    fsm_state_code  code;
    fsm_state_cb    action;
} fsm_state_t;							/* State type */

typedef struct {
    fsm_state_t curr;
    fsm_event_t event;
    fsm_state_t next;
} fsm_transition_t;						/* transition function type */

typedef struct {
	fsm_state_t      state_list[MAX_STATE_SIZE];
	fsm_event_t      event_list[MAX_EVENT_SIZE];
	fsm_transition_t transition_list[MAX_TRANSITION_SIZE];	
	uint8 			 state_count;
	uint8 		     event_count;
	uint8 			 transition_count;	
	
	fsm_state_code	 curr_state_code;
} fsm_t;								/* State machine */

void   fsm_run(fsm_t* fsm, fsm_event_t event);
void   fsm_addTransition(fsm_t* fsm, fsm_transition_t transition);
void   fsm_addEvent(fsm_t* fsm, fsm_event_t event);
void   fsm_addState(fsm_t* fsm, fsm_state_t state);
void   fsm_dispose(fsm_t* fsm);
fsm_t* fsm_create(fsm_state_t init_state);

    

#endif /* FSM_H */

