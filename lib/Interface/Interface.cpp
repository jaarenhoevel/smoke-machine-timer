#include <Interface.h>

Interface::Interface(Controller *controller, Machine *machine, gpio_num_t dataPin, gpio_num_t clockPin) {
    this->controller = controller;
    this->machine = machine;

    this->u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, 255, dataPin, clockPin); 
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
        this->u8g2->setFont(u8g2_font_logisoso32_tf);

        std::string timeStr;

        if (!this->controller->getIgnoreReady() && !this->machine->isReady()) {
            timeStr = "HEATING";
        } else {
            uint32_t timeLeft = this->controller->getTimeUntilNextEvent() / 1000;
            uint32_t secondsLeft = timeLeft % 60;
            uint32_t minutesLeft = (timeLeft / 60) % 60;
            
            timeStr = (minutesLeft < 10 ? "0" : "") + std::to_string(minutesLeft)+ ":" + (secondsLeft < 10 ? "0" : "") + std::to_string(secondsLeft);
        }

        uint8_t timeStrWidth = this->u8g2->getStrWidth(timeStr.c_str());
        this->u8g2->drawStr(64 - timeStrWidth / 2, 44, timeStr.c_str());

        this->u8g2->setFont(u8g2_font_helvB10_tf);
        std::string volumeStr = std::to_string(this->controller->getOutputVolume()) + " m\u00B3/s";

        uint8_t volumeStrWidth = this->u8g2->getStrWidth(volumeStr.c_str());
        this->u8g2->drawUTF8(64 - volumeStrWidth / 2, 64, volumeStr.c_str());
        
        if (this->controller->getIgnoreReady() && !this->machine->isReady()) this->u8g2->drawBox(0, 0, 128, 2);
    }
}