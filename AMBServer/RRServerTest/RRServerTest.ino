//RR
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define StatusLed 9
//#define DEBUG

String data, part1, part2, DataWord;


void setup(){
  Serial.begin(57600);
  initMirf(8, 10);
  configMirf("serv1", 32, 90);
#ifdef DEBUG
  Serial.println("Server opened");
  Serial.println("--------------");
#endif
}

void loop(){
#ifdef DEBUG
  Serial.println("--------------");
  Serial.println("--------------");
#endif
  digitalWrite(StatusLed, HIGH);
  configMirf("serv1", 32, 90);
  receiveDataWord(1);
  DataWord=data;
  digitalWrite(StatusLed, LOW);
#ifdef DEBUG
  Serial.println("--------------");
  Serial.println("--------------");
#endif 
  digitalWrite(StatusLed, HIGH);
  configMirf("serv2", 32, 95);
  receiveDataWord(2);
  DataWord=DataWord+"+"+data+"$";
  digitalWrite(StatusLed, LOW);
#ifdef DEBUG
  Serial.println("--------------");
#endif
  Serial.println(DataWord);
}




