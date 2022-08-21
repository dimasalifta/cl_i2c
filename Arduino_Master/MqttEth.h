#include "MessageParser.h"
#include "MessagePublish.h"

void action_CONNECTED();
void action_RST_MACHbootup();
void action_RST_MACH();
void action_INFO();
void funcUPDT_TKN();
void funcHIT_STRT(String ParamSTS_USR, String ParamTOKEN, String ParamCD_PLAY, String ParamCD_CONT, String ParamCD_RDY, String ParamMAX_CONT, String ParamGRIP_STR);
void action_HIT_RDY();
void CD_RDY_func();
void action_HIT_STRT();
void CD_PLY_func();
void action_USR_CTRL();
void action_GRBING();
void action_RWDING();
void CD_CONT_func();
void CD_RWDING_func();
void action_CONT();
void funcHIT_CONT(String ParamCD_PLAY, String ParamCD_CONT, String ParamCD_RDY, String ParamMAX_CONT, String ParamGRIP_STR);
void funcSTRT();
void funcCONT();
void funcDONE();

void CraneControl();


void callback(char* topic, byte* payload, unsigned int length) {
  String receivedTopic = topic;
  String payloadString;

  // for (int i=0; i<=length; i++) {
  //   payloadString += (char)payload[i];
  // }
  // Serial.println("Subscribed [" + receivedTopic + "]: " + payloadString + " : " + length);

  // Serial.println("GLOBAL_TO       : " + GLOBAL_TO);
  // Serial.println("GLOBAL_ACT      : " + GLOBAL_ACT);
  // Serial.println("GLOBAL_STS_USR  : " + GLOBAL_STS_USR);
  // Serial.println("GLOBAL_CTRL     : " + GLOBAL_CTRL);
  // Serial.println("GLOBAL_CD_PLAY  : " + GLOBAL_CD_PLAY);
  // Serial.println("GLOBAL_CD_CONT  : " + GLOBAL_CD_CONT);
  // Serial.println("GLOBAL_CD_RDY   : " + GLOBAL_CD_RDY);
  // Serial.println("GLOBAL_STS_MACH : " + GLOBAL_STS_MACH);
  // Serial.println("GLOBAL_RWD      : " + GLOBAL_RWD);
  // Serial.println("GLOBAL_GRIP_STR : " + GLOBAL_GRIP_STR);
  // Serial.println();

  if (receivedTopic == mqtt_topic)
  {
    messageParserTO(payload);
    if( TMP_TO == MACH_NAME) {
      messageParserACT(payload);
      if( TMP_ACT == "INFO" ){
        action_INFO();
      } else {
        if( TMP_ACT == "UPDT_TKN" ) {
          messageParserSTS_USR(payload);
          if (GLOBAL_STS_USR == TMP_STS_USR) {
            messageParserTOKEN(payload);
            if (GLOBAL_TOKEN == TMP_TOKEN) {
              funcUPDT_TKN();
              action_INFO();
            } else { action_INFO(); }
          } else { action_INFO(); }
        } else {
          if( TMP_ACT == "RST_MACH" ) {
            action_RST_MACH();
          } else {
            if( TMP_ACT == "HIT_STRT" ) {
                if (GLOBAL_STS_MACH == "AVL") {
                  if (GLOBAL_STS_USR == "") {
                    messageParserSTS_USR(payload);
                    messageParserTOKEN(payload);

                    messageParserCD_PLAY(payload);
                    messageParserCD_CONT(payload);
                    messageParserCD_RDY(payload);
                    messageParserMAX_CONT(payload);
                    messageParserGRIP_STR(payload);

                    funcHIT_STRT(TMP_STS_USR, TMP_TOKEN, TMP_CD_PLAY, TMP_CD_CONT, TMP_CD_RDY, TMP_MAX_CONT, TMP_GRIP_STR);
                    funcHIT_CONT(TMP_CD_PLAY, TMP_CD_CONT, TMP_CD_RDY, TMP_MAX_CONT, TMP_GRIP_STR);

                  } else { action_INFO(); }
                } else { action_INFO(); }
            } else {
              if( TMP_ACT == "STRT" ){
                messageParserSTS_USR(payload);
                if (GLOBAL_STS_USR == TMP_STS_USR) {
                  messageParserTOKEN(payload);
                  if (GLOBAL_TOKEN == TMP_TOKEN) {
                    GLOBAL_CURR_CONT = 0;
                    funcSTRT();
                  } else { action_INFO(); }
                } else { action_INFO(); }
              } else {
                if( TMP_ACT == "USR_CTRL" ){
                    if (GLOBAL_STS_MACH == "CD_PLAY") {
                      messageParserSTS_USR(payload);
                      if (GLOBAL_STS_USR == TMP_STS_USR) {
                        messageParserTOKEN(payload);
                        if (GLOBAL_TOKEN == TMP_TOKEN) {

                          // GLOBAL_TO         = TMP_TO;
                          // GLOBAL_ACT        = TMP_ACT;
                          // GLOBAL_STS_USR    = TMP_STS_USR;
                          messageParserCTRL(payload);
                          GLOBAL_CTRL       = TMP_CTRL;
                          // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
                          // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
                          // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
                          // GLOBAL_STS_MACH   = TMP_STS_MACH = "PLAY";
                          // GLOBAL_RWD        = TMP_RWD;
                          // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR
                          
                          // Serial.println("EXEC CTRL " + TMP_CTRL);
                          
                          
                          if ( TMP_CTRL == "G" ) {
                            action_GRBING();
                          }
                          else
                          {
                            CraneControl();
                          }
                        } else { action_INFO(); }
                      } else { action_INFO(); }
                    } else { action_INFO(); }
                } else {
                  if( TMP_ACT == "HIT_CONT" ) {
                    if (GLOBAL_STS_MACH == "CD_CONT") {
                      messageParserSTS_USR(payload);
                      if (GLOBAL_STS_USR == TMP_STS_USR) {
                        messageParserTOKEN(payload);
                        if (GLOBAL_TOKEN == TMP_TOKEN) {

                          messageParserCD_PLAY(payload);
                          messageParserCD_CONT(payload);
                          messageParserCD_RDY(payload);
                          messageParserMAX_CONT(payload);
                          messageParserGRIP_STR(payload);

                          funcHIT_CONT(TMP_CD_PLAY, TMP_CD_CONT, TMP_CD_RDY, TMP_MAX_CONT, TMP_GRIP_STR);
                        } else { action_INFO(); }
                      } else { action_INFO(); }
                    } else { action_INFO(); }
                  } else {
                    if( TMP_ACT == "CONT" ){
                      messageParserSTS_USR(payload);
                      if (GLOBAL_STS_USR == TMP_STS_USR) {
                        messageParserTOKEN(payload);
                        if (GLOBAL_TOKEN == TMP_TOKEN) {

                          GLOBAL_CURR_CONT += 1;
                          funcCONT();
                        } else { action_INFO(); }
                      } else { action_INFO(); }                      
                    } else
                    {
                      if( TMP_ACT == "DONE" ){
                        funcDONE();
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void funcHIT_STRT(String ParamSTS_USR, String ParamTOKEN, String ParamCD_PLAY, String ParamCD_CONT, String ParamCD_RDY, String ParamMAX_CONT, String ParamGRIP_STR){
  Serial.println("EXEC STRT");

  
  GLOBAL_CD_PLAY    = ParamCD_PLAY  != "" ? ParamCD_PLAY : DEFAULT_CD_PLAY;
  GLOBAL_CD_CONT    = ParamCD_CONT  != "" ? ParamCD_CONT : DEFAULT_CD_CONT;
  GLOBAL_CD_RDY     = ParamCD_RDY   != "" ? ParamCD_RDY  : DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "WT_CN_STRT";
  // GLOBAL_RWD        = TMP_RWD;
  GLOBAL_STS_USR    = ParamSTS_USR;
  GLOBAL_TOKEN      = ParamTOKEN;
  GLOBAL_MAX_CONT   = ParamMAX_CONT != "" ? ParamMAX_CONT : DEFAULT_MAX_CONT;
  GLOBAL_GRIP_STR   = ParamGRIP_STR != "" ? ParamGRIP_STR : DEFAULT_GRIP_STR;
  
  MessagePub("action_HIT_STRT");   
}

void funcHIT_CONT(String ParamCD_PLAY, String ParamCD_CONT, String ParamCD_RDY, String ParamMAX_CONT, String ParamGRIP_STR){
  Serial.println("EXEC HIT CONT");

  CountDown_CONT.stop();

  GLOBAL_CD_PLAY    = ParamCD_PLAY  != "" ? ParamCD_PLAY : DEFAULT_CD_PLAY;
  GLOBAL_CD_CONT    = ParamCD_CONT  != "" ? ParamCD_CONT : DEFAULT_CD_CONT;
  GLOBAL_CD_RDY     = ParamCD_RDY   != "" ? ParamCD_RDY  : DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "WT_CN_CONT";
  // GLOBAL_RWD        = TMP_RWD;
  // GLOBAL_STS_USR    = ParamSTS_USR;
  // GLOBAL_TOKEN      = ParamTOKEN;
  GLOBAL_MAX_CONT   = ParamMAX_CONT != "" ? ParamMAX_CONT : DEFAULT_MAX_CONT;
  GLOBAL_GRIP_STR   = ParamGRIP_STR != "" ? ParamGRIP_STR : DEFAULT_GRIP_STR;
  
  MessagePub("action_HIT_CONT");   
}

void funcSTRT(){
  // GLOBAL_CTRL =
  // GLOBAL_CD_PLAY =
  // GLOBAL_CD_CONT =
  // GLOBAL_CD_RDY =
  GLOBAL_STS_MACH = "STRT";
  // GLOBAL_RWD =
  // GLOBAL_STS_USR =
  // GLOBAL_TOKEN = TMP_TOKEN;
  // GLOBAL_TOKEN = 
  // GLOBAL_MAX_CONT = 
  // GLOBAL_CURR_CONT =
  // GLOBAL_GRIP_STR =

  MessagePub("funcSTRT");

  int timerCD_RDY = GLOBAL_CD_RDY.toInt();
  CountDown_RDY.start(timerCD_RDY);    
}

void funcUPDT_TKN(){
  // GLOBAL_CTRL =
  // GLOBAL_CD_PLAY =
  // GLOBAL_CD_CONT =
  // GLOBAL_CD_RDY =
  // GLOBAL_STS_MACH =
  // GLOBAL_RWD =
  // GLOBAL_STS_USR =
  GLOBAL_TOKEN = TMP_TOKEN;
  // GLOBAL_TOKEN = 
  // GLOBAL_MAX_CONT = 
  // GLOBAL_CURR_CONT =
  // GLOBAL_GRIP_STR =
}

void funcCONT(){
  // Serial.println("CONT!");
  funcSTRT();
}

void funcDONE(){
  CountDown_CONT.stop();
  
  action_RST_MACH();
}

void reconnectToServer() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    digitalWrite(lampIndicatorPin, LOW);  // Nyala
    delay(500);
    // Attempt to connect
    if (client.connect(clientID)) {
      digitalWrite(lampIndicatorPin, LOW);  // Nyala
      
      // client.subscribe(mqtt_topic1);
      client.subscribe(mqtt_topic);
      Serial.println("Connected to Broker succeeded!!!");

      action_CONNECTED(); // jika berhasil konek to Broker
      action_INFO();
      action_RST_MACHbootup();

      return true;
    } else {
      Serial.println("failed, rc=" + String(client.state()) + " try again...!!!");
      digitalWrite(lampIndicatorPin, HIGH);   // Mati
      delay(500);
    }
  }
}

void connectedToServer() {
  digitalWrite(lampIndicatorPin, LOW);  // Nyala
  client.loop();
}

void mqtt_connection_setup(){
  pinMode(lampIndicatorPin, OUTPUT);
  digitalWrite(lampIndicatorPin, HIGH);   // Mati

  client.setServer(serverBroker, 1883);
  client.setCallback(callback);
  Ethernet.begin(mac, ipArduino);
  reconnectToServer();
  action_CONNECTED(); // pertama kali nyala
  action_RST_MACHbootup();  // RESET all Variable Match when machine power on
  delay(1500);
}

void action_CONNECTED(){
  // GLOBAL_TO         = TMP_TO = "beacon";
  // GLOBAL_ACT        = "CONNECTED";
  // GLOBAL_STS_USR    = TMP_STS_USR;
  // GLOBAL_CTRL       = TMP_CTRL;
  // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
  // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
  // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "CONNECTED";
  // GLOBAL_RWD        = TMP_RWD;
  // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;
  MessagePub("action_CONNECTED");
}

void action_INFO(){
  Serial.println("EXEC INFO");
  // GLOBAL_TO         = TMP_TO;
  // GLOBAL_ACT        = TMP_ACT;
  // GLOBAL_STS_USR    = TMP_STS_USR;
  // GLOBAL_CTRL       = TMP_CTRL;
  // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
  // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
  // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
  // GLOBAL_STS_MACH   = TMP_STS_MACH = "RST_MACH";
  // GLOBAL_RWD        = TMP_RWD;
  // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;
  MessagePub("action_INFO");
}

void action_RST_MACHbootup(){
  GLOBAL_CTRL       = "";
  GLOBAL_CD_PLAY    = DEFAULT_CD_PLAY;
  GLOBAL_CD_CONT    = DEFAULT_CD_CONT;
  GLOBAL_CD_RDY     = DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "AVL";
  GLOBAL_RWD        = "";
  GLOBAL_STS_USR    = "";
  GLOBAL_TOKEN      = "";
  GLOBAL_MAX_CONT   = DEFAULT_MAX_CONT;
  GLOBAL_GRIP_STR   = DEFAULT_GRIP_STR;

  MessagePub("action_RST_MACH");
}

void action_RST_MACH(){
  GLOBAL_CTRL       = "";
  // GLOBAL_CD_PLAY    = DEFAULT_CD_PLAY;
  // GLOBAL_CD_CONT    = DEFAULT_CD_CONT;
  // GLOBAL_CD_RDY     = DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "AVL";
  GLOBAL_RWD        = "";
  GLOBAL_STS_USR    = "";
  GLOBAL_TOKEN      = "";
  // GLOBAL_MAX_CONT   = DEFAULT_MAX_CONT;
  // GLOBAL_GRIP_STR   = DEFAULT_GRIP_STR;
  MessagePub("action_RST_MACH");

}

void action_HIT_STRT(){
  Serial.println("EXEC VALIDATION STRT");
    if (GLOBAL_STS_MACH == "AVL")
    {
      if (GLOBAL_STS_USR == "")
      {
        // Serial.println("EXEC STRT");

        // GLOBAL_TO         = TMP_TO;
        GLOBAL_ACT        = TMP_ACT = "HIT_STRT";
        GLOBAL_STS_USR    = TMP_STS_USR;
        // GLOBAL_CTRL       = TMP_CTRL;
        GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
        GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
        GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
        GLOBAL_STS_MACH   = TMP_STS_MACH = "HIT_STRT";
        // GLOBAL_RWD        = TMP_RWD;
        GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;

        MessagePub("action_HIT_STRT");

        int timerCD_RDY = GLOBAL_CD_RDY.toInt();
        CountDown_RDY.start(timerCD_RDY);
      } else
      {
        action_INFO();
      }
    }
}

void action_GRBING()
{
  CountDown_PLAY.stop();    

  // GLOBAL_TO         = TMP_TO;
  // GLOBAL_ACT        = TMP_ACT = "GRBING";
  // GLOBAL_STS_USR    = TMP_STS_USR;
  // GLOBAL_CTRL       = TMP_CTRL = "";
  GLOBAL_CD_PLAY    = "";
  // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
  // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
  GLOBAL_STS_MACH   = "GRBING";
  // GLOBAL_RWD        = TMP_RWD;
  // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR
  
  Serial.println("EXEC GRAB!!!!");
  MessagePub("action_GRBING");
  
  CraneMotor_Xaxis(stopSpeed);
  CraneMotor_Yaxis(stopSpeed);
  CountDown_GRABINGDOWN.start(DEFAULT_CountDown_GRABINGDOWN);
 
  
  // The Claws dropping to down until 5 seconds or until the clawBottomSensor activates when the claw reaches the bottom or the doll
  while (digitalRead(limitSwitchDownPin) != LOW && CountDown_GRABINGDOWN.remaining() != 0)
  {
    action_RWDING();
    CraneMotor_Zaxis(-zAxisSpeed);
  }
  
  // Stop the doll and hold until 0.5 seconds
  for (int i = 0; i < 500; i++)
  {
    action_RWDING();
    CraneMotor_Zaxis(stopSpeed);
    delay(1);
  }
  // Grab the doll and hold until 0.5 seconds
  for (int i = 0; i < 500; i++)
  {
    action_RWDING();
    Crane_Gripper(GLOBAL_GRIP_STR);   // Crane_Gripper("40"); // minimal 40
//    Crane_Gripper("100");
//    delay(1);
  }

  // Claws climbed up until the claws reach clawTopSensor
  while (digitalRead(limitSwitchUpPin) != LOW)
  {
    action_RWDING();
    CraneMotor_Zaxis(zAxisSpeed);

  }
  CraneMotor_Zaxis(stopSpeed);

  // Going to Home
  while (returnToHomeState() == false){
    action_RWDING();
    ReturnToHome();
  }
  Serial.println("ReturnToHome ... DONE");
  Crane_Gripper("0");

  // cek apakah rewardnya belum dapet?
  CountDown_RWDING.start(DEFAULT_CountDown_RWDING);
  while (GLOBAL_STS_MACH == "GRBING"){
    Crane_Gripper("0");
    CD_RWDING_func();
    action_RWDING();
  }

  if (GLOBAL_MAX_CONT == "-1"){
    int timerGLOBAL_CD_CONT = GLOBAL_CD_CONT.toInt();
    CountDown_CONT.start(timerGLOBAL_CD_CONT);
  } else {
    if (GLOBAL_MAX_CONT == "0"){
      funcDONE();
    } else {  
      int NUMBER_GLOBAL_MAX_CONT = GLOBAL_MAX_CONT.toInt();
      if (GLOBAL_CURR_CONT < NUMBER_GLOBAL_MAX_CONT) {
        int timerGLOBAL_CD_CONT = GLOBAL_CD_CONT.toInt();
        CountDown_CONT.start(timerGLOBAL_CD_CONT);
      } else {
        funcDONE();
      }
    }
  }
}

void action_RWDING(){
  //grabbing dan ada boneka lewat
  if (digitalRead(dollCounterPin) ==  LOW && GLOBAL_STS_MACH == "GRBING")
  {
    // GLOBAL_TO         = TMP_TO;
    // GLOBAL_ACT        = TMP_ACT = "RWDING";
    // GLOBAL_STS_USR    = TMP_STS_USR;
    // GLOBAL_CTRL       = TMP_CTRL;
    // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
    // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
    // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
    GLOBAL_STS_MACH   = "RWDING";
    GLOBAL_RWD        = "CL09RWD";
    // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;
    
    MessagePub("action_RWDING");

    CD_RWDING = "";
  }
  else if (digitalRead(dollCounterPin) == HIGH && GLOBAL_STS_MACH == "GRBING" && CD_RWDING == "0" )
  {

    // GLOBAL_TO         = TMP_TO;
    // GLOBAL_ACT        = TMP_ACT = "RWDING";
    // GLOBAL_STS_USR    = TMP_STS_USR;
    // GLOBAL_CTRL       = TMP_CTRL;
    // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
    // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
    // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
    GLOBAL_STS_MACH   = "RWDING";
    GLOBAL_RWD        = "";
    // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;
    
    MessagePub("action_RWDING");

    CD_RWDING = "";
  }
}

void action_CONT(){
  if (GLOBAL_STS_USR == TMP_STS_USR)
  {
      if (GLOBAL_STS_MACH == "CD_CONT")
      {
        CountDown_CONT.stop();

        // GLOBAL_TO         = TMP_TO;
        GLOBAL_ACT        = TMP_ACT;
        // GLOBAL_STS_USR    = TMP_STS_USR;
        // GLOBAL_CTRL       = TMP_CTRL;
        // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
        // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
        // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
        GLOBAL_STS_MACH   = TMP_STS_MACH = "CONT";
        // GLOBAL_RWD        = TMP_RWD;
        // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR        
        
        int temp_GLOBAL_CD_RDY = GLOBAL_CD_RDY.toInt();
        CountDown_RDY.start(temp_GLOBAL_CD_RDY);
      }
  }
}

void CD_RDY_func()
{
  CD_RDYfirst = CountDown_RDY.remaining();
  if(CD_RDYfirst != CD_RDYLast)
  {
    CD_RDYLast = CD_RDYfirst;
    
    // GLOBAL_TO         = TMP_TO;
    // GLOBAL_ACT        = TMP_ACT = "CD_RDY";
    // GLOBAL_STS_USR    = TMP_ACT;
    // GLOBAL_CTRL       = TMP_CTRL;
    // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
    // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
    // GLOBAL_CD_RDY     = TMP_CD_RDY = String(CD_RDYfirst);
    GLOBAL_CD_RDY     = String(CD_RDYfirst);
    GLOBAL_STS_MACH   = TMP_STS_MACH = "CD_RDY";
    // GLOBAL_RWD        = TMP_RWD;
    // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;
    
    MessagePub("CD_RDY");
    if (GLOBAL_CD_RDY == "0")
    {
      int timerCD_PLAY = GLOBAL_CD_PLAY.toInt();
      CountDown_PLAY.start(timerCD_PLAY);
    }
  }
}

void CD_PLY_func()
{
  CD_PLAYfirst = CountDown_PLAY.remaining();
  if(CD_PLAYfirst != CD_PLAYLast)
  {
      CD_PLAYLast = CD_PLAYfirst;

      // GLOBAL_TO         = TMP_TO;
      // GLOBAL_ACT        = TMP_ACT = "CD_PLAY";
      // GLOBAL_STS_USR    = TMP_ACT;
      // GLOBAL_CTRL       = TMP_CTRL;
      GLOBAL_CD_PLAY    = String(CD_PLAYfirst);
      // GLOBAL_CD_CONT    = TMP_CD_CONT  != "" ? TMP_CD_CONT : DEFAULT_CD_CONT;
      // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
      GLOBAL_STS_MACH   = TMP_STS_MACH = "CD_PLAY";
      // GLOBAL_RWD        = TMP_RWD;
      // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;

      if (GLOBAL_CD_PLAY == "0") {
        action_GRBING();
      }
      MessagePub("CD_PLAY");
  }
}

void CD_CONT_func()
{
  CD_CONTfirst = CountDown_CONT.remaining();
  if(CD_CONTfirst != CD_CONTLast)
  {
    CD_CONTLast = CD_CONTfirst;
    
    // GLOBAL_TO         = TMP_TO;
    // GLOBAL_ACT        = TMP_ACT = "CD_CONT";
    // GLOBAL_STS_USR    = TMP_ACT;
    // GLOBAL_CTRL       = TMP_CTRL;
    // GLOBAL_CD_PLAY    = TMP_CD_PLAY  != "" ? TMP_CD_PLAY : DEFAULT_CD_PLAY;
    GLOBAL_CD_CONT    = String(CD_CONTfirst);
    // GLOBAL_CD_RDY     = TMP_CD_RDY   != "" ? TMP_CD_RDY  : DEFAULT_CD_RDY;
    GLOBAL_STS_MACH   = TMP_STS_MACH = "CD_CONT";
    // GLOBAL_RWD        = TMP_RWD;
    // GLOBAL_GRIP_STR   = TMP_GRIP_STR != "" ? TMP_GRIP_STR : DEFAULT_GRIP_STR;

    if (CD_CONTfirst <= 5){
      MessagePub("CD_CONT");
    }
    
    if (GLOBAL_CD_CONT == "0")
    {
      funcDONE();
    }
  }
}

void CD_RWDING_func()
{
  CD_RWDINGfirst = CountDown_RWDING.remaining();
  if(CD_RWDINGfirst != CD_RWDINGLast)
  {
    CD_RWDINGLast = CD_RWDINGfirst;
    CD_RWDING = String(CD_RWDINGfirst);
    //Serial.println("...");
  }
}

void CraneControl()
{
  if (GLOBAL_CTRL == "R")
  { 
    CraneMotor_Xaxis(xAxisSpeed);
    delay(1);
  }
  else if (GLOBAL_CTRL == "L")
  {
    CraneMotor_Xaxis(-xAxisSpeed);
    delay(1);
  }
  else if (GLOBAL_CTRL == "U")
  {
    CraneMotor_Yaxis(-yAxisSpeed);
    delay(1);
  }
  else if (GLOBAL_CTRL == "D")
  {
    CraneMotor_Yaxis(yAxisSpeed);
    delay(1);
  }
  else
  {
    CraneMotor_Xaxis(stopSpeed);
    CraneMotor_Yaxis(stopSpeed);
  }
}
