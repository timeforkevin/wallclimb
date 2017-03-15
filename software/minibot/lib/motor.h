#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

#ifdef MINIBOT

#define LEFTMOTORPIN 5
#define RIGHTMOTORPIN 6

#define LEFTREVERSED false
#define RIGHTREVERSED true

#define LEFTBIAS 1.0
#define RIGHTBIAS 0.65

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
#define TURN_SPEED (30)
#define PULSE_WIDTH_MIN (1000)
#define PULSE_WIDTH_MAX (2000)

#define SECONDS(x) (1000*x)

class VexMotor : Servo {
  public:
    VexMotor(int motor_pin, bool is_reversed, float bias)
    : Servo() {
      m_bias = bias;
      m_motor_pin = motor_pin;
      m_is_reversed = is_reversed;
    }

    void init() {
      attach(m_motor_pin);
    }

    void VexMotorWrite(float speed) {
      if (m_is_reversed) {
      	speed *= -m_bias;
      } else {
        speed *= m_bias;
      }
      speed = constrain(speed, -SPEED_MAX, SPEED_MAX);
      
      write(map(speed, -SPEED_MAX,       SPEED_MAX, 
                       PULSE_WIDTH_MIN,  PULSE_WIDTH_MAX));
    }

  private:
    float m_bias;
    int m_motor_pin;
    bool m_is_reversed;
};

#endif