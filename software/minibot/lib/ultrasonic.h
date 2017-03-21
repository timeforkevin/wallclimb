#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <limits.h>

#define RIGHTECHOPIN 8
#define RIGHTTRIGPIN 9
#define FRONTECHOPIN 10
#define FRONTTRIGPIN 11
#define LEFTECHOPIN 12
#define LEFTTRIGPIN 13

#define MAX_RANGE (500)
#define US_TO_CM (58.2)

class Ultrasonic {
  public:
    Ultrasonic(int echo_pin, int trig_pin) {
      m_echo_pin = echo_pin;
      m_trig_pin = trig_pin;
    }

    void init() {
      pinMode(m_echo_pin, INPUT);
      pinMode(m_trig_pin, OUTPUT);
    }

    long getDistance(int maxRange = MAX_RANGE) {
      // 10us pulse
      digitalWrite(m_trig_pin, LOW);
      delayMicroseconds(2);
      digitalWrite(m_trig_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(m_trig_pin, LOW);

      // Measure and return echo
      return pulseIn(m_echo_pin, HIGH, maxRange*US_TO_CM)/US_TO_CM;
    }
  private:
    int m_echo_pin;
    int m_trig_pin;
};

#endif
