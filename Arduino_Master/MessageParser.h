void messageParserTO(byte* payload){
  TMP_TO           = "";
  for (int i=TO_posBegin; i<=TO_posEnd; i++){
    TMP_TO += (char)payload[i];
  }
  TMP_TO.trim();
}

void messageParserACT(byte* payload){
  TMP_ACT          = "";
  for (int i=ACT_posBegin; i<=ACT_posEnd; i++){
    TMP_ACT += (char)payload[i];
  }
  TMP_ACT.trim();
}

void messageParserCTRL(byte* payload){

  TMP_CTRL         = "";
  for (int i=CTRL_posBegin; i<=CTRL_posEnd; i++){
    TMP_CTRL += (char)payload[i];
  }
  TMP_CTRL.trim();
}

void messageParserCD_PLAY(byte* payload){
  TMP_CD_PLAY      = "";
  for (int i=CD_PLAY_posBegin; i<=CD_PLAY_posEnd; i++){
    TMP_CD_PLAY += (char)payload[i];
  }
  TMP_CD_PLAY.trim();
}

void messageParserCD_CONT(byte* payload){
  TMP_CD_CONT      = "";
  for (int i=CD_CONT_posBegin; i<=CD_CONT_posEnd; i++){
    TMP_CD_CONT += (char)payload[i];
  }
  TMP_CD_CONT.trim();
}

void messageParserCD_RDY(byte* payload){
  TMP_CD_RDY       = "";
  for (int i=CD_RDY_posBegin; i<=CD_RDY_posEnd; i++){
    TMP_CD_RDY += (char)payload[i];
  }
  TMP_CD_RDY.trim();
}

void messageParserSTS_MACH(byte* payload){
  TMP_STS_MACH     = "";
  for (int i=STS_MACH_posBegin; i<=STS_MACH_posEnd; i++){
    TMP_STS_MACH += (char)payload[i];
  }
  TMP_STS_MACH.trim();
}

void messageParserRWD(byte* payload){
  TMP_RWD          = "";
  for (int i=RWD_posBegin; i<=RWD_posEnd; i++){
    TMP_RWD += (char)payload[i];
  }
  TMP_RWD.trim();
}

void messageParserSTS_USR(byte* payload){
  TMP_STS_USR      = "";
  for (int i=STS_USR_posBegin; i<=STS_USR_posEnd; i++){
    TMP_STS_USR += (char)payload[i];
  }
  TMP_STS_USR.trim();
}

void messageParserTOKEN(byte* payload){
  TMP_TOKEN      = "";
  for (int i=TOKEN_posBegin; i<=TOKEN_posEnd; i++){
    TMP_TOKEN += (char)payload[i];
  }
  TMP_TOKEN.trim();
}

void messageParserMAX_CONT(byte* payload){
  TMP_MAX_CONT      = "";
  for (int i=MAX_CONT_posBegin; i<=MAX_CONT_posEnd; i++){
    TMP_MAX_CONT += (char)payload[i];
  }
  TMP_MAX_CONT.trim();
}

void messageParserCURR_CONT(byte* payload){
  TMP_CURR_CONT      = "";
  for (int i=CURR_CONT_posBegin; i<=CURR_CONT_posEnd; i++){
    TMP_CURR_CONT += (char)payload[i];
  }
  TMP_CURR_CONT.trim();
}

void messageParserGRIP_STR(byte* payload){
  TMP_GRIP_STR     = "";
  for (int i=GRIP_STR_posBegin; i<=GRIP_STR_posEnd; i++){
    TMP_GRIP_STR += (char)payload[i];
  }
  TMP_GRIP_STR.trim();
}