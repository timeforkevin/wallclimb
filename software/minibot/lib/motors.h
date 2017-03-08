#ifndef MOTORS_H
#define MOTORS_H

#include <Servo.h>

#ifdef MINIBOT

#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6

#define LEFTREVERSED false
#define RIGHTREVERSED true

#endif

#ifdef LIFTBOT

#define LIFT_MOTOR_PIN 11
#define LEFT_MOTOR_PIN 10
#define RIGHT_MOTOR_PIN 9

#define LEFTREVERSED false
#define RIGHTREVERSED true
#define LIFTREVERSED false

#endif

#define SPEED_MAX (100)
#define PULSE_WIDTH_MIN (1000)
#define PULSE_WIDTH_MAX (2000)

#define SECONDS(x) (1000*x)

class VexMotor : Servo {
  public:
  	VexMotor(bool is_reversed)
  	: Servo() {
  		m_is_reversed = is_reversed;
  	}

  	void VexMotorWrite(int speed) {
  	  if (m_is_reversed) {
  	  	speed *= -1;
  	  }
  	  speed = constrain(speed, -SPEED_MAX, SPEED_MAX);
      
      write(map(speed, -SPEED_MAX,       SPEED_MAX, 
                       PULSE_WIDTH_MIN,  PULSE_WIDTH_MAX));
  	}
  private:
  	bool m_is_reversed;
};

#endif