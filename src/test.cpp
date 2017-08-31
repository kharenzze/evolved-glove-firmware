//tests

#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "EGUtils.h"

#include "ABE_ADCPi.h"

using namespace std;
using namespace ABElectronics_CPP_Libraries;
using namespace EGUtils;

void testADCPI() {
	ADCPi adc(0x68, 0x69, 18);
	adc.set_conversion_mode(1);
	adc.set_pga(4);

	while (1) {
		clearscreen();
		printf("Pin 1: %G \n", adc.read_voltage(1)); // read from channel 1
		//printf("Pin 1: %d \n", adc.read_raw(1)); // read from channel 1
		usleep(200000); // sleep 0.2 seconds
	}
}

int main (int argc, char **argv) {
	testADCPI();
	return 0;
}
