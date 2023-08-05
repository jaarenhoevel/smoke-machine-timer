#include <Arduino.h>

#include <Machine.h>
#include <Controller.h>
#include <Interface.h>

#define TRIGGER_PIN         GPIO_NUM_32
#define FEEDBACK_PIN        GPIO_NUM_35

#define DISPLAY_CLK_PIN     GPIO_NUM_16
#define DISPLAY_DATA_PIN    GPIO_NUM_17

#define ENCODER_A_PIN       GPIO_NUM_23
#define ENCODER_B_PIN       GPIO_NUM_21
#define ENCODER_BTN_PIN     GPIO_NUM_22

Machine *smokeMachine;
Controller *controller;
Interface *interface;

void setup() {
    smokeMachine = new Machine(TRIGGER_PIN, FEEDBACK_PIN);
    controller = new Controller(smokeMachine);
    interface = new Interface(controller, smokeMachine, DISPLAY_DATA_PIN, DISPLAY_CLK_PIN, ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BTN_PIN);

    controller->setMode(Controller::Mode::TIMED_OUTPUT);
    controller->setOutputVolume(1);

    Serial.begin(9600);
}

void loop() {
    smokeMachine->process();
    controller->process();
    interface->process();
}