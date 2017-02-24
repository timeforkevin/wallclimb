#include <MicroView.h>
#include <Servo.h>

#define MOTOR_PIN 3

MicroViewWidget *slider;
Servo testmotor;
float cur_speed;
bool inc;

void setup() {
  // put your setup code here, to run once:
  testmotor.attach(MOTOR_PIN);

  cur_speed = 0;
  inc = true;

  uView.begin();
  uView.clear(PAGE);
  slider = new MicroViewSlider(0, 0, -100, 100);
  uView.display();
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

  vexMotorWrite(testmotor, cur_speed);
  slider->setValue(cur_speed);
  uView.display();
  
}

void vexMotorWrite(Servo motor, int speed) {
  speed = constrain(speed, -100, 100);
  motor.write(map(speed, -100, 100, 1000, 2000));
}

