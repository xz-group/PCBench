//Reference Board

void setup() {
  SerialUSB.begin(9600); // Monitor Serial
  Serial2.begin(4800);   // UART being monitored by malicious chip
  delay(5000); // Startup Serial Monitor
  SerialUSB.println("Reference Board - ATtiny Attack");
  SerialUSB.println("Trigger Word: \"ATTACK\"\n\n");
}

void loop() {
   if (SerialUSB.available() > 0) {
    char input = SerialUSB.read();
    Serial2.print(input);
    SerialUSB.print(input);
    }
}
