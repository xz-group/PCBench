//Victim Board

void setup() {
  pinMode(13, OUTPUT);
  SerialUSB.begin(9600);
  SerialUSB.println("Victim Board - XOR Attack");
}

void loop() {
  // Constantly blinks built in LED to show that the code is still running
  // When LED stops blinking, the victim board has been attacked
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
