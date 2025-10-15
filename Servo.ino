//----------------เซ็ตค่าเซอร์โว 0 ตัวซ้าย------------------//
int ServoLock0 = 100;   //ค่าเซอร์โวเริ่มต้น ตัวซ้าย Servo0   100
int ServoDrop1 = 135;  //ค่าเซอร์โวปล่อยลูกบาศก์สีแดงช่อง1 SV0
int ServoDrop2 = 60;   //ค่าเซอร์โวปล่อยลูกบาศก์สีเขียวช่อง2 SV0
//----------------เซ็ตค่าเซอร์โว 1 ตัวขวา------------------//
int ServoLock1 = 100;   //ค่าเซอร์โวเริ่มต้น ตัวขวา Servo1    100
int ServoDrop3 = 140;  //ค่าเซอร์โวปล่อยลูกบาศก์สีน้ำเงินช่อง3 SV2
int ServoDrop4 = 65;   //ค่าเซอร์โวปล่อยลูกบาศก์สีเหลืองช่อง4 SV2
//----------------เซ็ตค่าเซอร์โว 2 ยกธง-------------------//
int ServoLock_Flag = 90;  //ค่าเซอร์โวเริ่มต้น ธง SV2

void begin_servo() {
  servoWrite(0, ServoLock0);
  servoWrite(1, ServoLock1);
  servoWrite(2, ServoLock_Flag);
}
void SentBoxRed() {
  servoWrite(0, ServoDrop1);
  delay(300);
  servoWrite(0, ServoLock0);
}
void SentBoxGreen() {
  servoWrite(0, ServoDrop2);
  delay(300);
  servoWrite(0, ServoLock0);
}
void SentBoxBlue() {
  servoWrite(1, ServoDrop3);
  delay(300);
  servoWrite(1, ServoLock1);
}
void SentBoxYellow() {
  servoWrite(1, ServoDrop4);
  delay(300);
  servoWrite(1, ServoLock1);
}
void ServoFlag() {
  while (true) {
    servoWrite(2, 40);
    delay(250);
    servoWrite(2, 0);
    delay(250);
  }
}
