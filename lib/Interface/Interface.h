#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP32Encoder.h>

#include <Controller.h>
#include <Machine.h>

#define INTERFACE_UPDATE_INTERVAL   100

class Interface {
    public:
        Interface(Controller *controller, Machine *macghine, gpio_num_t dataPin, gpio_num_t clockPin, gpio_num_t encoderAPin, gpio_num_t encoderBPin, gpio_num_t encoderBtnPin);

        void process();
    
    private:
        Controller *controller;
        Machine *machine;
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C *u8g2;

        ESP32Encoder *encoder;
        int64_t encoderPos = 1000;

        gpio_num_t encoderBtnPin;
        bool encoderBtnPressed = false;

        uint32_t lastUpdate = 0;

        void drawOverview();
};