/* 
 * File:   fsm.h
 * Author: isyq
 *
 * An easy FSM(Finite state machine) library.
 */

#include <stdlib.h>
#include <string.h>
#include "fsm.h"

#include "./logger.h"

/*******************************************************************************
* Function Name: fsm_create
********************************************************************************
*
* Summary:
*  Create a new finite state machine instant.
*
* Parameters:
*  init_state:  initialized state.
*
* Returns:
*  fsm_t: pointer to the fsm.
*
*******************************************************************************/
fsm_t* fsm_create(fsm_state_t init_state)
{
    /* Assign memory */
    fsm_t* fsm = (fsm_t* )calloc(1, sizeof(fsm_t));
    if (fsm == NULL) {
        i("Insufficient memory.\r\n");
        return NULL;   
    }
    
    /* Set zero */
    memset(fsm->state_list,      0, MAX_STATE_SIZE);
    memset(fsm->event_list,      0, MAX_EVENT_SIZE);
    memset(fsm->transition_list, 0, MAX_TRANSITION_SIZE);
    fsm->state_count        = 0;
    fsm->event_count        = 0;
    fsm->transition_count   = 0;

    fsm->curr_state_code    = init_state.code;
    
    return fsm;
}

/*******************************************************************************
* Function Name: fsm_dispose
********************************************************************************
*
* Summary:
*  Dispose the finite state machine.
*
* Parameters:
*  fsm:  pointer to the fsm.
*
* Returns:
*  None.
*
*******************************************************************************/
void fsm_dispose(fsm_t* fsm)
{
    if (fsm == NULL) {
        return;
    }
    
    free(fsm);
    fsm = NULL;
}

/*******************************************************************************
* Function Name: fsm_addState
********************************************************************************
*
* Summary:
*  Add a state to state machine.
*
* Parameters:
*  fsm:  pointer to the fsm.
*  state: state.
*
* Returns:
*  None.
*
*******************************************************************************/
void fsm_addState(fsm_t* fsm, fsm_state_t state)
{
    if (fsm->state_count > MAX_STATE_SIZE) {
        return;
    }
    
    fsm->state_list[fsm->state_count] = state;
    fsm->state_count++;
}

/*******************************************************************************
* Function Name: fsm_addEvent
********************************************************************************
*
* Summary:
*  Add a event to state machine.
*
* Parameters:
*  fsm:  pointer to the fsm.
*  event: event.
*
* Returns:
*  None.
*
*******************************************************************************/
void fsm_addEvent(fsm_t* fsm, fsm_event_t event)
{
    if (fsm->event_count > MAX_EVENT_SIZE) {
        return;
    }
    
    fsm->event_list[fsm->event_count] = event;
    fsm->event_count++;
}

/*******************************************************************************
* Function Name: fsm_addTransition
********************************************************************************
*
* Summary:
*  Add a tranfer to state machine.
*
* Parameters:
*  fsm:  pointer to the fsm.
*  transition: transition function.
*
* Returns:
*  None.
*
*******************************************************************************/
void fsm_addTransition(fsm_t* fsm, fsm_transition_t transition)
{
    if (fsm->transition_count > MAX_TRANSITION_SIZE) {
        return;
    }
    
    fsm->transition_list[fsm->transition_count] = transition;
    fsm->transition_count++;
}

/*******************************************************************************
* Function Name: fsm_run
********************************************************************************
*
* Summary:
*  Process finite state machine events.
*
* Parameters:
*  fsm:  pointer to the fsm.
*  event: event.
*
* Returns:
*  None.
*
*******************************************************************************/
void fsm_run(fsm_t* fsm, fsm_event_t event)
{
    uint8 i;
    for (i = 0; i < fsm->transition_count; i++) {
        if (event == fsm->transition_list[i].event) {
            if (fsm->curr_state_code == fsm->transition_list[i].curr.code) {
                fsm->transition_list[i].next.action();
                fsm->curr_state_code = fsm->transition_list[i].next.code;
            }
            else {
                i("Invalid state.\r\n");
            }
            
            return;
        }
    }
    if (i == fsm->transition_count) {
        i("Invalid event.\r\n");
    }    
}