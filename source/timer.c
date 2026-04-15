#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

#define MAX_TIMERS 3


struct timer {
    uint32_t timeout_ms;
    uint32_t current_count;
    timer_callback_t callback;
    bool enabled;
    bool in_use;
};




//en funktion som ställer in register


static void timer_init(void) {

    // Sätt CTC mode (Clear Timer on Compare Match)
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler 64
    
    OCR1A = 249;
    
    TIMSK1 |= (1 << OCIE1A);
    
    sei();
}




static timer_t timer_pool[MAX_TIMERS];



timer_t* timer_new(uint32_t timeout_ms, timer_callback_t callback) {
    
    if (timeout_ms == 0 || callback == NULL) {
        return NULL;
    }

    // Leta efter ledig plats (resurshantering)
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (!timer_pool[i].in_use) {
            timer_pool[i].timeout_ms = timeout_ms;
            timer_pool[i].callback = callback;
            timer_pool[i].current_count = 0;
            timer_pool[i].enabled = false;
            timer_pool[i].in_use = true; 
            return &timer_pool[i];
        }
    }

    
    return NULL;
}


void timer_delete(timer_t** self) {
    if (self == NULL || *self == NULL) return;

    (*self)->in_use = false;   
    (*self)->enabled = false;
    *self = NULL;              
}


void timer_restart(timer_t* self) {
    if (self == NULL) return;
    self->current_count = 0;   
    self->enabled = true;      
}
