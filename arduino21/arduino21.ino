#include "FastIMU.h"
#include <Wire.h>
#define Sensore A0
#define int1 3
#define int2 4
#define int3 5
#define vibra 2
#define IMU_ADDRESS 0x69    //Change to the address of the IMU
#define PERFORM_CALIBRATION
BMI160 IMU;
calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
int valore, rslt, i; 
int umidita;
unsigned long lastMillis = 0;
unsigned long interval = 1000;
volatile bool vibrazioneRilevata = false;
void setup() {
  // put your setup code here, to run once:
pinMode(Sensore, INPUT);
pinMode(int1, INPUT_PULLUP);
pinMode(int2, INPUT);
pinMode(int3, INPUT);
pinMode(vibra, INPUT);
Wire.begin();
 attachInterrupt(digitalPinToInterrupt(vibra), allarme, FALLING);
 Wire.setClock(400000); //400khz clock
Serial.begin(115200);
 while (!Serial) {
 ;
 }
 #ifdef PERFORM_CALIBRATION

 Serial.println("Keep IMU level.");
 delay(5000);
 IMU.calibrateAccelGyro(&calib);
 Serial.println("Calibration done!");
 Serial.println("Accel biases X/Y/Z: ");
 Serial.print(calib.accelBias[0]);
 Serial.print(", ");
 Serial.print(calib.accelBias[1]);
 Serial.print(", ");
 Serial.println(calib.accelBias[2]);
 Serial.println("Gyro biases X/Y/Z: ");
 Serial.print(calib.gyroBias[0]);


 Serial.print(", ");
  Serial.print(calib.gyroBias[1]);
 Serial.print(", ");
 Serial.println(calib.gyroBias[2]);
 delay(5000);
 IMU.init(calib, IMU_ADDRESS);
#endif

}
void loop() {
unsigned long currentMillis = millis();  // Ottieni il tempo corrente

 if (currentMillis - lastMillis >= interval) {  // Se sono passati almeno 1000
 lastMillis = currentMillis;
 if ( digitalRead(int1)==0){
 IMU.update();
 IMU.getAccel(&accelData);
 Serial.println(accelData.accelX);
 Serial.print("\t");
 Serial.print(accelData.accelY);
 Serial.print("\t");
 Serial.print(accelData.accelZ);
 Serial.print("\t");
 IMU.getGyro(&gyroData);
 Serial.print(gyroData.gyroX);
 Serial.print("\t");
 Serial.print(gyroData.gyroY);
 Serial.print("\t");
 Serial.print(gyroData.gyroZ);
}
else
 Serial.println("accellerometro spento");
 if(digitalRead(int2)==0){
 valore = analogRead(Sensore); 
 umidita = map(valore, 0, 1023, 0, 100);  // per trasformare in percentuale
 Serial.println(String (" \n Umidita: ") + umidita + "%");
}
else
 Serial.println("umidita spento");
}
if (vibrazioneRilevata) {
  if ( digitalRead(int3)==0)
    Serial.println("vibrazione spento");
  
   if ( digitalRead(int3)==0){
    Serial.println("ATTENZIONE: Vibrazione rilevata!");
    vibrazioneRilevata = false;
    delay(200); 
    }
  }
}
void allarme() {
  vibrazioneRilevata = true;
}
