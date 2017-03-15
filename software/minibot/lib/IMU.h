#ifndef IMU_H
#define IMU_H

#include "MPU9250.h"
#include "MPU9250.cpp"

#define SerialDebug true

class IMU : MPU9250 {
  public:
    float a[3];
    float g[3];
    float m[3];

    IMU()
    : MPU9250() {

    }

    void updateAccelData() {
      readAccelData(accelCount);
      a[0] = ((float)accelCount[0] * aRes) * 9.81 - accelBias[0];
      a[1] = ((float)accelCount[1] * aRes) * 9.81 - accelBias[1];
      a[2] = ((float)accelCount[2] * aRes) * 9.81 - accelBias[2];
    }

    void updateGyroData() {
      readGyroData(gyroCount);
      g[0] = (float)gyroCount[0] * gRes;
      g[1] = (float)gyroCount[1] * gRes;
      g[2] = (float)gyroCount[2] * gRes;
    }

    void updateMagData() {
      readMagData(magCount);
      m[0] = (float)magCount[0] * mRes * factoryMagCalibration[0] - magBias[0];
      m[1] = (float)magCount[1] * mRes * factoryMagCalibration[1] - magBias[1];
      m[2] = (float)magCount[2] * mRes * factoryMagCalibration[2] - magBias[2];
    }

    void init() 
    {
      Wire.begin();
      // TWBR = 12;  // 400 kbit/sec I2C speed
      byte c = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);


      if (c == 0x71) // WHO_AM_I should always be 0x71
      {
        // // Start by performing self test and reporting values
        MPU9250SelfTest(selfTest);

        //// GYRO & ACCEL CALIBRATION ////
        calibrateMPU9250(gyroBias, accelBias);

        // Initialize device for active mode read of acclerometer, gyroscope
        initMPU9250();

        // // Read the WHO_AM_I register of the magnetometer, this is a good test of
        // // communication
        byte d = readByte(AK8963_ADDRESS, 0x00);
        if (d != 0x48)
        {
          Serial.println(F("MAG Register failed, abort!"));
          Serial.flush();
          abort();
        }

        // Get magnetometer calibration from AK8963 ROM
        initAK8963(factoryMagCalibration);

        // Get sensor resolutions, only need to do this once
        getAres();
        getGres();
        getMres();

        //// MAGNET CALIBRATION ////
        // magCalMPU9250(magBias, magScale);
        magBias[0] = 1000;
        magBias[1] = 1000;
        magBias[2] = 1000;
        magScale[0] = 1.00;
        magScale[1] = 1.00;
        magScale[2] = 0.01;


// Serial.print(" bias:");
// Serial.print(magBias[0]);
// Serial.print(" ");
// Serial.print(magBias[1]);
// Serial.print(" ");
// Serial.print(magBias[2]);
// Serial.print(" ");
// Serial.print(" scale:");
// Serial.print(magScale[0]);
// Serial.print(" ");
// Serial.print(magScale[1]);
// Serial.print(" ");
// Serial.print(magScale[2]);
// Serial.print(" ");
      } // if (c == 0x71)
      else
      {
        Serial.print("Could not connect to MPU9250: 0x");
        Serial.println(c, HEX);

        // Communication failed, stop here
        Serial.println(F("Communication failed, abort!"));
        Serial.flush();
        abort();
      }
      Serial.println("Done set up!");
    }
};

#endif