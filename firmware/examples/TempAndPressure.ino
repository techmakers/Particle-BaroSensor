#include "BaroSensor.h"

void setup(){
	BaroSensor.begin();
}

void loop(){
	float pressure = round(BaroSensor.getPressure(OSR_8192)) ;
	float Temperature = BaroSensor.getTemperature() ;
	Serial.print(pressure) ;
	Serial.print(temperature) ;
}