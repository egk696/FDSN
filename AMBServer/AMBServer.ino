#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#define StatusLed 9
//#define DEBUG
//#define TIMED

String data, part1, part2, DataWord;

/*
 *  Συνάρτηση αρχικοποίησης του προγράμματος.
 */
void setup(){
  Serial.begin(115200);
  initMirf(8, 10);
  configMirf("serv1", 32, 90);
#ifdef DEBUG
  Serial.println("Server opened");
  Serial.println("--------------");
#endif
}

/*
 *  Συνάρτηση εκτέλεσης του προγράμματος.
 */
void loop(){
#ifdef TIMED
  Tstart = micros();
#endif
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
#ifdef TIMED
  Serial.println(micros()-Tstart);
#endif
}




