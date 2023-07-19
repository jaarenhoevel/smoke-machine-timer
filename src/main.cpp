#include <Arduino.h>

#include <Machine.h>
#include <Controller.h>

#define TRIGGER_PIN   GPIO_NUM_25
#define FEEDBACK_PIN  GPIO_NUM_32

Machine *smokeMachine;
Controller *controller;

void setup() {
  smokeMachine = new Machine(TRIGGER_PIN, FEEDBACK_PIN);
  controller = new Controller(smokeMachine);
}

void loop() {
  smokeMachine->process();
  controller->process();
}