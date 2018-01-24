#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

void setup(){
  Serial.begin(115200);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
}

void loop(){
  if(Serial.available() > 0){
    Serial.read();
    Serial.println(myLidarLite.distance());
    delay(10);
  }
}

