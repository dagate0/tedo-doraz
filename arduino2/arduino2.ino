#include &quot;FastIMU.h&quot;
#include &lt;Wire.h&gt;
#define Sensore A0
#define int1 2
#define int2 3
#define IMU_ADDRESS 0x69    //Change to the address of the IMU
#define PERFORM_CALIBRATION
BMI160 IMU;
calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
int valore, rslt, i; 
int umidita;
unsigned long lastMillis = 0;  // Tempo dell&#39;ultima lettura
unsigned long interval = 1000;
void setup() {
  // put your setup code here, to run once:
pinMode(Sensore, INPUT);
pinMode(int1, INPUT);
Wire.begin();
 Wire.setClock(400000); //400khz clock
Serial.begin(115200);
 while (!Serial) {
 ;
 }
 #ifdef PERFORM_CALIBRATION

 Serial.println(&quot;Keep IMU level.&quot;);
 delay(5000);
 IMU.calibrateAccelGyro(&amp;calib);
 Serial.println(&quot;Calibration done!&quot;);
 Serial.println(&quot;Accel biases X/Y/Z: &quot;);
 Serial.print(calib.accelBias[0]);
 Serial.print(&quot;, &quot;);
 Serial.print(calib.accelBias[1]);
 Serial.print(&quot;, &quot;);
 Serial.println(calib.accelBias[2]);
 Serial.println(&quot;Gyro biases X/Y/Z: &quot;);
 Serial.print(calib.gyroBias[0]);


 Serial.print(&quot;, &quot;);
  Serial.print(calib.gyroBias[1]);
 Serial.print(&quot;, &quot;);
 Serial.println(calib.gyroBias[2]);
 delay(5000);
 IMU.init(calib, IMU_ADDRESS);
#endif

}
void loop() {
unsigned long currentMillis = millis();  // Ottieni il tempo corrente

 if (currentMillis - lastMillis &gt;= interval) {  // Se sono passati almeno 1000
ms
 lastMillis = currentMillis;
 if ( digitalRead(int1)==0){
 IMU.update();
 IMU.getAccel(&amp;accelData);
 Serial.println(accelData.accelX);
 Serial.print(&quot;\t&quot;);
  Serial.print(accelData.accelY);
  Serial.print(&quot;\t&quot;);
  Serial.print(accelData.accelZ);
  Serial.print(&quot;\t&quot;);
  IMU.getGyro(&amp;gyroData);
  Serial.print(gyroData.gyroX);
  Serial.print(&quot;\t&quot;);
  Serial.print(gyroData.gyroY);
  Serial.print(&quot;\t&quot;);
  Serial.print(gyroData.gyroZ);
      }
      else
      Serial.println(&quot;accellerometro spento&quot;);
if(digitalRead(int2)==0){
valore = analogRead(Sensore); 
umidita = map(valore, 0, 1023, 0, 100);  // per trasformare in percentuale
Serial.println(String (&quot; \n Umidita: &quot;) + umidita + &quot;%&quot;);
}
      else
      Serial.println(&quot;umidita spento&quot;);
}
}