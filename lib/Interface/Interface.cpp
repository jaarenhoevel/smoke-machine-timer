#include <Interface.h>

Interface::Interface(Controller *controller, gpio_num_t dataPin, gpio_num_t clockPin) {
    this->controller = controller;

    this->u8g2 = new U8G2_SSD1306_128X64_NONAME_1_SW_I2C(U8G2_R0, dataPin, clockPin);
    this->u8g2->begin();

    this->u8g2->firstPage();
    do {
        /* all graphics commands have to appear within the loop body. */    
        this->u8g2->setFont(u8g2_font_profont22_tr);
        this->u8g2->drawStr(0,24,"Smoke Timer");
    } while (this->u8g2->nextPage());
}

void Interface::process() {

}