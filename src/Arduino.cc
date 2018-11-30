#include "arduino-mock/Arduino.h"

static ArduinoMock* arduinoMock = NULL;
ArduinoMock* arduinoMockInstance() {
  if(!arduinoMock) {
    arduinoMock = new ArduinoMock();
  }
  return arduinoMock;
}

void releaseArduinoMock() {
  if(arduinoMock) {
    delete arduinoMock;
    arduinoMock = NULL;
  }
}

ArduinoMock::ArduinoMock() {
  currentMillis = 0;
  _millisDelayed = 0;
  _interruptsOn = true;
}

void interrupts(void) {
  arduinoMock->_interruptsOn = true;
  return arduinoMock->interrupts();
};

void noInterrupts(void) {
  arduinoMock->_interruptsOn = false;
  return arduinoMock->noInterrupts();
};

uint8_t digitalPinToBitMask(uint8_t pin) { 
  if (pin >= 0 && pin <= 7) {
    return (0x01 << pin);
  } else if (pin >= 8 && pin <= 13) {
    return (0x01 << (pin - 8));
  } else {
    return 0x01;
  }
};

uint8_t digitalPinToPort(uint8_t pin) { 
  UNUSED(pin);
  return 1;
};

uint8_t* portOutputRegister(uint8_t port) {
  UNUSED(port);
  return &arduinoMock->PORTD; 
};

uint8_t* portInputRegister(uint8_t port) {
  UNUSED(port);
  return &arduinoMock->PIND; 
};

uint8_t* portModeRegister(uint8_t port) {
  UNUSED(port);
  return &arduinoMock->DDRD; 
};

void pinMode(uint8_t a, uint8_t b) {
  assert (arduinoMock != NULL);
  arduinoMock->pinMode(a, b);
}
void digitalWrite(uint8_t a, uint8_t b) {
  assert (arduinoMock != NULL);
  arduinoMock->digitalWrite(a, b);
}

int digitalRead(uint8_t a) {
  assert (arduinoMock != NULL);
  return arduinoMock->digitalRead(a);
}

int analogRead(uint8_t a) {
  assert (arduinoMock != NULL);
  return arduinoMock->analogRead(a);
}

void analogReference(uint8_t mode) {
  UNUSED(mode);
}

void analogWrite(uint8_t a, int b) {

  assert (arduinoMock != NULL);
  arduinoMock->analogWrite(a, b);
}

unsigned long millis(void) {
  assert (arduinoMock != NULL);
  arduinoMock->millis();
  return arduinoMock->getMillis();
}

unsigned long micros(void) {
  return 0;
}
void delay(unsigned long a) {
  assert (arduinoMock != NULL);
  arduinoMock->delay(a);
}
void delayMicroseconds(unsigned int us) {
  assert (arduinoMock != NULL);
  arduinoMock->_millisDelayed += us;
  arduinoMock->delayMicroseconds(us);
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  UNUSED(pin);
  UNUSED(state);
  UNUSED(timeout);
  return 0;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder,
              uint8_t val) {
  UNUSED(dataPin);
  UNUSED(clockPin);
  UNUSED(bitOrder);
  UNUSED(val);
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
  UNUSED(dataPin);
  UNUSED(clockPin);
  UNUSED(bitOrder);
  return 0;
}

void attachInterrupt(uint8_t, void (*)(void), int mode) {
  UNUSED(mode);
}

void detachInterrupt(uint8_t) {}
