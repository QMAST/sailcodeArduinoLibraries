#include "pololu_servo.h" 

PololuMSC::PololuMSC(Stream* serialIn, int reset_pin) {
    this->serialCom = serialIn;
    this->reset_pin = reset_pin;
}

int PololuMSC::restart() {
    // reset the pololu
    digitalWrite(this->reset_pin, HIGH);
    delay(this->RESET_HIGH_WAIT);
    digitalWrite(this->reset_pin, LOW);
    delay(this->RESET_LOW_WAIT);

    // send initialization byte
    this->serialCom->write(0xFF);

    return 0;
}
