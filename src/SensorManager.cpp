/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "SensorManager.h"
#include "EGUtils.h"
#include "EGConfig.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
 
using namespace std;
using namespace EGUtils;
using namespace ABElectronics_CPP_Libraries;

void SensorManager::init (void) {
	mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, ADC_DEFAULT_RATE);
	// mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, 18);
	mainADC->set_conversion_mode(ADC_DEFAULT_CONVERSION_MODE);
	mainADC->set_pga(ADC_DEFAULT_PGA);

	orientationSensor = new Adafruit_BNO055();
	if (!orientationSensor->begin()) {
		error("Orientation Sensor could not start properly");
	}
}

void SensorManager::getSensorData (char* buffer, int* length) {
	*length = 8; //reserving space for timestamp
	cout << "trama init" << endl;
	// reading mainADC data for fingers
	for (int i = 1; i <= CHANNELS_PER_ADC; i++) {
		double data = mainADC->read_voltage(i);
		//cout << i << ": " << data << endl;
		appendDoubleToPacketBuffer(data, buffer, length);
		// usleep(30);
	}

	//Orientation
	sensors_event_t orientationEvent;
	orientationSensor->getEvent(&orientationEvent);

	std::cout << orientationEvent.orientation.x << "\t\t" 
	<< orientationEvent.orientation.y << "\t\t" 
	<< orientationEvent.orientation.z << std::endl;

	
	//set Timestamp
	auto now = chrono::high_resolution_clock::now();
	auto ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count();
	char* timestampAsBytes = (char*) &ns;

	for (int i = 0; i < sizeof(ns); i++) {
		buffer[i] = timestampAsBytes[i];
	}

}

