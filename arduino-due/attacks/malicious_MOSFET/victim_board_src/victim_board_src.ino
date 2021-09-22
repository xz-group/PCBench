//Reference Board

void setup() {
  SerialUSB.begin(9600); // Monitor Serial
  Serial1.begin(9600); // (TX-18 RX-19)
  delay(5000); // Startup Serial Monitor
  SerialUSB.println("Victim Board - MOSFET Attack");
}

void loop() {
   if (Serial1.available() > 0) {
    char input = Serial1.read();
    Serial1.write(input); // Mirror data to the Serial1 TX pin which is directly connected to the LED
    SerialUSB.println(input); // Mirror back to monitor
   }
}
