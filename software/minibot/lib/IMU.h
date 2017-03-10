#ifndef IMU_H
#define IMU_H

#include <quaternionFilters.h>
#include <MPU9250.h>

#define SerialDebug true

class IMU {
	private: 
	MPU9250 myIMU;
	
	public:
	IMU()
	void init()
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

	//// IMU RETURNS ACCEL IN cm/s^2
	float getax(){
		myIMU.readAccelData(myIMU.accelCount); 
		myIMU.ax = ((float)myIMU.accelCount[0] * myIMU.aRes) * 981; // - myIMU.accelBias[0];
		return myIMU.ax;
	}

	float getay(){
		myIMU.readAccelData(myIMU.accelCount); 
		myIMU.ay = ((float)myIMU.accelCount[1] * myIMU.aRes) * 981; // - myIMU.accelBias[1];
		return myIMU.ax;
	}

	float getaz(){
		myIMU.readAccelData(myIMU.accelCount); 
		myIMU.az = ((float)myIMU.accelCount[2] * myIMU.aRes) * 981; // - myIMU.accelBias[2];
		return myIMU.ax;
	}

	float getgx(){
		myIMU.readGyroData(myIMU.gyroCount);  
		myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
		return myIMU.gx;
	}

	float getgy(){
	    myIMU.readGyroData(myIMU.gyroCount);  
    	myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
    	return myIMU.gy;
	}

	float getgz(){
		myIMU.readGyroData(myIMU.gyroCount);  
	    myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;
	    return myIMU.gz;
	}

	float getmx(){
		myIMU.readMagData(myIMU.magCount); 
		myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes
  					* myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
  		return myIMU.mx;
	}

	float getmy(){
		myIMU.readMagData(myIMU.magCount); 
		myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes
              		* myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
        return myIMU.my;     		
	}

	float getmz(){
		myIMU.readMagData(myIMU.magCount); 
		myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes
           			* myIMU.factoryMagCalibration[2] - myIMU.magBias[2];
		return myIMU.mz;
	}

}

#endif