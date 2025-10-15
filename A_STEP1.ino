void STEP1(float timer) {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 0.1;         // KD
  int ramp_up = 50;       // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 50;     // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  bool num = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
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

    current_degree_P = angleRead(PITCH);
    if (current_degree_P > 180) current_degree_P -= 360;
    else if (current_degree_P < -180) current_degree_P += 360;

    readLine();
    // ในกรณีเจอพื้นสีขาว และเจอ จุดเช็คพ้อยท์ จะเดินข้าม
    if (line_value[1] > 3 || line_value[2] > 3) {
      motorWrite(speed_left, speed_left, speed_right, speed_right);
    }
    // ในกรณีเจอเส้นดำ และเจอพื้นที่วางลูกบาศก์
    if (line_value[1] <= 2 && line_value[2] <= 2) {
      while (1) {
        int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
        int max_speed = 20;     // ความเร็วสูงสุด
        float kp = 2.5;         // KP
        float kd = 0.1;         // KD
        int ramp_up = 50;       // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
        int ramp_down = 50;     // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
        int current_speed = min_speed;
        unsigned long timer_forward = millis();
        float previous_error = 0;
        while (1) {
          unsigned long elapsed_time = millis() - timer_forward;
          unsigned long remaining_time = Distance_Check_ChopSticks - elapsed_time;
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
          motorWrite(speed_left, speed_left, speed_right, speed_right);
          if (elapsed_time >= Distance_Check_ChopSticks * power_factor) {
            motorStop();
            break;
          }

          current_degree_P = angleRead(PITCH);
          if (current_degree_P > 180) current_degree_P -= 360;
          else if (current_degree_P < -180) current_degree_P += 360;
          if (current_degree_P >= degree_ChS) { num += 1; break; }

          previous_error = error;
        }
        break;
      }

      if (num >= 1) {
        ChopSticks();
        break;
      } else if (num < 1) {
        motorStop();
        delay(delayALL);
        BB(30, Distance_Check_ChopSticks+50);
        SetFront(20);
        FF(20, Distance_color);
        delay(delayALL+100);
        Check_Color();
        break;
      }
    }
    // เดินครบ 1 บ็อก ก็จะหยุดนิ่งและทำ Step ต่อไป
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      delay(delayALL);
      Step = 1;
      break;
    }

    // เจออุปสรรค ตะเกียบ และสะพาน
    readLine();
    if (current_degree_P >= degree_ChS && current_degree_P <= degree_ChS + 3 &&
        line_value[0] <= 40 && line_value[3] <= 40) {
      motorStop();
      delay(delayALL);
      while (1) {
        current_degree_P = angleRead(PITCH);
        if (current_degree_P > 180) current_degree_P -= 360;
        else if (current_degree_P < -180) current_degree_P += 360;

        if (current_degree_P <= degree_ChS) {
          ChopSticks();
          break;
        } else if (current_degree_P >= degree_Br && current_degree_P <= degree_Br + 10) {
          Bridge();
          break;
        }
      }
      break;
    }

    // เจออุปสรรค สะพาน
    if (current_degree_P >= degree_Br) {
      motorStop();
      delay(delayALL);
      while (1) {
        current_degree_P = angleRead(PITCH);
        if (current_degree_P > 180) current_degree_P -= 360;
        else if (current_degree_P < -180) current_degree_P += 360;

        if (current_degree_P <= degree_ChS) {
          ChopSticks();
          break;
        } else if (current_degree_P >= degree_Br && current_degree_P <= degree_Br + 10) {
          Bridge();
          break;
        }
      }
    }

    // เจออุปสรรค ด้านข้างสะพาน
    if (line_value[6] >= BRIDGE_SIDE) {
      BB(speedBack, Backword_ExitLineBlack);
      delay(delayALL);
      Step = 2;
      break;
    }
    previous_error = error;
  }
}
