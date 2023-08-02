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
    if (this->controller->getMode() == Controller::Mode::TIMED_OUTPUT) {
        this->u8g2->setFont(u8g2_font_logisoso32_tn);

        uint32_t timeLeft = this->controller->getTimeUntilNextEvent() / 1000;
        uint32_t secondsLeft = timeLeft % 60;
        uint32_t minutesLeft = (timeLeft / 60) % 60;
        
        std::string timeStr = (minutesLeft < 10 ? "0" : "") + std::to_string(minutesLeft)+ ":" + (secondsLeft < 10 ? "0" : "") + std::to_string(secondsLeft);
        this->u8g2->drawStr(16, 64, timeStr.c_str());
    }
}