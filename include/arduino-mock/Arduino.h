/**
 * Arduino mock header
 */
#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#ifdef WIN32
#elif linux
#else
#define true 0x1
#define false 0x0
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define NOT_AN_INTERRUPT 0
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

void interrupts(void);
void noInterrupts(void);

uint8_t digitalPinToBitMask(uint8_t);
uint8_t digitalPinToPort(uint8_t);
uint8_t* portOutputRegister(uint8_t);
uint8_t* portInputRegister(uint8_t);
uint8_t* portModeRegister(uint8_t);

typedef uint8_t boolean;
typedef uint8_t byte;

void init(void);

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#include <gmock/gmock.h>

#define UNUSED(expr) do { (void)(expr); } while (0)
#define F(x) (x)

class ArduinoMock {
  private:
    unsigned long  currentMillis;

  public:
    ArduinoMock();
    bool _interruptsOn;
    unsigned int _millisDelayed;

    void _resetMillisDelayed(void) {
        _millisDelayed = 0;
    }

    // https://www.arduino.cc/en/Reference/PortManipulation
    // Pins 0 to 7
    uint8_t DDRD;   // mode register
    uint8_t PORTD;  // output register
    uint8_t PIND;   // input register

    // Pins 8 to 13
    uint8_t DDRB;   // mode register
    uint8_t PORTB;  // output register
    uint8_t PINB;   // input register

    // Analog Pins 0 to 5
    uint8_t DDRC;   // mode register
    uint8_t PORTC;  // output register
    uint8_t PINC;   // input register

    unsigned long getMillis() {
      return currentMillis;
    };

    void setMillisRaw (unsigned long milliseconds) {
      currentMillis = milliseconds;
    };
    void setMillisSecs(unsigned long seconds) {
      setMillisRaw(seconds *      1000);
    };
    void setMillisMins(unsigned long minutes) {
      setMillisRaw(minutes *   60 * 1000);
    };
    void setMillisHrs (float         hours)   {
      setMillisRaw(hours  * 60 * 60 * 1000);
    };

    void addMillisRaw (unsigned long milliseconds) {
      currentMillis += milliseconds;
    };
    void addMillisSecs(unsigned long seconds) {
      addMillisRaw(seconds *      1000);
    };
    void addMillisMins(unsigned long minutes) {
      addMillisRaw(minutes *   60 * 1000);
    };
    void addMillisHrs (float         hours)   {
      addMillisRaw(hours  * 60 * 60 * 1000);
    };

    MOCK_METHOD2(pinMode, void (uint8_t, uint8_t));
    MOCK_METHOD2(analogWrite, void (uint8_t, int));
    MOCK_METHOD2(digitalWrite, void (uint8_t, uint8_t));
    MOCK_METHOD1(digitalRead, int (int));
    MOCK_METHOD1(analogRead, int (int));
    MOCK_METHOD1(delay, void (int));
    MOCK_METHOD1(delayMicroseconds, void (int));
    MOCK_METHOD0(millis, unsigned long ());
    MOCK_METHOD0(interrupts, void (void));
    MOCK_METHOD0(noInterrupts, void (void));
};
ArduinoMock* arduinoMockInstance();
void releaseArduinoMock();

#endif // ARDUINO_H
