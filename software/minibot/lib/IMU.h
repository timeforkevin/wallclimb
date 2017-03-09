#ifndef IMU_H
#define IMU_H

#include <quaternionFilters.h>
#include <MPU9250.h>

#define SerialDebug true

class IMU {
	public:
	void setup()
	{
	  Wire.begin();
	  // TWBR = 12;  // 400 kbit/sec I2C speed
	  Serial.begin(38400);
	  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);


	  if (c == 0x71) // WHO_AM_I should always be 0x71
	  {
	    // // Start by performing self test and reporting values
	    myIMU.MPU9250SelfTest(myIMU.selfTest);

	    //// GYRO & ACCEL CALIBRATION ////
	    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

	    // Initialize device for active mode read of acclerometer, gyroscope
	    myIMU.initMPU9250();

	    // // Read the WHO_AM_I register of the magnetometer, this is a good test of
	    // // communication
	    byte d = myIMU.readByte(AK8963_ADDRESS, 0x00);
	    if (d != 0x48)
	    {
	      Serial.println(F("MAG Register failed, abort!"));
	      Serial.flush();
	      abort();
	    }

	    // Get magnetometer calibration from AK8963 ROM
	    myIMU.initAK8963(myIMU.factoryMagCalibration);

	    // Get sensor resolutions, only need to do this once
	    myIMU.getAres();
	    myIMU.getGres();
	    myIMU.getMres();

	    //// MAGNET CALIBRATION ////
	    myIMU.magCalMPU9250(myIMU.magBias, myIMU.magScale);
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
	}

	//GET ACCEL

	//GET GYRO

	//GET MAG
}

#endif