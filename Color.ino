char color() {
  unsigned int ValueRGB = 100;
  uint16_t r, g, b, c, colorTemp, lux;

  // Get raw data from the sensor
  tcs.getRawData(&r, &g, &b, &c);

  // Calculate color temperature and lux
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  float red, green, blue;
  uint32_t sum = c;
  red = r;
  red /= sum;
  green = g;
  green /= sum;
  blue = b;
  blue /= sum;
  red *= 256;
  green *= 256;
  blue *= 256;

  if (red > ValueRGB + 40 && green < ValueRGB && blue < ValueRGB)
    return 'R';  // สีแดง

  else if (red < ValueRGB && green > ValueRGB + 25 && blue < ValueRGB)
    return 'G';  // สีเขียว

  else if (red < ValueRGB - 30 && green < ValueRGB && blue > ValueRGB + 25)
    return 'B';  // สีน้ำเงิน

  else if (red > ValueRGB && green > ValueRGB && blue < ValueRGB - 45)
    return 'Y';  // สีเหลือง

  else
    return 'E';  // สีขาว สีดำ
}

void Check_Color() {
  while (true) {
    readLine();
    // สีแดง
    if (color() == 'R') {
      tft.fillScreen(ST77XX_RED);
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 10 && line_value[2] >= 10) {
          motorStop();
          break;
        }
      }
      SentBoxRed();
      C1 = 1;
      check_cube();
      BB(30, 100);
      // RR(Spin180);
      spinDegree(90);
      spinDegree(90);
//      delay(delayALL);
//      SetBack(20);
      delay(delayALL);
      STEP1(WalkOneBlock_ColorExit);
      Step = 1;
      break;
    }

    // สีเขียว
    if (color() == 'G') {
      lcdClear();
      tft.fillScreen(ST77XX_GREEN);
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 10 && line_value[2] >= 10) {
          motorStop();
          break;
        }
      }
      SentBoxGreen();
      C2 = 1;
      check_cube();
      BB(30, 100);
      // RR(Spin180);
      spinDegree(90);
      spinDegree(90);
//      delay(delayALL);
//      SetBack(20);
      delay(delayALL);
      STEP1(WalkOneBlock_ColorExit);
      Step = 1;
      break;
    }

    // สีน้ำเงิน
    if (line_value[5] <= 50 && line_value[4] <= 50) {
      tft.fillScreen(ST77XX_BLUE);
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 50 && line_value[2] >= 50) {
          motorStop();
          break;
        }
      }
      SentBoxBlue();
      C3 = 1;
      check_cube();
      BB(20, 100);
      // RR(Spin180);
      spinDegree(90);
      spinDegree(90);
//      delay(delayALL);
//      SetBack(20);
      delay(delayALL);
      STEP1(WalkOneBlock_ColorExit);
      Step = 1;
      break;
    }

    // สีน้ำเงิน
    /*if (color() == 'B') {
      tft.fillScreen(ST77XX_BLUE);
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 10 && line_value[2] >= 10) {
          motorStop();
          break;
        }
      }
      SentBoxBlue();
      C3 = 1;
      check_cube();
      BB(30, 100);
      // RR(Spin180);
      spinDegree(90);
      spinDegree(90);
//      delay(delayALL);
//      SetBack(20);
      delay(delayALL);
      STEP1(WalkOneBlock_ColorExit);
      Step = 1;
      break;
    }*/

    // สีเหลือง
    if (color() == 'Y') {
      tft.fillScreen(ST77XX_YELLOW);
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 10 && line_value[2] >= 10) {
          motorStop();
          break;
        }
      }
      SentBoxYellow();
      C4 = 1;
      check_cube();
      BB(30, 100);
      // RR(Spin180);
      spinDegree(90);
      spinDegree(90);
//      delay(delayALL);
//      SetBack(20);
      delay(delayALL);
      STEP1(WalkOneBlock_ColorExit);
      Step = 1;
      break;
    }

    // สีอื่นๆ
    else {
      current_degree = angleRead(YAW);
      BB(speedBack, Backword_ExitLineBlack);
      Step = 2;
      break;
    }
  }
}

void check_cube() {
  drawBitmap(0, 0, logo, 160, 128);
  if (C1 == 1 && C2 == 1 && C3 == 1 && C4 == 1)
    ServoFlag();
}

void ShowValue_Color() {
  lcdClear();
  lcdSetTextSize(2);
  lcdPrintText(20, 10, "CHECK COLOR", 0xf800);
  lcdSetTextSize(1);
  while (1) {
    uint16_t r, g, b, c, colorTemp, lux;

    // Get raw data from the sensor
    tcs.getRawData(&r, &g, &b, &c);

    // Calculate color temperature and lux
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);
    float red, green, blue;
    uint32_t sum = c;
    red = r;
    red /= sum;
    green = g;
    green /= sum;
    blue = b;
    blue /= sum;
    red *= 256;
    green *= 256;
    blue *= 256;

    lcdPrintText(10, 40, "sensor r =      ", 0xffff);
    lcdPrintText(75, 40, String(red), 0xffff);
    lcdPrintText(10, 60, "sensor g =      ", 0xffff);
    lcdPrintText(75, 60, String(green), 0xffff);
    lcdPrintText(10, 80, "sensor b =      ", 0xffff);
    lcdPrintText(75, 80, String(blue), 0xffff);
    lcdPrintText(10, 100, "color =      ", 0xffff);
    lcdPrintText(75, 100, String(color()), 0xffff);
  }
}
