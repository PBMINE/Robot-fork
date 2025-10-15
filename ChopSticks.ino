void ChopSticks() {
  FF(Speed_Chopsticks, Distance_ChopSticks);
  delay(delayALL);
  // ถ้าในกรณีเป็นพื้นสีขาว
  while (1) {
    if (color() == 'R') {
      tft.fillScreen(ST77XX_RED);
      C1 = 1;
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 50 && line_value[2] >= 50) {
          motorStop();
          break;
        }
      }
      SentBoxRed();
      check_cube();
      // BB(20, 100);
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

    if (color() == 'G') {
      tft.fillScreen(ST77XX_GREEN);
      C2 = 1;
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 50 && line_value[2] >= 50) {
          motorStop();
          break;
        }
      }
      SentBoxGreen();
      check_cube();
      // BB(20, 100);
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

    if (color() == 'B') {
      tft.fillScreen(ST77XX_BLUE);
      C3 = 1;
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 50 && line_value[2] >= 50) {
          motorStop();
          break;
        }
      }
      SentBoxBlue();
      check_cube();
      // BB(20, 100);
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

    readLine();
    if (color() == 'Y' && line_value[0] <= 2 && line_value[1] <= 2 && line_value[2] <= 2 && line_value[3] <= 2) {
      tft.fillScreen(ST77XX_YELLOW);
      C4 = 1;
      while (1) {
        readLine();
        BB(speedBack);
        if (line_value[1] >= 50 && line_value[2] >= 50) {
          motorStop();
          break;
        }
      }
      SentBoxYellow();
      check_cube();
      // BB(20, 100);
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
    else { //if (color() == 'E') {
      motorStop();
      Step = 1;
      break;
    }
  }
}
