void serialCtrl(){
    static String receivedData;

    while(Serial.available()){
        char receivedChar =  Serial.read();
        receivedData += receivedChar;
        if(receivedChar == '\n'){
            DeserializationError err = deserializeJson(jsonCmdReceive,receivedData);
            if(err == DeserializationError::Ok){
                // Serial.println(receivedData);
                printf("receivedData: %s",receivedData.c_str());
            }else{
                printf("DeserializationError: %s",receivedData.c_str());
            }
            receivedData = "";
        }
    }
}