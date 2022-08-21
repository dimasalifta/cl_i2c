class Joystick
{
  private:
    bool _lastState1;
    bool _lastState2;
    bool _lastState3;
    bool _lastState4;
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _pin3;
    uint8_t _pin4;

  public:
    Joystick(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
    {
      _pin1 = pin1;
      _pin2 = pin2;
      _pin3 = pin3;
      _pin4 = pin4;
    };
    
    void begin() {
      pinMode(_pin1, INPUT_PULLUP);
      pinMode(_pin2, INPUT_PULLUP);
      pinMode(_pin3, INPUT_PULLUP);
      pinMode(_pin4, INPUT_PULLUP);
    }

    bool forward() {
      delay(10);
      bool state1 = digitalRead(_pin1);
      if (state1 != _lastState1)
      {
        _lastState1 = state1;
        return state1 == LOW ? HIGH : LOW;
      }
    }

    bool backward() {
      delay(10);
      bool state2 = digitalRead(_pin2);
      if (state2 != _lastState2)
      {
        _lastState2 = state2;
        return state2 == LOW ? HIGH : LOW;
      }
    }

    bool right() {
      delay(10);
      bool state3 = digitalRead(_pin3);
      if (state3 != _lastState3)
      {
        _lastState3 = state3;
        return state3 == LOW ? HIGH : LOW;
      }
    }

    bool left() {
      delay(10);
      bool state4 = digitalRead(_pin4);
      if (state4 != _lastState4)
      {
        _lastState4 = state4;
        return state4 == LOW ? HIGH : LOW;
      }
    }
};

Joystick joystick(forwardPin, backwardPin, rightPin, leftPin);

void joystick_setup()
{
  joystick.begin();
  Serial.println("joystick_setup ... DONE");
}