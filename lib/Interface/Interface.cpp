#include <Interface.h>

Interface::Interface(Controller *controller, Machine *machine, gpio_num_t dataPin, gpio_num_t clockPin) {
    this->controller = controller;
    this->machine = machine;

    this->u8g2 = new U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R0, dataPin, clockPin); 
    this->u8g2->begin();
}

void Interface::process() {    
    if (millis() - this->lastUpdate < INTERFACE_UPDATE_INTERVAL) return;
    this->lastUpdate = millis();

    this->u8g2->clearBuffer();
    
    this->drawOverview();

    this->u8g2->sendBuffer();
}

void Interface::drawOverview() {
    this->u8g2->setFont(u8g2_font_profont22_tr);
    this->u8g2->drawStr(0, 22, (this->machine->isReady()) ? "Ready." : "Heating...");
    this->u8g2->drawStr(0, 44, (this->machine->isActive()) ? "Active." : "Idle.");
}