/*
 *  Συνάρτηση αρχικοποίησης βιβλιοθήκης Mirf 
 *  για την επικοινωνία με τον πομποδέκτη nRF24l01.
 *  ce:  το pin στην πλατφόρμα του arduino στο οποίο είναι συνδεδεμένο
 *       το pin ce (chip enable) του nRF24l01.
 *  csn: το pin στην πλατφόρμα του arduino στο οποίο είναι συνδεδεμένο
 *       το pin csn (chip select) του nRF24l01.
 */
void initMirf(int ce, int csn){
  Mirf.cePin=ce;
  Mirf.csnPin=csn;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
}

/*
 *  Συνάρτηση ορισμού ρυθμίσεων του πομποδέκτη nRF24L01
 *  μέσω της βιβλιοθήκης Mirf.
 *  address:  αλφαριθμητικό επιθυμητής διεύθυνσης για τον πομποδέκτη.
 *  payload:  το μέγεθος των δεδομένων που πρόκειται να μεταφερθούν σε byte.
 *  channel:  το κανάλι επικοινωνίας που θα χρησιμοποιησεί ο πομποδέκτης.
 *            Διαθέσιμο εύρως τιμών 0-127 με 1MHz διαχωρισμό μεταξύ κάθε καναλιού.
 */
void configMirf(char* address, int payload, int channel){
  Mirf.setRADDR((byte *)address);
  Mirf.payload = payload;
  Mirf.channel = channel;
  Mirf.config();
}


/*
 *  Συνάρτηση αποστολής αιτήματος για έναρξη λήψης δεδομένων.
 *  address:  Η διεύθυνση προς την οποία θα αποσταλλεί το αίτημα.
 *  msg:  Το κείμενο του αιτήματος που θα σταλεί.
 */
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

/*
 *  Συνάρτηση λήψης απάντησης όταν υπάρχουν διαθέσιμα δεδομένα
 *  προς λήψη, πράγμα που συμβολίζεται από την βιβλιοθήκη μέσω της συνάρτησης
 *  Mirf.dataRead().
 *  returns:  αλφαριθμητικό που περιέχει τα δεδομένα, της απάντησης.
 */
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


