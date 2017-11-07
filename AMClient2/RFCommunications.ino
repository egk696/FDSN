void startMirf(int ce, int csn, char* Raddr, char* Taddr, int channel, int payload){
#ifdef DEBUG
  Serial.println("Init Mirf");
#endif
  initMirf(ce, csn);
  configMirf(Raddr, Taddr, channel, payload);
}

void initMirf(int ce, int csn){
  Mirf.cePin=ce;
  Mirf.csnPin=csn;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
}

void configMirf(char* Raddr, char* Taddr, int channel, int payload){
  Mirf.setRADDR((byte *)Raddr);
  Mirf.setTADDR((byte *)Taddr);
  Mirf.channel = channel;
  Mirf.payload = payload;
  Mirf.config();
}

boolean transmitDataWord(){
  String req = waitRequest();
  if(req == "REQ2"){
#ifdef DEBUG
    Serial.println("\nGot Request: " + req);
#endif
    sendData(s, 0, (s.length()/2)+1);
    return false;
  } 
  else if(req == "SEC2") {
#ifdef DEBUG
    Serial.println("\nGot Request: " + req);
#endif
    sendData(s, (s.length()/2), s.length()+1);
    return true;
  }
}


String waitRequest(){
  unsigned long time = millis();
  byte buffer[Mirf.payload];
#ifdef DEBUG
  Serial.println("Waiting for request");
#endif
  while(!Mirf.dataReady());
  Mirf.getData(buffer);
  return (char*) buffer;
}

void sendData(String data, int start, int length){
  byte buffer[Mirf.payload];
  char dataWordChar[Mirf.payload];

  data.substring(start, length).toCharArray(dataWordChar, length-start);

  for(int i=0;i<Mirf.payload;i++){
    buffer[i] = byte(dataWordChar[i]);
  }

  Mirf.send(buffer);
#ifdef DEBUG
  Serial.print("Sending response: ");
  Serial.println((char*) buffer);
#endif
  while(Mirf.isSending());
#ifdef DEBUG
  Serial.println("\nResponse sent");
#endif
}





