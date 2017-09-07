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
	void init (void);
private:
	ADCPi *mainADC, *secondaryADC;
};