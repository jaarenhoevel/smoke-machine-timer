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

uint32_t Controller::getTimeUntilNextEvent() {
    if (this->mode != Controller::Mode::TIMED_OUTPUT) return 0;

    uint32_t timeSinceLastEvent = millis() - this->lastInterval;

    if (timeSinceLastEvent > this->interval) return 0;

    if (timeSinceLastEvent < this->duration) return this->duration - timeSinceLastEvent;

    return this->interval - timeSinceLastEvent;
}

void Controller::setOutputVolume(uint8_t volume, uint32_t interval) {
    if (volume < 1 || volume > 99) return;

    this->interval = interval;
    this->duration = volume / (MAX_OUPUT_VOLUME * 1.f) * interval;

    if (this->machine->isActive()) this->machine->deactivate();
}

uint8_t Controller::getOutputVolume() {
    return (1.f * this->duration / this->interval) * MAX_OUPUT_VOLUME;
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