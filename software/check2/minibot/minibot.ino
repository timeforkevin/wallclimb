#include <Servo.h>

#define MOTOR1_PIN 5
#define MOTOR2_PIN 6
#define MOTOR3_PIN 7

#define LMAX (100)
#define RMAX (-100)

#define SECONDS(x) (1000*x)

Servo leftMotor;
Servo rightMotor;
float cur_speed;
bool inc;

void setup() {
  // put your setup code here, to run once:
  leftMotor.attach(MOTOR1_PIN);
  rightMotor.attach(MOTOR2_PIN);

  // Forwards 5 seconds
  vexMotorWrite(leftMotor, LMAX);
  vexMotorWrite(rightMotor, RMAX);

  delay(SECONDS(5));

  vexMotorWrite(leftMotor, 0);
  vexMotorWrite(rightMotor, 0);

}

void loop() {
}

void vexMotorWrite(Servo motor, int speed) {
  speed = constrain(speed, -100, 100);
  motor.write(map(speed, -100, 100, 1000, 2000));
}

