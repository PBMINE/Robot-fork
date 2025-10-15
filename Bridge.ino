void Bridge() {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = Speed_Bridge;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 0.1;         // KD
  int ramp_up = 50;       // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 50;     // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = Distance_Bridge_Up - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;

    readLine();
    if (elapsed_time >= Distance_Bridge_Up * power_factor) {
      motorStop();
      Step = 1;
      break;
    }

    if (line_value[1] <= 1 && line_value[2] <= 1) {
      motorStop();
      // beep(200);
      // STOP();
      SetFront(speedBack, Backword_ExitBridge + 100);
      if (Mode == 0) spinDegree(-90);
      else spinDegree(90);
      Bridge2();
      break;
    }

    if (line_value[0] >= 3 && line_value[3] >= 3) {
      FF(Speed_Bridge);
    } else if (line_value[0] <= 2 && line_value[3] >= 3) {
      motorWrite(50, 50, 0, 0);
      // delay(100);
    } else if (line_value[0] >= 3 && line_value[3] <= 2) {
      motorWrite(0, 0, 50, 50);
      // delay(100);
    }

    previous_error = error;
  }
}

void Bridge2() {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = Speed_Bridge;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 0.1;         // KD
  int ramp_up = 50;       // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 50;     // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = Distance_Bridge_Down - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;

    readLine();
    if (elapsed_time >= Distance_Bridge_Down * power_factor) {
      motorStop();
      Step = 1;
      break;
    }

    if (line_value[1] <= 1 && line_value[2] <= 1) {
      motorStop();
      SetFront(speedBack, Backword_ExitBridge + 100);
      spinDegree(90);
      spinDegree(90);
//      LL(Spin180_Bridge);
//      SetBack(30, Backword_ExitLineBlack);
      Bridge3();
      break;
    }

    if (line_value[0] >= 3 && line_value[3] >= 3) {
      FF(Speed_Bridge);
    } else if (line_value[0] <= 2 && line_value[3] >= 3) {
      motorWrite(50, 50, 0, 0);
      // delay(100);
    } else if (line_value[0] >= 3 && line_value[3] <= 2) {
      motorWrite(0, 0, 50, 50);
      // delay(100);
    }

    previous_error = error;
  }
}

void Bridge3() {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = Speed_Bridge;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 0.1;         // KD
  int ramp_up = 50;       // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 50;     // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = Distance_Bridge_Down - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;

    readLine();
    if (elapsed_time >= Distance_Bridge_Down * power_factor) {
      motorStop();
      Step = 1;
      break;
    }

    if (line_value[1] <= 1 && line_value[2] <= 1) {
      motorStop();
      SetFront(speedBack, Backword_ExitBridge + 100);
      if (Mode == 0) spinDegree(90);
      else spinDegree(-90);
      FF(Speed_Bridge, Distance_Bridge_Down);
      Step = 1;
      break;
    }

    if (line_value[0] >= 3 && line_value[3] >= 3) {
      FF(Speed_Bridge);
    } else if (line_value[0] <= 2 && line_value[3] >= 3) {
      motorWrite(50, 50, 0, 0);
      // delay(100);
    } else if (line_value[0] >= 3 && line_value[3] <= 2) {
      motorWrite(0, 0, 50, 50);
      // delay(100);
    }

    previous_error = error;
  }
}
