/*
 *  Συνάρτηση έναρξης της βιβλιόθηκης Mirf η οποία αρχικοποιεί και ρυθμίζει τις
 *  παραμέτρους του πομποδέκτη nRF24l01.
 *  ce:  το pin στην πλατφόρμα του arduino στο οποίο είναι συνδεδεμένο
 *       το pin ce (chip enable) του nRF24l01.
 *  csn: το pin στην πλατφόρμα του arduino στο οποίο είναι συνδεδεμένο
 *       το pin csn (chip select) του nRF24l01.
 *  Raddr:  αλφαριθμητικό επιθυμητής διεύθυνσης απο την οποία θα λαμβάνονται τα δεδομένα.
 *  Τaddr:  αλφαριθμητικό επιθυμητής διεύθυνσης προς την οποία θα αποστέλονται τα δεδομένα.
 *  channel:  το κανάλι επικοινωνίας που θα χρησιμοποιησεί ο πομποδέκτης.
 *            Διαθέσιμο εύρως τιμών 0-127 με 1MHz διαχωρισμό μεταξύ κάθε καναλιού.
 *  payload:  το μέγεθος των δεδομένων που πρόκειται να μεταφερθούν σε byte.
 */
void startMirf(int ce, int csn, char* Raddr, char* Taddr, int channel, int payload){
#ifdef DEBUG
  Serial.println("Init Mirf");
#endif
  initMirf(ce, csn);
  configMirf(Raddr, Taddr, channel, payload);
}

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
 *  Raddr:  αλφαριθμητικό επιθυμητής διεύθυνσης απο την οποία θα λαμβάνονται τα δεδομένα.
 *  Τaddr:  αλφαριθμητικό επιθυμητής διεύθυνσης προς την οποία θα αποστέλονται τα δεδομένα.
 *  channel:  το κανάλι επικοινωνίας που θα χρησιμοποιησεί ο πομποδέκτης.
 *            Διαθέσιμο εύρως τιμών 0-127 με 1MHz διαχωρισμό μεταξύ κάθε καναλιού.
 *  payload:  το μέγεθος των δεδομένων που πρόκειται να μεταφερθούν σε byte.
 */
void configMirf(char* Raddr, char* Taddr, int channel, int payload){
  Mirf.setRADDR((byte *)Raddr);
  Mirf.setTADDR((byte *)Taddr);
  Mirf.channel = channel;
  Mirf.payload = payload;
  Mirf.config();
}

/*
 *  Συνάρτηση μεταφοράς των μετρήσεων που βρίσκονται αποθηκευμένες στην παγκόσμια
 *  μεταβλητή s εάν όμως έχει γίνει αίτημα προς λήψη απο τον συγκεκριμένο κόμβο-πελάτη.
 *  returns: λογική ένδειξη (true/false) για την επιτυχής ή όχι αποστολής των δεδομένων.
 */
boolean transmitDataWord(){
  String req = waitRequest();
  if(req == "REQ1"){
#ifdef DEBUG
    Serial.println("\nGot Request: " + req);
#endif
    sendData(s, 0, (s.length()/2)+1);
    return false;
  } 
  else if(req == "SEC1") {
#ifdef DEBUG
    Serial.println("\nGot Request: " + req);
#endif
    sendData(s, (s.length()/2), s.length()+1);
    return true;
  }
}

/*
 * Συνάρτηση αναμονής λήψης αιτήματος μετάδοσης μετρήσεων. Διαβάζει τα δεδομένα
 * που είναι διαθέσιμα προς παραλαβεί απο τον nRF24l01.
 * returns:  τα δεδομένα που λήφθηκαν (πιθανό αίτημα για αποστολή δεδομένων).
 */
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

/*
 *  Συνάρτηση αποστολής δεδομένων των μετρήσεων
 *  data:  αλφαριθμητικό με τα δεδομένα προς αποστολή.
 *  start:  αρχική θέση στο αλφαριθμητικό απο την οποία θα αρχίσουν να
 *         αποστέλλονται τα δεδομένα.
 *  length: μήκος των δεδομένων που θα σταλούν αρχίζοντας απο την θέση που
 *          ορίζεται απο την μεταβλητή start. 
 */
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





