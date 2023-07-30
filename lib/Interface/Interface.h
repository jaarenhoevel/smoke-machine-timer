#include <Arduino.h>
#include <U8g2lib.h>

#include <Controller.h>

#define INTERFACE_UPDATE_INTERVAL   750

class Interface {
    public:
        Interface(Controller *controller, gpio_num_t dataPin, gpio_num_t clockPin);

        void process();
    
    private:
        Controller *controller;
        U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2;

        uint32_t lastUpdate = 0;
};