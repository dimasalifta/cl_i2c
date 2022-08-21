void MessagePub(String Action){
    String pubGLOBAL_TO        = "";
    pubGLOBAL_TO               = GLOBAL_TO + "          ";
    pubGLOBAL_TO               = pubGLOBAL_TO.substring(0, TO_length) + ">";

    String pubGLOBAL_ACT        = "";
    pubGLOBAL_ACT               = GLOBAL_ACT + "          ";
    pubGLOBAL_ACT               = pubGLOBAL_ACT.substring(0, ACT_length) + ">";
    
    String pubGLOBAL_CTRL       = "";
    pubGLOBAL_CTRL              = GLOBAL_CTRL + " ";
    pubGLOBAL_CTRL              = pubGLOBAL_CTRL.substring(0, CTRL_length) + ">";
    
    String pubGLOBAL_CD_PLAY    = "";
    pubGLOBAL_CD_PLAY           = GLOBAL_CD_PLAY + "  ";
    pubGLOBAL_CD_PLAY           = pubGLOBAL_CD_PLAY.substring(0, CD_PLAY_length) + ">";
    
    String pubGLOBAL_CD_CONT    = "";
    pubGLOBAL_CD_CONT           = GLOBAL_CD_CONT + " ";
    pubGLOBAL_CD_CONT           = pubGLOBAL_CD_CONT.substring(0, CD_CONT_length) + ">";
    
    String pubGLOBAL_CD_RDY     = "";
    pubGLOBAL_CD_RDY            = GLOBAL_CD_RDY + " ";
    pubGLOBAL_CD_RDY            = pubGLOBAL_CD_RDY.substring(0, CD_RDY_length) + ">";
    
    String pubGLOBAL_STS_MACH   = "";
    pubGLOBAL_STS_MACH          = GLOBAL_STS_MACH + "          ";
    pubGLOBAL_STS_MACH          = pubGLOBAL_STS_MACH.substring(0, STS_MACH_length) + ">";

    String pubGLOBAL_RWD        = "";
    pubGLOBAL_RWD               = GLOBAL_RWD + "           ";   // ini 11 spasi
    pubGLOBAL_RWD               = pubGLOBAL_RWD.substring(0, RWD_length) + ">";
    
    String pubGLOBAL_STS_USR    = "";
    pubGLOBAL_STS_USR           = GLOBAL_STS_USR + "                    ";
    pubGLOBAL_STS_USR           = pubGLOBAL_STS_USR.substring(0, STS_USR_length) + ">";
    
    String pubGLOBAL_TOKEN      = "";
    pubGLOBAL_TOKEN             = GLOBAL_TOKEN + "                                                            ";
    pubGLOBAL_TOKEN             = pubGLOBAL_TOKEN.substring(0, TOKEN_length) + ">";
    
    String pubGLOBAL_MAX_CONT   = "";
    pubGLOBAL_MAX_CONT          = GLOBAL_MAX_CONT + "  ";
    pubGLOBAL_MAX_CONT          = pubGLOBAL_MAX_CONT.substring(0, MAX_CONT_length) + ">";
    
    String pubGLOBAL_CURR_CONT  = "";
    pubGLOBAL_CURR_CONT         = String(GLOBAL_CURR_CONT) + "  ";
    pubGLOBAL_CURR_CONT         = pubGLOBAL_CURR_CONT.substring(0, CURR_CONT_length) + ">";
    
    String pubGLOBAL_GRIP_STR   = "";
    pubGLOBAL_GRIP_STR          = GLOBAL_GRIP_STR + "   ";
    pubGLOBAL_GRIP_STR          = pubGLOBAL_GRIP_STR.substring(0, GRIP_STR_length) + ">";

    String pubPayload = "";
    pubPayload = pubGLOBAL_TO + pubGLOBAL_ACT + pubGLOBAL_CTRL + pubGLOBAL_CD_PLAY + pubGLOBAL_CD_CONT + pubGLOBAL_CD_RDY + pubGLOBAL_STS_MACH + pubGLOBAL_RWD + pubGLOBAL_STS_USR + pubGLOBAL_TOKEN + pubGLOBAL_MAX_CONT + pubGLOBAL_CURR_CONT + pubGLOBAL_GRIP_STR;
    
    char char_array[pubPayload.length() + 1];
    pubPayload.toCharArray(char_array, pubPayload.length() + 1);

    client.publish(mqtt_topic, char_array);
    Serial.println(char_array);
}