void dmpDataReady() {
  mpuInterrupt = true;
}


void startMPU6050(){
#ifdef DEBUG
  Serial.println("Init MPU");
#endif
  initMPU();
#ifdef DEBUG
  Serial.println("Enable Test");
#endif
  initTests();
#ifdef DEBUG
  Serial.println("Calibration");
#endif
  initCalibration(16);
#ifdef DEBUG
  Serial.println("Init DMP");
#endif
  initDMP();
#ifdef DEBUG
  Serial.println("Disable Test");
#endif
  stopTests();
#ifdef DEBUG
  Serial.println("Warming UP");
#endif
  //doWarmUp();
}

void initMPU(){
  do{
    mpu.initialize();
  }
  while(!mpu.testConnection());
}

void initTests(){
  mpu.setAccelXSelfTest(true);
  mpu.setAccelYSelfTest(true);
  mpu.setAccelZSelfTest(true); 
}

void initCalibration(int mode){
  mpu.setDLPFMode(mode);
}

void initDMP(){
  do{
    devStatus = mpu.dmpInitialize();
  }
  while(devStatus!=0);
  mpu.setDMPEnabled(true);
  attachInterrupt(0, dmpDataReady, RISING);
  mpuIntStatus = mpu.getIntStatus();
  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
}

void stopTests(){
  mpu.setAccelXSelfTest(false);
  mpu.setAccelYSelfTest(false);
  mpu.setAccelZSelfTest(false);
}

void waitAndReadAccelGyro(){
  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize);

  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    return;
  } 
  else if ((mpuIntStatus & 0x02) || fifoCount+4==1024) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    getAccelGyroData();
    fifoCount -= packetSize;
    return;
  }
}

void getAccelGyroData(){
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetAccel(&aa, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
  RawX = ypr[0] * 180/M_PI;
  RawY = ypr[1] * 180/M_PI;
  RawZ = ypr[2] * 180/M_PI;
  RawAccelX = aaReal.x / 4096.0;
  RawAccelY = aaReal.y / 4096.0;
  RawAccelZ = aaReal.z / 4096.0;
}

void gatherSamples(int N){
  for(int i=0;i<N;i++) waitAndReadAccelGyro();
}

void doWarmUp(){
  for(int i=0;i<2000;i++){
    waitAndReadAccelGyro();
  }
  //warmup = false;
  waitAndReadAccelGyro();
}

void sleepAccelGyro(){
  mpu.setSleepEnabled(true);
}

void wakeAccelGyro(){
  mpu.setSleepEnabled(false);
}




