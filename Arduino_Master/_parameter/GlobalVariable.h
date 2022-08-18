// Mqtt Configuration -------------------------------------------------------------
// Update these with values suitable for your network.
// byte mac[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xDD, 0x11};   // for arduino on the table
byte mac[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xDD, 0x29};
// IPAddress ipArduino(192, 168, 1, 224);
IPAddress ipArduino(192, 168, 1, 29);
IPAddress serverBroker(180, 210, 205, 235);

const char* mqtt_topic = "claudia09";
const char* clientID = "machine_claudia09";

EthernetClient ethClient;
PubSubClient client(serverBroker, 1883, ethClient);
// Mqtt Configuration -------------------------------------------------------------

// Machine Default Configuration -------------------------------------------------------------
String DEFAULT_TO           = "beacon";
String DEFAULT_CD_RDY       = "3";
String DEFAULT_CD_PLAY      = "10";
String DEFAULT_CD_CONT      = "6";
String DEFAULT_GRIP_STR     = "95";

String DEFAULT_MAX_CONT     = "-1";

String MACH_NAME     = "claudia09";
int DEFAULT_CountDown_GRABINGDOWN   = 5;        // unit in second
int DEFAULT_CountDown_RWDING        = 3000;        // unit in second
// Machine Default Configuration -------------------------------------------------------------

// Pin Configuration -------------------------------------------------------------
// pin 4,10,11,12,13 untuk ETH SHIELD
const int motorForwardPin             = 13;          // I2C PWM no 8
const int motorBackwardPin            = 12;          // I2C PWM no 9
const int motorLeftPin                = 14;         // I2C PWM no 10
const int motorRightPin               = 15;         // I2C PWM no 11
const int motorUpPin                  = 10;         // I2C PWM no 12
const int motorDownPin                = 11;         // I2C PWM no 13
const int solenoidPinA                = 8;         // I2C PWM no 14
const int solenoidPinB                = 9;
         // I2C PWM no 15
const int buttonOkPin                 = 22;         // Grab
const int forwardPin                  = 23;         // Front
const int rightPin                    = 24;         // Right
const int backwardPin                 = 25;         // Back
const int leftPin                     = 26;         // Left

const int dollCounterPin              = 32;         // Proxy Sensor
const int limitSwitchBackwardPin      = 30;         // Limit Switch Back
const int limitSwitchRightPin         = 27;         // Limit Switch Right
const int limitSwitchLeftPin          = 28;         // Limit Switch Left
const int limitSwitchUpPin            = 29;         // Limit Switch Up
const int limitSwitchDownPin          = 31;         // Limit Switch Down

const int lampIndicatorPin            = 33;


// Pin Configuration -------------------------------------------------------------

// Variable for Crane -------------------------------------------------------------
int sumbuX;
int sumbuY;
int sumbuZ;
int xAxisSpeed  = 4095; 
int yAxisSpeed  = 4095;
int zAxisSpeed  = 4095;
int stopSpeed   = 0;
// Variable for Crane -------------------------------------------------------------

// CountDown Init -------------------------------------------------------------
CountDown CountDown_RDY(CountDown::SECONDS);
CountDown CountDown_PLAY(CountDown::SECONDS);
CountDown CountDown_CONT(CountDown::SECONDS);
CountDown CountDown_RWDING(CountDown::MILLIS);
CountDown CountDown_GRABINGDOWN(CountDown::SECONDS);

int CD_RDYfirst;
int CD_RDYLast;        // Ready CountDown

int CD_PLAYfirst;
int CD_PLAYLast;        // Ready CountDown

int CD_CONTfirst;
int CD_CONTLast;        // Ready CountDown

int CD_RWDINGfirst;
int CD_RWDINGLast;        // Rewarding CountDown

String CD_RWDING;        // Rewarding CountDown
// CountDown Init -------------------------------------------------------------

// Variable for Machine -------------------------------------------------------------
String GLOBAL_TO           = DEFAULT_TO;
String GLOBAL_ACT          = "INFO";
String GLOBAL_CTRL         = "";
String GLOBAL_CD_PLAY      = DEFAULT_CD_PLAY;
String GLOBAL_CD_CONT      = DEFAULT_CD_CONT;
String GLOBAL_CD_RDY       = DEFAULT_CD_RDY;
String  GLOBAL_STS_MACH     = "";
String GLOBAL_RWD          = "";
String GLOBAL_STS_USR      = "";
String GLOBAL_TOKEN        = "";
String GLOBAL_MAX_CONT     = "";
int GLOBAL_CURR_CONT       = 0;
String GLOBAL_GRIP_STR     = DEFAULT_GRIP_STR;  // Minimal 40%
// Variable for Machine -------------------------------------------------------------

// Parser Position
/* Name and Length and Position
TO          [10]        0-9
ACT         [10]        11-20
CTRL        [1]         22
CD_PLAY     [2]         24-25
CD_CONT     [1]         27
CD_RDY      [1]         29
STS_MACH    [10]        31-40
RWD         [10]        42-51
STS_USR     [20]        53-72
TOKEN       [60]        60
MAX_CONT    [2]         135-136
CURR_CONT   [2]         138-139
GRIP_STR    [3]         141-143
*/
const int TO_posBegin = 0;
const int TO_length = 10;
const int TO_posEnd = 9;
const int ACT_posBegin = 11;
const int ACT_length = 10;
const int ACT_posEnd = 20;
const int CTRL_posBegin = 22;
const int CTRL_length = 1;
const int CTRL_posEnd = 22;
const int CD_PLAY_posBegin = 24;
const int CD_PLAY_length = 2;
const int CD_PLAY_posEnd = 25;
const int CD_CONT_posBegin = 27;
const int CD_CONT_length = 1;
const int CD_CONT_posEnd = 27;
const int CD_RDY_posBegin = 29;
const int CD_RDY_length = 1;
const int CD_RDY_posEnd = 29;
const int STS_MACH_posBegin = 31;
const int STS_MACH_length = 10;
const int STS_MACH_posEnd = 40;
const int RWD_posBegin = 42;
const int RWD_length = 10;
const int RWD_posEnd = 51;
const int STS_USR_posBegin = 53;
const int STS_USR_length = 20;
const int STS_USR_posEnd = 72;
const int TOKEN_posBegin = 74;
const int TOKEN_length = 60;
const int TOKEN_posEnd = 133;
const int MAX_CONT_posBegin = 135;
const int MAX_CONT_length = 2;
const int MAX_CONT_posEnd = 136;
const int CURR_CONT_posBegin = 138;
const int CURR_CONT_length = 2;
const int CURR_CONT_posEnd = 139;
const int GRIP_STR_posBegin = 141;
const int GRIP_STR_length = 3;
const int GRIP_STR_posEnd = 143;

// Variable for Sending Message -------------------------------------------------------------
String TMP_TO           = "";
String TMP_ACT          = "";
String TMP_CTRL         = "";
String TMP_CD_PLAY      = "";
String TMP_CD_CONT      = "";
String TMP_CD_RDY       = "";
String TMP_STS_MACH     = "";
String TMP_RWD          = "";
String TMP_STS_USR      = "";
String TMP_TOKEN        = "";
String TMP_MAX_CONT     = "";
String TMP_CURR_CONT    = "";
String TMP_GRIP_STR     = "";
// Variable for Sending Message-------------------------------------------------------------

// Variable for return To Home-------------------------------------------------------------
boolean returnToHomeState();
// Variable for return To Home-------------------------------------------------------------