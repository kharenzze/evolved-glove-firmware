/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "ABE_ADCPi.h"
#include "Adafruit_BNO055.h"
#include "EGConfig.h"

using namespace ABElectronics_CPP_Libraries;

typedef struct
    {
      double min;
	  double max;
    } VoltageRange;

class SensorManager {
public:
	void getSensorData(char *buffer, int *length);
	void init (void);
private:
	double _getNormalizedVoltage(double voltage, int finger);
	ADCPi *mainADC, *secondaryADC;
	Adafruit_BNO055 *orientationSensor;
	VoltageRange fingerVoltage[NUMBER_OF_FINGERS];
};