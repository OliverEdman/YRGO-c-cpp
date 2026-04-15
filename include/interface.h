/**
 * @brief Timer interface.
 */
#pragma once

#include <stdint.h>

namespace driver {
namespace timer {

/** * @brief Alias för timer-callbacks. 
 */
using timer_callback_t = void (*)(void);

/**
 * @brief Interface för Timer-drivrutiner.
 * Detta definierar kontraktet som alla timers måste följa.
 */
class Interface {
public:
    /**
     * @brief Virtuell destruktor. 
     * Motsvarar logiken i timer_delete() för att frigöra resurser.
     */
    virtual ~Interface() = default;

    /**
     * @brief Startar timern (om redan igång görs ingenting).
     */
    virtual void start() = 0;

    /**
     * @brief Stoppar timern (utan att nollställa räknaren).
     */
    virtual void stop() = 0;

    /**
     * @brief Togglar timern (av/på).
     */
    virtual void toggle() = 0;

    /**
     * @brief Stoppar timern och nollställer räknaren.
     */
    virtual void reset() = 0;

    /**
     * @brief Nollställer räknaren och startar om timern.
     */
    virtual void restart() = 0;

    /**
     * @brief Indikerar ifall timern är igång och kan generera callbacks.
     */
    virtual bool isEnabled() const = 0;

    /**
     * @brief Ger timerns nuvarande timeout i ms.
     */
    virtual uint32_t getTimeoutMs() const = 0;

    /**
     * @brief Sätter ny timeout om denna är giltig (> 0).
     * Om timern är igång startar perioden om från 0.
     */
    virtual void setTimeoutMs(uint32_t timeout_ms) = 0;

protected:
    // Vi hindrar direkt instansiering av interfacet genom att göra konstruktorn skyddad
    Interface() = default;
};

} // namespace timer
} // namespace driver
