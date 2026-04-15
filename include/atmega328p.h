/**
 * @brief Timer driver for ATmega328P.
 */
#pragma once

#include <stdint.h>
#include "driver/timer/interface.h"

namespace driver 
{
namespace timer
{
/**
 * @brief Timer driver for ATmega328P.
 * * 
 * @note Three hardware timers (Timer 0 - Timer 2) are available.
 */
class Atmega328p final : public Interface
{
public:
    /**
     * @brief Constructor.
     * @param[in] timeout_ms The timeout in milliseconds. Must be > 0.
     * @param[in] callback Callback to invoke on timeout. Must not be nullptr.
     * @param[in] startTimer Start the timer immediately (default = false).
     */
    explicit Atmega328p(uint32_t timeout_ms, timer_callback_t callback, 
                        bool startTimer = false) noexcept;

    ~Atmega328p() noexcept override;

    // --- Interface Overrides ---

    /** @brief Motsvarar valideringen i timer_new. */
    bool isInitialized() const noexcept; 

    bool isEnabled() const noexcept override;
    
    uint32_t getTimeoutMs() const noexcept override;
    
    void setTimeoutMs(uint32_t timeout_ms) noexcept override;

    void start() noexcept override;

    void stop() noexcept override;

    void toggle() noexcept override;

    /** @brief Stoppar timern och nollställer räknaren. */
    void reset() noexcept override;

    /** @brief Nollställer räknaren och startar om timern. */
    void restart() noexcept override;

    // --- Specifika för denna implementation ---

    /** @brief Kontrollerar om timern har gått ut. */
    bool hasTimedOut() const noexcept;

    /** @brief Anropas från ISR för att köra callbacken. */
    void handleCallback() noexcept;

    
    Atmega328p()                               = delete;
    Atmega328p(const Atmega328p&)            = delete;
    Atmega328p(Atmega328p&&)                 = delete;
    Atmega328p& operator=(const Atmega328p&) = delete;
    Atmega328p& operator=(Atmega328p&&)      = delete;

private:
    struct Hardware; // Opaque pekar-struktur till registren
    Hardware* _hw;
    
    uint32_t _timeout_ms;
    uint32_t _current_count;
    timer_callback_t _callback;
    bool _is_enabled;
    bool _initialized;

    
    void setupHardware() noexcept;
};
} // namespace timer
} // namespace driver
