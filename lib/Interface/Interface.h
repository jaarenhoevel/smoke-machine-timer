#include <Arduino.h>
#include <U8g2lib.h>

#include <Controller.h>

class Interface {
    public:
        Interface(Controller *controller, gpio_num_t dataPin, gpio_num_t clockPin);

        void process();
    
    private:
        Controller *controller;
        U8G2_SSD1306_128X64_NONAME_1_SW_I2C *u8g2;
};