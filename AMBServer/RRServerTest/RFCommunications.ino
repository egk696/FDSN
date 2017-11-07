void initMirf(int ce, int csn){
  Mirf.cePin=ce;
  Mirf.csnPin=csn;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
}

void configMirf(char* address, int payload, int channel){
  Mirf.setRADDR((byte *)address);
  Mirf.payload = payload;
  Mirf.channel = channel;
  Mirf.config();
}

void sendRequest(char* address, String msg){
  byte buffer[Mirf.payload];
  //unsigned long time = millis();
  Mirf.setTADDR((byte *)address);
  msg.getBytes(buffer, msg.length()+1);
  Mirf.send(buffer);
#ifdef DEBUG
  Serial.println("Sending request: " + msg);
#endif
  while(Mirf.isSending());
#ifdef DEBUG
  Serial.println("Request Sent");
#endif

}

String getResponse(){
  byte buffer[Mirf.payload];
  unsigned long time = millis();
#ifdef DEBUG
  Serial.println("Waiting for response");
#endif
  while(!Mirf.dataReady()){
    if((millis() - time) > 1000){
      return "";
    }
    continue;
  }
  Mirf.getData(buffer);
#ifdef DEBUG
  Serial.print("Got Data: ");
  Serial.println((char*) buffer + '\0');
#endif
  return (char *) buffer;
}


