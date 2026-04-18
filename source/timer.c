#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "timer.h"

#define MAX_TIMERS 3

// kanske behöver lägga till mer variabler senare i min struct för att göra mer saker tex timer_start_tick
//eller liknande.

struct timer {

    uint32_t timeout_ms;      // För att veta hur ofta den ska köras (t.ex. 100)
    timer_callback_t callback; // För att spara pekaren till funktionen som ska köras
    bool is_enabled;           // För att veta om timern just nu tickar eller är av
    bool in_use;               // För att hålla koll på om denna plats i poolen (1-3) är upptagen
    uint32_t elapsed_ms;       // För att nollställa timer.
};
  

/**logken hur timer_new funktion skall användas och Returnera NULL om:

    - Timeouten är ogiltig.
   - Callback saknas.
   - Inga timerkretsar finns tillgängliga (resursbrist).

    */



// Gör en lista med 3 av min timer struct utanför timer_new funktion


static struct timer timer_pool[3];


// här börjar all logik alla funktioner får värden och pekare osv
timer_t* timer_new(uint32_t timeout_ms, timer_callback_t callback) {

    if (timeout_ms == 0 ) {

        return NULL;  // includa #include <stddef.h> för att få med NULL 
    } 

    if (callback == NULL) {

        return NULL;
    }


for (int i = 0; i < MAX_TIMERS; i++) { // DEFINE MAX_TIMER == 3
    if (timer_pool[i].in_use == false) { // in_use är en bool så den tittar är i true eller false om false gör detta

        timer_pool[i].in_use = true; // NU ANVÄNDER är den inte ledig längre

        // leta rätt på rätt variabel i listen och sätt värderna 
        timer_pool[i].timeout_ms = timeout_ms; // Spara tiden (t.ex. 100)
        timer_pool[i].callback = callback;     // Spara funktionen (t.ex. blinka_led)
        timer_pool[i].is_enabled = false;      // Den ska vara avstängd tills man kör timer_start
        timer_pool[i].elapsed_ms = 0;          // Nollställ räknaren
        
        return &timer_pool[i]; // 
    }

}


// Om vi hamnar HÄR betyder det att vi kollat alla 3 platser 
// och alla var upptagna (in_use == true).
return NULL;

}



// en funktion so msak kunna ta bort en timer och

//vi retunerar en dubbel pekare så när vi skapar en timer får vi en pekeare sedan vill vi peka på den pekaren vi
//fick för att kunna radera den coh nollställa.

void timer_delete(timer_t** self) {
    //  Finns det en pekare att ta bort?
    if (self == NULL || *self == NULL) {
        return; // Om inte gör ingenting
    }

    // När en timer tas bort ska dess timerkrets bli tillgänglig igen det gör jag här.

    /** self är nu pekaren man får när man skapar en timer 
     * så nu pekar jag på den pekaren man vill ta bort med funkntioen timer_delete 
     * och säter in use till false eftersom den är nu ledig 
     * och is_enable false från true för nu tar vi bort 
     * sen sätter vi pekearen till NULL och nmollställer så vi kan få en ny pekaere senare osv..
     */

    (*self)->in_use = false;
    (*self)->is_enabled = false;
    (*self)->elapsed_ms = 0; // sen kan vi nollställa räknaren eftersom vi vill starta på 0 nästa timer.


    // sätter pekaren till NULL NollställeR!
    *self = NULL;
}
   
  // en funktion som kollar vilken timer so är på eller av för att tex styra logiken för LED 
  //enkel logik man får bara true eller false 
  //i main sedan kan man skriva if timer_is_enable == true tänd LED
  //eller typ if timer_is_enable == false släck LED

bool timer_is_enabled(const timer_t* self) {

    if (self == NULL) {
        return false;
    }

    // Skicka bara tillbaka värdet (true eller false).
   
    return self->is_enabled;
}

  // Funktion som ska kunna starta timen om redan är start gör inget 
void timer_start(timer_t* self) {

    if(self == NULL) {
        return;
    }

    self ->is_enabled = true; // -> == gå till adressen och titta inuti 

}
// Funktion som ska kunna stoppa timern UTAN ATT NOLSTÄLLA TIMERN
void timer_stop(timer_t* self) {
  
    if (self == NULL) {
        return;
    }

    self ->is_enabled = false;
}

// funktion som ska kunna toggla av och på
void timer_toggle(timer_t* self) {
    if(self == NULL) {
        return; 
    }
    self->is_enabled = !self->is_enabled; // inverteraar bytter bara håll eller aa togglar
}

// Funktion som ska reserta timern men inte starta igen
void timer_restart(timer_t* self) {
    if (self == NULL) {
        return;
    }

    self->elapsed_ms = 0;
    self->is_enabled = true; //säkerhet ifall den är avstängd 
}

//timer_restart() nollställer räknaren och startar om timern.

void timer_reset(timer_t* self) {
    if (self == NULL) return;

    self->elapsed_ms = 0;
    self->is_enabled = false; 
}

// funktionen skall ge timern i ms
uint32_t timer_timeout_ms(const timer_t* self) {
    if (self == NULL) return 0;
    return self->timeout_ms;
}

//Funktionen skall sätta en ny timeout
void timer_set_timeout_ms(timer_t* self, uint32_t timeout_ms) {
    if (self == NULL || timeout_ms == 0) return;
    self->timeout_ms = timeout_ms;
    self->elapsed_ms = 0;
}

