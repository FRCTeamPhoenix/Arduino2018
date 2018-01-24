#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

void setup(){
	//begin serial rate at 115200 baud
	Serial.begin(115200);
	//begin lidar sensor
	myLidarLite.begin(0, true);
	//configure sensor
	myLidarLite.configure(0);
}

void loop(){
	//if data written over serial, ping back lidar data
  if(Serial.available() > 0){
    Serial.read();
    Serial.println(myLidarLite.distance());
    delay(10);
  }
}

