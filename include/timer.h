#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include <stdint.h>

/** * @brief Opaque structure för timern.
 * Detaljerna är dolda i timer.c (Inkapsling).
 */
typedef struct timer timer_t;

/** @brief Funktionspekare för callbacks. */
typedef void (*timer_callback_t)(void);

// --- API-Funktioner ---

// Skapar en ny timer (max 3 st)
timer_t* timer_new(uint32_t timeout_ms, timer_callback_t callback);

// Tar bort en timer och nollar pekaren
void timer_delete(timer_t** self);

// Status och kontroll
bool timer_is_enabled(const timer_t* self);
void timer_start(timer_t* self);
void timer_stop(timer_t* self);
void timer_toggle(timer_t* self);

// Hantering av timeout
uint32_t timer_timeout_ms(const timer_t* self);
void timer_set_timeout_ms(timer_t* self, uint32_t timeout_ms);

#endif /* TIMER_H_ */



/* Gällande funktionerna ovan:

    timer_new() skapar en ny timer om:
        Given timeout är giltig (0U < timeout_ms).
        Callback finns (NULL != callback).
        En timerkrets finns tillgänglig.
    timer_delete() tar bort en timer och frigör allokerade resurser om:
        Timern är giltig ((NULL != self) && (NULL != *self)).
        När en timer tas bort ska dess timerkrets bli tillgänglig igen.
    timer_is_enabled() indikerar ifall timern är på eller inte:
        "Enabled" betyder att timern är igång och kan generera callbacks.
    timer_start() startar timern (om redan igång görs ingenting).
    timer_stop() stoppar timern (utan att nollställa räknaren).
    timer_toggle() togglar timern.
    timer_reset() stoppar timern och nollställer räknaren.
    timer_restart() nollställer räknaren och startar om timern.
    timer_timeout_ms() ger timerns timeout i ms.
    timer_set_timeout_ms() sätter ny timeout om denna är giltig (0U < timeout_ms):
        Om timeouten är ogiltig görs ingenting.
        Om timern är igång och timeout ändras så startar perioden om från 0.
*/