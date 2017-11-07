void initDHT(){
  dht.begin();
}

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
