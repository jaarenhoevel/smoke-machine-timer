#include <Controller.h>

Controller::Controller(Machine *machine) {
    this->machine = machine;

    this->mode = Controller::Mode::OFF;

    this->interval = 60000;
    this->duration = 5000;

    this->lastUpdate = 0;
    this->lastInterval = 0;

    this->ignoreReady = false;
}

void Controller::setMode(Controller::Mode mode) {
    this->mode = mode;
    this->machine->deactivate();
}

Controller::Mode Controller::getMode() {
    return this->mode;
}

void Controller::setIgnoreReady(bool ignoreReady) {
    this->ignoreReady = ignoreReady;
}

bool Controller::getIgnoreReady() {
    return this->ignoreReady;
}

void Controller::setInterval(uint32_t interval) {
    this->interval = interval;
}

uint32_t Controller::getInterval() {
    return this->interval;
}

void Controller::setDuration(uint32_t duration) {
    this->duration = duration;
}

uint32_t Controller::getDuration() {
    return this->duration;
}

void Controller::process() {
    if (millis() - this->lastUpdate < UPDATE_INTERVAL) return;
    
    switch (this->mode) {
        case Controller::Mode::MAX_OUTPUT:
            this->machine->activate(0, this->ignoreReady);
            break;

        case Controller::Mode::TIMED_OUTPUT:
            if (millis() - this->lastInterval > this->interval && (this->machine->isReady() || this->ignoreReady)) {
                this->machine->activate(this->duration, this->ignoreReady);
                this->lastInterval = millis();
            }
            break;
        
        default:
            break;
    }
}