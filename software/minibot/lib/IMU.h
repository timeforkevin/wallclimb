#ifndef IMU_H
#define IMU_H

// #include "quaternionFilters.h"
#include "MPU9250.h"

#define SerialDebug true

class IMU : MPU9250 {
	private: 
	
	public:
	IMU() : MPU9250() {}
	void init() 
	{
	  Wire.begin();
	  // TWBR = 12;  // 400 kbit/sec I2C speed
	  Serial.begin(38400);
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
	    magCalMPU9250(magBias, magScale);
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

	//// IMU RETURNS ACCEL IN cm/s^2
	float getax(){
		readAccelData(accelCount); 
		ax = ((float)accelCount[0] * aRes) * 981; // - accelBias[0];
		return ax;
	}

	float getay(){
		readAccelData(accelCount); 
		ay = ((float)accelCount[1] * aRes) * 981; // - accelBias[1];
		return ax;
	}

	float getaz(){
		readAccelData(accelCount); 
		az = ((float)accelCount[2] * aRes) * 981; // - accelBias[2];
		return ax;
	}

	float getgx(){
		readGyroData(gyroCount);  
		gx = (float)gyroCount[0] * gRes;
		return gx;
	}

	float getgy(){
	    readGyroData(gyroCount);  
    	gy = (float)gyroCount[1] * gRes;
    	return gy;
	}

	float getgz(){
		readGyroData(gyroCount);  
	    gz = (float)gyroCount[2] * gRes;
	    return gz;
	}

	float getmx(){
		readMagData(magCount); 
		mx = (float)magCount[0] * mRes
  					* factoryMagCalibration[0] - magBias[0];
  		return mx;
	}

	float getmy(){
		readMagData(magCount); 
		my = (float)magCount[1] * mRes
              		* factoryMagCalibration[1] - magBias[1];
        return my;     		
	}

	float getmz(){
		readMagData(magCount); 
		mz = (float)magCount[2] * mRes
           			* factoryMagCalibration[2] - magBias[2];
		return mz;
	}

};

#endif