void initMPU6050(int calib_accel, int calib_gyro){
  do{
    mpu.initialize();
    mpu.setDLPFMode(16);
    mpu.setFullScaleAccelRange(calib_accel);
    mpu.setFullScaleGyroRange(calib_gyro);
  }
  while(!mpu.testConnection());
  if(calib_accel == 0){
    sensitivityA = 16384;
  }
  else if(calib_accel == 1){
    sensitivityA = 8192;
  }
  else if(calib_accel == 2){
    sensitivityA = 4096;
  }
  else if(calib_accel == 3){
    sensitivityA = 2048;
  }
  if(calib_gyro == 0){
    sensitivityG = 131;
  }
  else if(calib_gyro == 1){
    sensitivityG = 65.5;
  }
  else if(calib_gyro == 2){
    sensitivityG = 32.8;
  }
  else if(calib_gyro == 3){
    sensitivityG = 16.4;
  }
  calculateYPR();
  gyroAngleX = accelAngleX;
  gyroAngleY = accelAngleY;
  gyroAngleZ = accelAngleZ;
  angleX = accelAngleX;
  angleY = accelAngleY;
  angleZ = accelAngleZ;
  timer = micros();
}

void getAccelGyroDataRaw(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  calculateGyroRates();
  calculateGyroAngles();
  calculateAccel();
  calculateYPR();
  calculateAngles();
}

void calculateGyroRates(){
  RawX = float(gx)/sensitivityG;
  RawY = float(gy)/sensitivityG;
  RawZ = float(gz)/sensitivityG;
}

void calculateGyroAngles(){
  gyroAngleX += RawX*(micros()-timer)/1000000;
  gyroAngleY += RawY*(micros()-timer)/1000000;
  gyroAngleZ += RawZ*(micros()-timer)/1000000;
}

void calculateAccel(){
  RawAccelX = (float)ax/sensitivityA;
  RawAccelY = (float)ay/sensitivityA;
  RawAccelZ = (float)az/sensitivityA;
}

void calculateYPR(){
  accelAngleX = (atan2(RawAccelY, RawAccelZ))*RAD_TO_DEG; // Roll
  accelAngleY = (atan2(RawAccelX, RawAccelZ))*RAD_TO_DEG; // Pitch
  accelAngleZ = (atan2(RawAccelX, RawAccelY)-PI/2)*RAD_TO_DEG; //Yaw
}

//Complementary Filter
void calculateAngles(){
  angleX = (0.93*(angleX+(RawX*(float)(micros()-timer)/1000000)))+(0.07*accelAngleX); //Roll
  angleY = (0.93*(angleY+(RawY*(float)(micros()-timer)/1000000)))+(0.07*accelAngleY); //Pitch
  angleZ = (0.93*(angleZ+(RawZ*(float)(micros()-timer)/1000000)))+(0.07*accelAngleZ); //Yaw
}
