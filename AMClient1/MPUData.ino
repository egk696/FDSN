/*
 *  Συνάρτηση αρχικοποίησης του αισθητήρα γυροσκοπίου-αξελερόμετρου MPU6050
 *  με την χρήση των βιβλιοθηκών MPU6050_6Axis_MotionApps20.h και I2Cdev.h
 *  calib_accel:  ρύθμιση ευαισθησίας αξελερόμετρου.
 *  calib_gyro: ρύθμιση ευαισθησίας γυροσκόπιου.
 */
void initMPU6050(int calib_accel, int calib_gyro){
  do{
    mpu.initialize();
    mpu.setDLPFMode(16);
    mpu.setFullScaleAccelRange(calib_accel);
    mpu.setFullScaleGyroRange(calib_gyro);
  }
  while(!mpu.testConnection());
  if(calib_accel == 0){
    sensitivityA = 16384.0;
  }
  else if(calib_accel == 1){
    sensitivityA = 8192.0;
  }
  else if(calib_accel == 2){
    sensitivityA = 4096.0;
  }
  else if(calib_accel == 3){
    sensitivityA = 2048.0;
  }
  if(calib_gyro == 0){
    sensitivityG = 131.0;
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

/*
 *  Συνάρτηση λήψης δεδομένων απο τον αισθητήρα MPU6050, υπολογισμού του κόμβου στους 3 άξονες
 *  και αποθήκευσης των μετρήσεων στις μεταβλητές angleX, angleY, angleZ και RawAccelX, RawAccelY, RawAccelZ.
 */
void getAccelGyroDataRaw(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  calculateGyroRates();
  calculateGyroAngles();
  calculateAccel();
  calculateYPR();
  calculateAngles();
}

/*
 *  Συνάρτηση υπολογισμού του ρυθμού περιστροφής του γυροσκοπίου βάση της επιλεχθίσας ευαισθησίας. 
 */
void calculateGyroRates(){
  RawX = float(gx)/sensitivityG;
  RawY = float(gy)/sensitivityG;
  RawZ = float(gz)/sensitivityG;
}

/*
 *  Συνάρτηση υπολογισμού γωνίας κλίσης στους άξονες βάση μόνο των δεδομένων του γυροσκοπίου. 
 *    ang = gyroData * Δt / 1000000
 */
void calculateGyroAngles(){
  gyroAngleX += RawX*(micros()-timer)/1000000;
  gyroAngleY += RawY*(micros()-timer)/1000000;
  gyroAngleZ += RawZ*(micros()-timer)/1000000;
}

/*
 *  Συνάρτηση υπολογισμού της επιτάχυνσης βάση της επιλεχθίσας ευαισθησίας.
 */
void calculateAccel(){
  RawAccelX = (float)ax/sensitivityA;
  RawAccelY = (float)ay/sensitivityA;
  RawAccelZ = (float)az/sensitivityA;
}

/*
 * Συνάρτηση υπολογισμού της γωνίας κλίσης του κόβμου-ασθενή βάση μόνο των δεδομένων του αξελερόμετρου.
 */
void calculateYPR(){
  accelAngleX = (atan2(RawAccelY, RawAccelZ))*RAD_TO_DEG; // Roll
  accelAngleY = (atan2(RawAccelX, RawAccelZ))*RAD_TO_DEG; // Pitch
  accelAngleZ = (atan2(RawAccelX, RawAccelY)-PI/2)*RAD_TO_DEG; //Yaw
}


/*
 *  Συνάρτηση υπολογισμού της γωνίας κλίσης του κόμβου-ασθενή με την χρήση του συμπληρωματικού φίλτρου.
 *    θ = 0.93 * (angle + gyroData * dt) + 0.07*accelData
 */
void calculateAngles(){
  angleX = (0.93*(angleX+(RawX*(float)(micros()-timer)/1000000)))+(0.07*accelAngleX); //Roll
  angleY = (0.93*(angleY+(RawY*(float)(micros()-timer)/1000000)))+(0.07*accelAngleY); //Pitch
  angleZ = (0.93*(angleZ+(RawZ*(float)(micros()-timer)/1000000)))+(0.07*accelAngleZ); //Yaw
}
