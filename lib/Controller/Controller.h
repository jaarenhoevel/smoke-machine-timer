#pragma once

#include <Arduino.h>

#include <Machine.h>

#define UPDATE_INTERVAL 100

class Controller {
    public:
        Controller(Machine *machine);

        enum Mode {
            OFF,
            TIMED_OUTPUT,
            MAX_OUTPUT
        };

        void setMode(Mode mode);
        Mode getMode();

        void setIgnoreReady(bool ignoreReady);
        bool getIgnoreReady();

        void setInterval(uint32_t interval);
        uint32_t getInterval();

        void setDuration(uint32_t duration);
        uint32_t getDuration();

        void process();
    private:
        Mode mode = Mode::OFF;
        Machine *machine;

        uint32_t interval, duration, lastUpdate, lastInterval;

        bool ignoreReady = false;
};