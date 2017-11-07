void gatherSensorDataDemo(){
  RawTemp+=1;//random(0,50);
  RawHum+=1;//random(0,100);
  RawX+=1;//random(0,255);
  RawY+=1;//random(0,255);
  RawZ+=1;//random(0,255);
  RawAccelX+=1;//random(0,4);
  RawAccelY+=1;//random(0,4);
  RawAccelZ+=1;//random(0,4);
  delay(random(500,4000));
}


void createDataWord(){
  s += round(RawTemp);
  s += ":";
  s += round(RawHum);
  s += ":";
  s += round(angleZ);
  s += ":";
  s += round(angleY);
  s += ":";
  s += round(angleX);
  s += ":";
  s += round(RawAccelX);
  s += ":";
  s += round(RawAccelY);
  s += ":";
  s += round(RawAccelZ);
#ifdef DEBUG
  Serial.println(s);
#endif
}

