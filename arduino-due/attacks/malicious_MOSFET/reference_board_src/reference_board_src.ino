//Reference Board

void setup() {
  SerialUSB.begin(9600); // Monitor Serial
  Serial1.begin(9600); // (TX-18 RX-19)
  delay(5000); // Startup Serial Monitor
  SerialUSB.println("Reference Board - MOSFET Attack");
}

void loop() {
   if (SerialUSB.available() > 0) {
    char input = SerialUSB.read();
    SerialUSB.println(input); // Mirror back to monitor
    Serial1.println(input); // Send characters to Victim Board
   }
}
