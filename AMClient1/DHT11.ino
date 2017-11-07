/*
 *  Συνάρτηση αρχικοποίησης βιβλιοθήκης DHT.h για επικοινωνία
 *  με τον αισθητήρα θερμοκρασίας-υγρασίας.
 */
void initDHT(){
  dht.begin();
}

/*
 *  Συνάρτηση λήψης μετρήσεων θερμοκρασίας και υγρασίας
 *  και αποθήκευσης τους στις αντίστοιχες μεταβλητές RawTemp, RawHum.
 */
void getTempNHumReadOut(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(t) || isnan(h)){
    RawTemp = 0;
    RawHum = 0;
  }
  else{
    RawTemp = t;
    RawHum = h;
  }
}
