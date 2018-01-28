/*
Test code for the Arduino controllers
Written by Tom Bonar for testing
Sensors being used for this code are the HR-MaxSonar from MaxBotix
Used to Read the PW input.
*/
const int pwPin1 = 5; //this may be different depending on the Arduino being used, and the other PW pins being used.
long sensor1, cm, inches;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
}

void read_sensor(){
  sensor1 = pulseIn(pwPin1, HIGH);
  cm = sensor1/10; // converts the range to cm
  inches = cm/2.54; // converts the range to inches
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall(){         
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(sensor1); //This can be made to match the measurement type you wish to have.
  Serial.println("mm"); //Typically will be the range reading increments.
}

void loop () {
  read_sensor();
  printall();
  delay(100); //make this match the refresh rate of the sensor
}

