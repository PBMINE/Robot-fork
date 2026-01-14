# #include <PTBOTAtomVX.h>
#include "Adafruit_TCS34725.h"

// AdfkmndrmrehnhprehrembneewingewonewpgnewpgnewpgnewognpewnpiegnewpgnpewgnpiengiewngpewnhuoebgwNFWQGEAK; EWNGWNVN;EWGWEGVPOWGNEWHGLASKGNWEUGWLNEWOGHELBWHOHWEKBJWUTW'VPKQWGOPWHJ

// Define pins for Wire1 (ESP32 second I2C bus)
// ENC2> SDA1 = 25 | ENC3> SDA1 = 36 | ENC4> SDA1 = 34
// ENC2> SCL1 = 26 | ENC3> SCL1 = 39 | ENC4> SCL1 = 35
#define SDA1 25
#define SCL1 26

// Create an instance of the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);

//                    S0   S1   S2   S3   S4   S5  S6
int sensor_min[] = { 152, 263, 167, 250, 270, 270, 0 };   // ค่าเซ็นเซอร์พื้นสีน้ำเงิน
int sensor_max[] = { 700, 961, 690, 950, 945, 906, 540 };  // ค่าเซ็นเซอร์พื้นสีขาว

float power_factor = 1.0;

int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
float current_degree = 0, current_degree_P = 0;
float previous_error_forward = 0;

///////////////////////////////--หุ่นยนต์ พื้นปกติ--//////////////////////////////////////////////////
int speed = 70;            //ความเร็วมอเตอร์ ปกติ (ความเร็วมอเตอร์ 0-100)
float WalkOneBlock = 525;  //ระยะทางเดิน 1 ช่อง (เวลา 1000 = 1วินาที)

float WalkOneBlock_ColorExit = 340;  //ระยะทางเดิน 1 ช่อง หลังจากหุ่นยนต์หมุน 180 องศา ออกจากพื้นที่วางลูกบาศก์ (เวลา 1000 = 1วินาที)

int speedBack = 50;                  //ความเร็วมอเตอร์ถอยหลังออกจากเส้นดำ (ความเร็วมอเตอร์ 0-100)
float Backword_ExitLineBlack = 255;  //ระยะทาง ถอยออกจากเส้นดำก่อนเลี้ยว (เวลา 1000 = 1วินาที)

int speedSpin = 70;    //ความเร็วเลี้ยว (ความเร็วมอเตอร์ 0-100)
float SpinLeft = 130;  //อาศาเลี้ยวซ้าย (เวลา 1000 = 1วินาที)

float SpinRight = 130;  //อาศาเลี้ยวขวา (เวลา 1000 = 1วินาที)

float Spin180 = 240;  //อาศาเลี้ยว 180 องศา (เวลา 1000 = 1วินาที)

int Distance_color = 135;  //ระยะทาง เข้าเช็คพื้นสีวาง    12Q1  231 Q q1    AQ    ACDFEWQ1  4U6T5ลูกบาศก์ (เวลา 1000 = 1วินาที)
//------------------------------------------------------------------------------------------//

/////////////////////////////--หุ่นยนต์ กรณเจอตะเกียบ--/////////////////////////////////////
float degree_ChS = 3;                 //องศาทางขึ้นตะเกียบ
int Distance_Check_ChopSticks = 150;  //ระยะทางเข้าเช็คว่าเป็นตะเกียบหรือเส้นดำ
int Speed_Chopsticks = 25;            //ความเร็วมอเตอร์ วิ่งบนตะเกียบ (ความเร็วมอเตอร์ 0-100)

int Distance_ChopSticks = 2200;  //ระยะทางเดินข้ามตะเกียบ (เวลา 1000 = 1วินาที)
//------------------------------------------------------------------------------------------//

/////////////////////////////--หุ่นยนต์ กรณเจอสะพาน--/////////////////////////////////////
float degree_Br = 5;            //องศาทางขึ้นสะพาน
int Backword_ExitBridge = 200;  // ระยะทางถอยออกจากบนขอบสะพาน
int Speed_Bridge = 70;          //ความเร็วมอเตอร์ วิ่งบนสะพาน (ความเร็วมอเตอร์ 0-100)

int Distance_Bridge_Up = 1650;     //ระยะทางเดินขึ้นสะพาน + ลงสะพาน (เวลา 1000 = 1วินาที) ทางตรงเท่านั้น
int Distance_Bridge_Down = 1000;  //ระยะทางเดินลงสะพาน (เวลา 1000 = 1วินาที)

float SpinLeft_Bridge = 190;  //อาศาเลี้ยวซ้าย บนสะพาน (เวลา 1000 = 1วินาที)

float SpinRight_Bridge = 185;  //อาศาเลี้ยวขวา บนสะพาน (เวลา 1000 = 1วินาที)

float Spin180_Bridge = 380;  //อาศาเลี้ยว บนสะพาน 180 องศา (เวลา 1000 = 1วินาที)

int BRIDGE_SIDE = 40;  //เซนเซอร์จับด้านข้างสะพาน เข้าใกล้ขอบข้างสะพาน
//------------------------------------------------------------------------------------------//

bool Mode = 0;
int Step = 0;
int C1;
int C2;
int C3;
int C4;
long delayALL = 100;
///////////////////////////////--สิ้นสุดการปรับจูนหุ่นยนต์--//////////////////////////////////////////////////

void setup() {
  initialize();
  lcdClear();
  tft.setRotation(1);
  // Initialize Wire1 with custom SDA and SCL pins
  Wire1.begin(SDA1, SCL1);
  if (tcs.begin(TCS34725_ADDRESS, &Wire1))
    ;
  begin_servo();

//   ShowValue_Sensor_0_1000(); // เช็คค่าสีพื้นขาว-น้ำเงิน
//   ShowValue_Color();         // เช็คค่าสีพื้นที่วางลูกบาศก์ rgb
//   ShowValue_Gyro();          // เช็คค่า Gyro

  while (1) {
    if (knobRead() <= 400) {
      lcdSetTextSize(2);
      lcdPrintText(25, 50, "MOVE LEFT  ", 0xf800);
      Mode = 0;
      if (knobRead() >= 600) lcdClear();
    } else if (knobRead() >= 600) {
      lcdSetTextSize(2);
      lcdPrintText(25, 50, "MOVE RIGHT ", 0xf800);
      Mode = 1;
      if (knobRead() <= 400) lcdClear();
    } else if (knobRead() > 400 && knobRead() < 600) {
      drawBitmap(0, 0, logo, 160, 128);
      if (knobRead() <= 400 || knobRead() >= 600) lcdClear();
    }
    if (switchRead(A) || switchRead(B)) {
      break;
    }
  }

  delay(1000);  // หน่วงเวลาหลังกดปุ่มเริ่มต้น 1000 = 1วินาที
  setAngleOffset();
  current_degree = 0;

  // เช็คบล็อคออกจากสีทึบ START
  while (1) {
    readLine();
    if (line_value[0] >= 3 || line_value[3] >= 3)
      break;
    FF(speed);
  }
  STEP1(WalkOneBlock - 100);
  // STOP();
}

void loop() {
  while (1) {
    // แบบใช้ Gyro เลี้ยว
    if (Step == 0) STEP1(WalkOneBlock);

    else if (Step == 1) {
      if (Mode == 0) spinDegree(-90);
      else spinDegree(90);
      Step = 0;
      // STOP();
    }

    else if (Step == 2) {
      if (Mode == 0) spinDegree(90);
      else spinDegree(-90);
      Step = 0;
    }
  }
  //----------------------------------------//
  /*while (1) {
    // แบบใช้ Timer เลี้ยว
    if (Step == 0) STEP1(WalkOneBlock);

    else if (Step == 1) {
      if (Mode == 0) LL(SpinLeft);
      else RR(SpinRight);
      Step = 0;
    }

    else if (Step == 2) {
      if (Mode == 0) RR(SpinRight);
      else LL(SpinLeft);
      Step = 0;
    }
  }*/
  //----------------------------------------//
}
