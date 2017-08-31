#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include "Adafruit_BNO055.h"
#include <unistd.h>  //needed for delays
#include <iomanip> //setprecision

//using namespace std;

// int main() {
// 	std::cout << "Hello world" << std::endl;
// 	uint8_t sensor_fd = wiringPiI2CSetup(0x28);
// 	std::cout << unsigned(sensor_fd) << std::endl;
// 	int i = wiringPiI2CReadReg8(sensor_fd, 0x0);
// 	uint8_t j = 0xA0;
// 	std::cout << i << " " << unsigned(j) << std::endl;
// 	return 0;
// }

#define DEFAULT_DELAY 100000
#define SYSTEM_SHOULD_BE_ENABLED false

void clearscreen () {
    printf("\033[2J\033[1;1H");
}

void displaySensorDetails(Adafruit_BNO055* device)
{
	sensor_t sensor;
	device->getSensor(&sensor);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Sensor:       " << sensor.name << std::endl;
	std::cout << "Driver Ver:   " << sensor.version << std::endl;
	std::cout << "Unique ID:    " << sensor.sensor_id << std::endl;
	std::cout << "Max Value:    " << sensor.max_value << std::endl;
	std::cout << "Min Value:    " << sensor.min_value << std::endl;
	std::cout << "Resolution:   " << sensor.resolution << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << std::endl;
	usleep(500000);
}

void displayCalStatus(Adafruit_BNO055* device)
{
	/* Get the four calibration values (0..3) */
	/* Any sensor data reporting 0 should be ignored, */
	/* 3 means 'fully calibrated" */
	uint8_t system, gyro, accel, mag;
	system = gyro = accel = mag = 0;

  if (SYSTEM_SHOULD_BE_ENABLED) {
    while (!system) {
        device->getCalibration(&system, &gyro, &accel, &mag);
        if (!system){
          std::cout << "! " << std::flush;
          usleep(DEFAULT_DELAY);
        }
      }
      std::cout << std::endl;
  } else {
    device->getCalibration(&system, &gyro, &accel, &mag);
  }

	

	/* Display the individual values */
	// Serial.print("Sys:");
	// Serial.print(system, DEC);
	// Serial.print(" G:");
	// Serial.print(gyro, DEC);
	// Serial.print(" A:");
	// Serial.print(accel, DEC);
	// Serial.print(" M:");
	// Serial.print(mag, DEC);
	std::cout << unsigned(system) << " " << unsigned(gyro) << " " 
	<< unsigned(accel) << " " << unsigned(mag) << std::endl;
}

void displayEvent(Adafruit_BNO055* device) {
	/* Get a new sensor event */
	sensors_event_t event;
	device->getEvent(&event);

  // if (event.orientation.z < -180) {
  //   event.orientation.z += 2048;
  // }

	std::cout << event.orientation.x << "\t\t" 
	<< event.orientation.y << "\t\t" 
	<< event.orientation.z << std::endl;
}

void displayAcc(Adafruit_BNO055* device) {
	/* Get a new sensor event */
  imu::Vector<3> acc;
	acc = device->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

	std::cout << acc[0] << "\t\t"
	          << acc[1] << "\t\t"
	          << acc[2] << std::endl;
}

void _config() {
  std::setprecision(3);
}

int main() {


	#ifdef __arm__
	std::cout << "It run!" << std::endl;
	#endif

	Adafruit_BNO055 sensor = Adafruit_BNO055(1, BNO055_ADDRESS_A);
	if (!sensor.begin(Adafruit_BNO055::OPERATION_MODE_IMUPLUS)) {
		std::cout << "fuuuuu";
		return 1;
	}
	displaySensorDetails(&sensor);

	while (true) {
		displayCalStatus(&sensor);
		displayEvent(&sensor);
    displayAcc(&sensor);
    // sensor.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
		usleep(DEFAULT_DELAY);
		clearscreen();
	}

	return 0;
}