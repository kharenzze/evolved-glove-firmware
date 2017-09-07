/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "SensorManager.h"
#include "EGUtils.h"
#include "EGConfig.h"
#include <iostream>
#include <unistd.h>
 
using namespace std;
using namespace EGUtils;
using namespace ABElectronics_CPP_Libraries;

void SensorManager::init (void) {
	mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, ADC_DEFAULT_RATE);
	// mainADC = new ADCPi(ADDRESS_ADC1_1, ADDRESS_ADC1_2, 18);
	mainADC->set_conversion_mode(ADC_DEFAULT_CONVERSION_MODE);
	mainADC->set_pga(ADC_DEFAULT_PGA);
}

void SensorManager::getSensorData (char* buffer, int* length) {
	cout << "trama init" << endl;
	for (int i = 1; i <= CHANNELS_PER_ADC; i++) {
		double data = mainADC->read_voltage(i);
		//cout << i << ": " << data << endl;
		appendDoubleToPacketBuffer(data, buffer, length);
		// usleep(30);
	}
}

