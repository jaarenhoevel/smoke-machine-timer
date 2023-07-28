#include <Arduino.h>

#include <Machine.h>
#include <Controller.h>
#include <Interface.h>

#define TRIGGER_PIN       GPIO_NUM_25
#define FEEDBACK_PIN      GPIO_NUM_32

#define DISPLAY_CLK_PIN   GPIO_NUM_26
#define DISPLAY_DATA_PIN  GPIO_NUM_27

Machine *smokeMachine;
Controller *controller;
Interface *interface;

void setup() {
    smokeMachine = new Machine(TRIGGER_PIN, FEEDBACK_PIN);
    controller = new Controller(smokeMachine);
    interface = new Interface(controller, DISPLAY_DATA_PIN, DISPLAY_CLK_PIN);
}

void loop() {
    smokeMachine->process();
    controller->process();
    interface->process();
}