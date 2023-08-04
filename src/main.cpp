#include <Arduino.h>

#include <Machine.h>
#include <Controller.h>
#include <Interface.h>

#define TRIGGER_PIN       GPIO_NUM_32
#define FEEDBACK_PIN      GPIO_NUM_35

#define DISPLAY_CLK_PIN   GPIO_NUM_16
#define DISPLAY_DATA_PIN  GPIO_NUM_17

Machine *smokeMachine;
Controller *controller;
Interface *interface;

void setup() {
    smokeMachine = new Machine(TRIGGER_PIN, FEEDBACK_PIN);
    controller = new Controller(smokeMachine);
    interface = new Interface(controller, smokeMachine, DISPLAY_DATA_PIN, DISPLAY_CLK_PIN);

    controller->setMode(Controller::Mode::TIMED_OUTPUT);
    //controller->setIgnoreReady(true);
    controller->setOutputVolume(5);

    Serial.begin(9600);
}

void loop() {
    smokeMachine->process();
    controller->process();
    interface->process();
}