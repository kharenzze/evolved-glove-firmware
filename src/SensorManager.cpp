/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "SensorManager.h"
#include "EGUtils.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <limits>
 
using namespace std;
using namespace EGUtils;
using namespace ABElectronics_CPP_Libraries;

void SensorManager::init (void) {
	mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, ADC_DEFAULT_RATE);
	// mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, 18);
	mainADC->set_conversion_mode(ADC_DEFAULT_CONVERSION_MODE);
	mainADC->set_pga(ADC_DEFAULT_PGA);

	secondaryADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, ADC_DEFAULT_RATE);
	// mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, 18);
	secondaryADC->set_conversion_mode(ADC_DEFAULT_CONVERSION_MODE);
	secondaryADC->set_pga(ADC_DEFAULT_PGA);

	orientationSensor = new Adafruit_BNO055();
	if (!orientationSensor->begin()) {
		error("Orientation Sensor could not start properly");
	}

	for (int i = 0; i < NUMBER_OF_FINGERS; i++) {
		fingerVoltage[i].min = numeric_limits<double>::max();
		fingerVoltage[i].max = numeric_limits<double>::min();
	}
}

void SensorManager::getSensorData (char* buffer, int* length) {
	*length = 8; //reserving space for timestamp
	if (DEBUG_MODE) {
		cout << "frame init" << endl;
	}
	
	int fingerNumber = 0;
	// reading mainADC data for fingers
	for (int i = 1; i <= CHANNELS_ON_MAIN_ADC; i++) {
		const double data = mainADC->read_voltage(i);
		const double normalizedData = _getNormalizedVoltage(data, fingerNumber);
		fingerNumber++;
		//cout << i << ": " << normalizedData << endl;
		appendDoubleToPacketBuffer(normalizedData, buffer, length);
		// usleep(30);
		
	}
	// reading secondaryADC data for fingers
	for (int i = 1; i <= CHANNELS_ON_SEC_ADC; i++) {
		const double data = secondaryADC->read_voltage(i);
		const double normalizedData = _getNormalizedVoltage(data, fingerNumber);
		fingerNumber++;
		//cout << i << ": " << data << endl;
		appendDoubleToPacketBuffer(normalizedData, buffer, length);
		// usleep(30);
	}

	//Orientation
	//sensors_event_t orientationEvent;
	//orientationSensor->getEvent(&orientationEvent);
	imu::Vector<3> orientation = orientationSensor->getVector(Adafruit_BNO055::VECTOR_EULER);
	for (int i = 0; i < 3; i++) {
		double data = orientation[i];
		appendDoubleToPacketBuffer(data, buffer, length);
		if (DEBUG_MODE) {
			std::cout << data << "\t\t";
		}
	}
	if (DEBUG_MODE) {
		std::cout << endl;
	}
	
	// std::cout << orientationEvent.orientation.x << "\t\t" 
	// << orientationEvent.orientation.y << "\t\t" 
	// << orientationEvent.orientation.z << std::endl;
	
	//set Timestamp
	auto now = chrono::high_resolution_clock::now();
	auto ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count();
	char* timestampAsBytes = (char*) &ns;

	for (int i = 0; i < sizeof(ns); i++) {
		buffer[i] = timestampAsBytes[i];
	}

}

double SensorManager::_getNormalizedVoltage(double voltage, int finger) {
	if (voltage < fingerVoltage[finger].min) {
		fingerVoltage[finger].min = voltage;
	} else if (voltage > fingerVoltage[finger].max) {
		fingerVoltage[finger].max = voltage;
	}
	double rangeValue = fingerVoltage[finger].max - fingerVoltage[finger].min;
	return (voltage - fingerVoltage[finger].min) / rangeValue;
}

