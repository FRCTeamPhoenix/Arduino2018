int val = 0;
int pirState = LOW;
void setup() {
  // put your setup code here, to run once:
pinMode(7, INPUT);
pinMode(4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
val = digitalRead(7);
if (val == HIGH) {
  digitalWrite(4, HIGH);
  if (pirState == LOW) {
    pirState = HIGH;
  }
 
} else {
  digitalWrite(4, LOW);
  if (pirState == HIGH) {
    pirState = LOW;
  }
}
}
