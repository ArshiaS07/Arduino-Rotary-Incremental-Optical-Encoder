class RotaryEncoder {
    public:
      RotaryEncoder(int clkPin, int dtPin) : _clkPin(clkPin), _dtPin(dtPin) {}

      void begin() {
#ifdef DEBUG
        Serial.begin(9600);
#endif
        pinMode(_clkPin, INPUT_PULLUP);
        pinMode(_dtPin, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(_clkPin), &RotaryEncoder::encoderISR, CHANGE, this);
      }

      long getCount() const {
        return _encoderCount;
      }

      float getSpeed() const {
        return _degreesPerSecond;
      }

    private:
      int _clkPin;
      int _dtPin;
      long _encoderCount = 0;
      byte _encoderState = 0;
      byte _lastEncoderState = 0;
      unsigned long _prevTime = 0;
      unsigned long _currTime = 0;
      float _degreesPerCount = 0;
      float _degreesPerSecond = 0;

      static void encoderISR(void* arg) {
        RotaryEncoder* re = static_cast<RotaryEncoder*>(arg);
        re->_currTime = micros();
        re->_encoderState = (digitalRead(re->_dtPin) << 1) | digitalRead(re->_clkPin);
        if (re->_encoderState != re->_lastEncoderState) {
          switch (re->_encoderState) {
            case 0b01:
              re->_encoderCount++;
              break;
            case 0b10:
              re->_encoderCount--;
              break;
            case 0b11:
              re->_encoderCount++;
              re->_encoderCount--;
              break;
            default:
              break;
          }
          re->_lastEncoderState = re->_encoderState;
          // Compute Speed in Degrees per Second
          re->_degreesPerCount = 360.0 / re->_encoderCount; // degrees per count
          re->_degreesPerSecond = re->_degreesPerCount * 1e6 / (re->_currTime - re->_prevTime); // degrees per second
          re->_prevTime = re->_currTime;
#ifdef DEBUG
          Serial.print("Encoder Count: ");
          Serial.println(re->_encoderCount);
          Serial.print("Encoder Speed: ");
          Serial.print(re->_degreesPerSecond);
          Serial.println(" deg/s");
#endif
        }
      }
  };