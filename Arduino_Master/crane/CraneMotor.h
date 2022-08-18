void Crane_Gripper(String _GLOBAL_GRIP_STR);
void CraneMotor_Xaxis(int velocity);
void CraneMotor_Yaxis(int velocity);
void CraneMotor_Zaxis(int velocity);
void ReturnToHome();
void craneMotor_returnToHomeSetup();

void craneMotor_setup()
{
  pinMode(dollCounterPin,         INPUT);
  pinMode(limitSwitchBackwardPin, INPUT_PULLUP);
  pinMode(limitSwitchRightPin,    INPUT_PULLUP);
  pinMode(limitSwitchLeftPin,     INPUT_PULLUP);
  pinMode(limitSwitchUpPin,       INPUT_PULLUP);
  pinMode(limitSwitchDownPin,     INPUT_PULLUP);

  pinMode(motorForwardPin,        OUTPUT);
  pinMode(motorBackwardPin,       OUTPUT);
  pinMode(motorLeftPin,           OUTPUT);
  pinMode(motorRightPin,          OUTPUT);
  pinMode(motorUpPin,             OUTPUT);
  pinMode(motorDownPin,           OUTPUT);
  pinMode(solenoidPinA,           OUTPUT);
  pinMode(solenoidPinB,           OUTPUT);

 
  Crane_Gripper("0");
  CraneMotor_Xaxis(0);
  CraneMotor_Yaxis(0);
  CraneMotor_Zaxis(0);

  Serial.println("craneMotor_setup ... DONE");
}

void craneMotor_returnToHomeSetup()
{
  // CraneMotor_Zaxis(-4095);
  // //
  //Serial.print("crane motor z axis done"); 
  while (returnToHomeState() == false)
  {
    ReturnToHome();
  }
  Serial.println("ReturnToHome ... DONE");
}

void Crane_Gripper(String _GLOBAL_GRIP_STR){
  int cengkraman = _GLOBAL_GRIP_STR.toInt();
  if(cengkraman >= 100) cengkraman = 100;
  if(cengkraman <= 0)   cengkraman = 0;

  int map_cengkraman = (cengkraman,0,100,4095,0);

  pwm.setPWM(solenoidPinA, 0, map_cengkraman);
  pwm.setPWM(solenoidPinB, 0, 4095);
}


void CraneMotor_Xaxis(int velocity)
{
  if (velocity > 0)    velocity = 4095;
  if (velocity < 0)    velocity = -4095;

  if (velocity > 0)
  {
    pwm.setPWM(motorRightPin, 0, velocity);
  }  
  else if (velocity < 0)
  {
    pwm.setPWM(motorLeftPin, 0, abs(velocity));
  }
  else
  {
    pwm.setPWM(motorRightPin, 0, 100);
    pwm.setPWM(motorLeftPin, 0, 100);
    
  }
}

void CraneMotor_Yaxis(int velocity)
{
  if (velocity > 0)    velocity = 4095;
  if (velocity < 0)    velocity = -4095;

  if (velocity > 0)
  {
    pwm.setPWM(motorForwardPin, 0, velocity);
  }
  else if (velocity < 0)
  {
    pwm.setPWM(motorBackwardPin, 0, abs(velocity));
  }
  else
  {
    pwm.setPWM(motorForwardPin, 0, 100);
    pwm.setPWM(motorBackwardPin, 0, 100);
  }
}

void CraneMotor_Zaxis(int velocity)
{
  if (velocity > 0)    velocity = 4095;
  if (velocity < 0)    velocity = -4095;

  if (velocity > 0)
  {
    pwm.setPWM(motorUpPin, 0, velocity);
  }  

  else if (velocity < 0)
  {
    pwm.setPWM(motorDownPin, 0, abs(velocity));
  }

  else
  {
    pwm.setPWM(motorUpPin, 0, 0);
    pwm.setPWM(motorDownPin, 0, 0);
  }
}

void ReturnToHome()
{
  // if (digitalRead(limitSwitchUpPin) == LOW){
  //   CraneMotor_Zaxis(4095);
  // }
  // else if (digitalRead(limitSwitchLeftPin) == LOW){
  //   CraneMotor_Yaxis(4095);
  // }
  // else if (digitalRead(limitSwitchBackwardPin) == LOW){
  //   CraneMotor_Xaxis(-4095);
  // }
    digitalRead(limitSwitchBackwardPin) == LOW ? CraneMotor_Xaxis(0) : CraneMotor_Xaxis(-4095);
    digitalRead(limitSwitchLeftPin)     == LOW ? CraneMotor_Yaxis(0) : CraneMotor_Yaxis(4095);
    digitalRead(limitSwitchUpPin)       == LOW ? CraneMotor_Zaxis(0) : CraneMotor_Zaxis(4095);
    if (returnToHomeState() == true)
    {
      CraneMotor_Xaxis(0);
      CraneMotor_Yaxis(0);
      CraneMotor_Zaxis(0);
      Crane_Gripper("0");
    }
}