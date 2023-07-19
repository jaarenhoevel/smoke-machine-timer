#include <Arduino.h>

#include <Machine.h>

#define TRIGGER_PIN   GPIO_NUM_25
#define FEEDBACK_PIN  GPIO_NUM_32

Machine *smokeMachine;

void setup() {
  smokeMachine = new Machine(TRIGGER_PIN, FEEDBACK_PIN);
}

void loop() {
  smokeMachine->process();
}