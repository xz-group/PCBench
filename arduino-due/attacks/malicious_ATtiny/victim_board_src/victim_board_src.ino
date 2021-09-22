//Victim Board

void setup() {
  SerialUSB.begin(4800); // Monitoring UART
  Serial2.begin(4800);   // UART being monitored by Malicious Chip
  pinMode(13, OUTPUT);
}

void loop() {
  SerialUSB.println("RUNNING"); // Ping to show that board has not yet been attacked
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
