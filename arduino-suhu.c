const int inPin = 0; // analog 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = analogRead(inPin);
  //Serial.print(v); Serial.print("\n");
  float mlVolts = (v / 1024.0) * 5000;
  float celcius = mlVolts / 10;
  Serial.print(celcius); Serial.print("C"); Serial.print("\n");
  delay(1000);
}
