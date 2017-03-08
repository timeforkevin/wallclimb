#include <Servo.h>

#define MOTOR1_PIN 11
#define MOTOR2_PIN 10
#define MOTOR3_PIN 9

#define SECONDS(x) (1000*x)

Servo liftMotor;
Servo leftMotor;
Servo rightMotor;

void setup() {
  // put your setup code here, to run once:
  liftMotor.attach(MOTOR1_PIN);
  leftMotor.attach(MOTOR2_PIN);
  rightMotor.attach(MOTOR3_PIN);

  // Forwards 5 seconds
  vexMotorWrite(leftMotor, 100);
  vexMotorWrite(rightMotor, 100);

  delay(SECONDS(5));

  // Lift up 3 seconds
  vexMotorWrite(leftMotor, 0);
  vexMotorWrite(rightMotor, 0);

  vexMotorWrite(liftMotor, 100);

  // Done
  delay(SECONDS(3));

  vexMotorWrite(liftMotor, 0);
}

void loop() {
}

void vexMotorWrite(Servo motor, int speed) {
  speed = constrain(speed, -100, 100);
  motor.write(map(speed, -100, 100, 1000, 2000));
}

