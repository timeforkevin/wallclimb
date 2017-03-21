#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

#ifdef MINIBOT

#define LEFTMOTORPIN 5
#define RIGHTMOTORPIN 6

#define LEFTREVERSED false
#define RIGHTREVERSED true

#define LEFTBIAS 1.0
#define RIGHTBIAS 0.55

#endif

#ifdef LIFTBOT

#define LIFTMOTORPIN 11
#define LEFTMOTORPIN 10
#define RIGHTMOTORPIN 9
#define WINCHMOTORPIN 12

#define LEFTREVERSED false
#define RIGHTREVERSED true
#define LIFTREVERSED false
#define WINCHREVERSED false

#endif

#define SPEED_MAX (100)
#define TURN_SPEED (26)
#define PULSE_WIDTH_MIN (1000)
#define PULSE_WIDTH_MAX (2000)

#define SECONDS(x) (1000*x)

class VexMotor : Servo {
  public:
    VexMotor(int motor_pin, bool is_reversed, float bias)
    : Servo() {
      m_motor_pin = motor_pin;
      m_bias = bias;
      if (is_reversed) {
          m_bias *= -1;
      }
    }

    void init() {
      attach(m_motor_pin);
    }

    void VexMotorWrite(float speed) {
      speed = constrain(speed*m_bias, -SPEED_MAX, SPEED_MAX);
      write(map(speed, -SPEED_MAX,       SPEED_MAX,
                       PULSE_WIDTH_MIN,  PULSE_WIDTH_MAX));
    }

  private:
    float m_bias;
    int m_motor_pin;
};

#endif
