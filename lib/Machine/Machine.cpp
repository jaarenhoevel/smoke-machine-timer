#include <Machine.h>

Machine::Machine(gpio_num_t triggerPin, gpio_num_t feedbackPin) {
    this->triggerPin = triggerPin;
    this->feedbackPin = feedbackPin;

    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->feedbackPin, INPUT);
    digitalWrite(this->triggerPin, NO_TRIGGER_SIGNAL);
}

bool Machine::isReady() {
    return this->ready;
}

bool Machine::isActive() {
    return this->active;
}

void Machine::process() {
    if (digitalRead(this->feedbackPin) == READY_SIGNAL) {
        this->lastReady = millis();

        this->ready = true;
    } else {
        if (!this->active && millis() - this->lastReady > READY_TIMEOUT) {
            this->ready = false;
        }
    }

    if (this->active && this->activationTimeout > 0 && millis() > this->activationTimeout) {
        this->deactivate();
    }
}

bool Machine::activate(uint32_t duration, bool ignoreReady) {
    if (!ignoreReady && !this->isReady()) return false;
    
    if (duration > 0) this->activationTimeout = millis() + duration;

    digitalWrite(this->triggerPin, TRIGGER_SIGNAL);
    this->active = true;

    return true;
}

bool Machine::deactivate() {
    if (!this->active) return false;

    digitalWrite(this->triggerPin, NO_TRIGGER_SIGNAL);
    this->active = false;

    return true;
}