#include <Wire.h>
#include <LIDARLite.h>
#include <pt.h>

LIDARLite myLidarLite;

static struct pt pt1, pt2; // each protothread needs one of these
const int pwPin1 = 5; //this may be different depending on the Arduino being used, and the other PW pins being used.
long sensor1, cm, inches;

void setup(){
	//begin serial rate at 115200 baud
	Serial.begin(115200);
	//begin lidar sensor
	myLidarLite.begin(0, true);
	//configure sensor
	myLidarLite.configure(0);
  pinMode(pwPin1, INPUT);
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  sensor1 = 0;
}

void read_sensor(){
  sensor1 = pulseIn(pwPin1, HIGH);
  cm = sensor1/10; // converts the range to cm
  inches = cm/2.54; // converts the range to inches
}

void updateLoop(){
  //if data written over serial, ping back sensor data
  if(Serial.available() > 0){
    Serial.read();
    String startChar = "s";
    String l = " ";
    String toPrint = startChar + sensor1 +l+myLidarLite.distance();
    Serial.println(toPrint);
  }
}

/* This function toggles the LED after 'interval' ms passed */
static int protothread1(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // never stop 
    /* each time the function is called the second boolean
    *  argument "millis() - timestamp > interval" is re-evaluated
    *  and if false the function exits after that. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
    read_sensor();
  }
  PT_END(pt);
}

/* exactly the same as the protothread1 function */
static int protothread2(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis();
    updateLoop();
  }
  PT_END(pt);
}

void loop(){
	protothread1(&pt1, 100); // call every 100 ms to keep refresh rate
  protothread2(&pt2, 10); // call main update loop
}

