#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <CountDown.h>
#include "libpwm/Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include "GlobalVariable.h"
#include "Joystick.h"
#include "CraneMotor.h"
#include "CountDownAll.h"
#include "MqttEth.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40

// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

#if defined(ARDUINO_ARCH_SAMD)  
// for Zero, the output on USB Serial console, remove the line below if using programming port to program the Zero!
  #define Serial SerialUSB
#endif


void setup()
{
  #ifdef ESP8266
  Wire.pins(20, 21);   // Pin SDA & SCL
  #endif
  Serial.begin(115200);
  Serial1.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(1000);  // This is the maximum PWM frequency

  joystick_setup();
  craneMotor_setup();
  craneMotor_returnToHomeSetup();
  mqtt_connection_setup();
}

void loop()
{  
  // Handling auto connection to server
  !client.connected() ? reconnectToServer() : connectedToServer();

  CD_RDY_func();

  CD_PLY_func();
  
  CD_CONT_func();
}

boolean returnToHomeState()
{ 
  if (digitalRead(limitSwitchBackwardPin) == LOW && digitalRead(limitSwitchLeftPin) == LOW && digitalRead(limitSwitchUpPin) == LOW)
  {
    // Serial.println("if rth state");
    CraneMotor_Xaxis(0);
    CraneMotor_Yaxis(0);
    CraneMotor_Zaxis(0);
    return true;
  }
  else
  {
    return false;
  }
}
