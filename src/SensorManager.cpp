/**
* Created by Pablo Ráez @kharenzze
* Configuration
**/

#include "SensorManager.h"
#include "EGUtils.h"
#include "EGConfig.h"
 
using namespace EGUtils;

void SensorManager::getSensorData(char* buffer, int* length) {
	int n = 12;
	appendIntToPacketBuffer(n, buffer, length);
}