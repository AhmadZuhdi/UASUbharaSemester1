#define triggerPin 13
#define echoPin 12


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration, distance;
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2);
  Serial.print("Jarak: "); Serial.print(distance / 29.1); Serial.print("Cm\n");
  delay(500);
}
