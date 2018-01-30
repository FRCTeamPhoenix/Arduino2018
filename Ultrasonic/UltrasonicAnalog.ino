const int anPin = 1;



long anVolt, inches, cm;
int sum = 0;
int avgrange = 60;




void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i = 0; i < avgrange ; i++)
{
  anVolt = analogRead(anPin) / 2;
  sum+= anVolt;
  delay(10);
}
inches = sum / avgrange;
cm = inches * 2.54;
Serial.print(inches);
Serial.print("in,");
Serial.print(cm);
Serial.print("cm");
Serial.println();



sum = 0;

delay(500);
}
