#define UNO

#ifdef MICROVIEW
#include <MicroView.h>
MicroViewWidget *slider;
#endif

#include <Servo.h>

#ifdef UNO
#define MOTOR1_PIN 5
#define MOTOR2_PIN 6
#define MOTOR3_PIN 7
#elif defined(MEGA)
#define MOTOR1_PIN 9
#define MOTOR2_PIN 10
#define MOTOR3_PIN 11
#endif

Servo testmotor1;
Servo testmotor2;
Servo testmotor3;
float cur_speed;
bool inc;

void setup() {
  // put your setup code here, to run once:
  testmotor1.attach(MOTOR1_PIN);
  testmotor2.attach(MOTOR2_PIN);
  testmotor3.attach(MOTOR3_PIN);

  cur_speed = 0;
  inc = true;

#ifdef MICROVIEW
  uView.begin();
  uView.clear(PAGE);
  slider = new MicroViewSlider(0, 0, -100, 100);
  uView.display();
#endif
}

void loop() {
  delay(300);

  if (cur_speed == 100) {
    inc = false;
  }
  if (cur_speed == -100) {
    inc = true;
  }
  
  if (inc) {
    cur_speed += 10;
  } else {
    cur_speed -= 10;
  }

  vexMotorWrite(testmotor1, cur_speed);
  vexMotorWrite(testmotor2, cur_speed);
  vexMotorWrite(testmotor3, cur_speed);
#ifdef MICROVIEW
  slider->setValue(cur_speed);
  uView.display();
#endif
}

void vexMotorWrite(Servo motor, int speed) {
  speed = constrain(speed, -100, 100);
  motor.write(map(speed, -100, 100, 1000, 2000));
}

