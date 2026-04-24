#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>

#include "timer.h"
#include "gpio.h"
#include "timer_hw.h"

/* --- Konstanter --- */
#define LED_PIN_ID 9  
#define BTN_PIN_ID 7 
#define BLINK_DELAY 100

/* --- mina PEKARE --- */
static timer_t* led_timer_ptr = NULL;
static gpio_t* led_gpio_ptr = NULL;
static gpio_t* btn_gpio_ptr = NULL;

/**

* @brief Callback som körs var 100:e ms.

* Denna funktion bor i main.c eftersom det är här vi bestämmer

* vad som ska hända när just denna timer går ut.

*/

void led_toggle(void) {


if (timer_is_enabled(led_timer_ptr)) {

gpio_toggle(led_gpio_ptr);

}

}


int main(void) {


led_gpio_ptr = gpio_new(LED_PIN_ID, GPIO_DIRECTION_OUTPUT, NULL);

btn_gpio_ptr = gpio_new(BTN_PIN_ID, GPIO_DIRECTION_INPUT_PULLUP, NULL);

timer_hw_init();

led_timer_ptr = timer_new(BLINK_DELAY, led_toggle);

if (led_timer_ptr == NULL) {

while(1);

}

timer_start(led_timer_ptr);

bool last_btn_state = true; 

while (1) {
    bool current_btn_state = gpio_read(btn_gpio_ptr);

    if (last_btn_state == true && current_btn_state == false) {
        
    
        timer_toggle(led_timer_ptr);

        if (!timer_is_enabled(led_timer_ptr)) {
            gpio_write(led_gpio_ptr, false); 
        }
        
       
        _delay_ms(50); 
    }

    last_btn_state = current_btn_state;
}

while (1) {

    
}

// Läs av knappen. Eftersom Pull-up är den FALSE när jag trycker.

if (gpio_read(btn_gpio_ptr) == false) {

timer_toggle(led_timer_ptr);


if (!timer_is_enabled(led_timer_ptr)) {

gpio_write(led_gpio_ptr, false);

}


return 0;

}


}


