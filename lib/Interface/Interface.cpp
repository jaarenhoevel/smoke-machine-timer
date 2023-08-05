#include <Interface.h>

Interface::Interface(Controller *controller, Machine *machine, gpio_num_t dataPin, gpio_num_t clockPin, gpio_num_t encoderAPin, gpio_num_t encoderBPin, gpio_num_t encoderBtnPin) {
    this->controller = controller;
    this->machine = machine;

    this->u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, 255, dataPin, clockPin); 
    this->u8g2->begin();

    ESP32Encoder::useInternalWeakPullResistors=UP;

    this->encoder = new ESP32Encoder();
    this->encoder->attachHalfQuad(encoderAPin, encoderBPin);

    this->encoder->setCount(0);

    this->encoderBtnPin = encoderBtnPin;
    pinMode(this->encoderBtnPin, INPUT_PULLUP);
}

void Interface::process() {    
    if (millis() - this->lastUpdate < INTERFACE_UPDATE_INTERVAL) return;
    this->lastUpdate = millis();

    if (this->encoderPos != this->encoder->getCount()) {
        if (this->encoder->getCount() >= MAX_OUPUT_VOLUME) {
            this->encoder->setCount(MAX_OUPUT_VOLUME - 1);
            this->controller->setIgnoreReady(!this->controller->getIgnoreReady());
        }
        else if (this->encoder->getCount() < 0) {
            this->encoder->setCount(0);
        }

        this->controller->setMode((this->encoder->getCount() == 0) ? Controller::Mode::OFF : Controller::Mode::TIMED_OUTPUT);
        
        this->encoderPos = this->encoder->getCount();
        this->controller->setOutputVolume(this->encoderPos);
    }

    if (!digitalRead(this->encoderBtnPin) != this->encoderBtnPressed) {
        this->encoderBtnPressed = !digitalRead(this->encoderBtnPin);
        
        if (this->encoderBtnPressed) this->machine->activate(0, true);
        else this->machine->deactivate();
    }

    this->u8g2->clearBuffer();
    
    this->drawOverview();

    this->u8g2->sendBuffer();
}

void Interface::drawOverview() {
    this->u8g2->setFont(u8g2_font_logisoso32_tf);

    std::string timeStr;

    if (this->controller->getMode() == Controller::Mode::OFF) {
        timeStr = "OFF";
    } else if (!this->controller->getIgnoreReady() && !this->machine->isReady()) {
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
        
    if ((this->controller->getIgnoreReady() || this->controller->getMode() == Controller::Mode::OFF) && !this->machine->isReady()) this->u8g2->drawBox(0, 0, 128, 2);
}