/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "ABE_ADCPi.h"
#include "Adafruit_BNO055.h"

using namespace ABElectronics_CPP_Libraries;

class SensorManager {
public:
	void getSensorData(char *buffer, int *length);
private:
	ADCPi *mainADC, *secondaryADC;
};