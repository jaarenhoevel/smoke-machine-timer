#pragma once

#include <Arduino.h>

#define READY_SIGNAL        LOW
#define READY_TIMEOUT       2000

#define TRIGGER_SIGNAL      HIGH
#define NO_TRIGGER_SIGNAL   LOW

class Machine {
    public:
        Machine(gpio_num_t triggerPin, gpio_num_t feedbackPin);
    
        bool isReady();
        bool isActive();
        bool activate(uint32_t duration = 0, bool ignoreReady = false);
        bool deactivate();

        void process();
    
    private:
        bool ready = false;
        bool active = false;

        uint32_t lastReady = 0;

        uint32_t activationTimeout = 0;

        gpio_num_t triggerPin, feedbackPin;
};