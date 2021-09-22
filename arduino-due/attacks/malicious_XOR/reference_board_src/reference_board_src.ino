//Reference Board

#define VICTIM_44 10 // Pin 44 on Victim Board
#define VICTIM_45 11 // Pin 45 on Victim Board
#define VICTIM_46 12 // Pin 46 on Victim Board

char inputArray[6];
char trigger[] = {'A', 'T', 'T', 'A', 'C', 'K'};

void setup() {
  pinMode(VICTIM_44, OUTPUT);
  pinMode(VICTIM_45, OUTPUT);
  pinMode(VICTIM_46, OUTPUT);
  SerialUSB.begin(9600); // Monitor Serial for trigger
  delay(5000); // Startup Serial Monitor
  SerialUSB.println("Reference Board - XOR Attack");
  SerialUSB.println("Trigger Word: \"ATTACK\"\n\n");
}

void loop() {
   if (SerialUSB.available() > 0) {
    char input = SerialUSB.read();
    SerialUSB.println(input);
    
    for(int i = 0; i < 5; i++) {
      inputArray[i] = inputArray[i+1];
    }
    inputArray[5] = input;

    bool matchTrigger = true;
    for(int i = 0; i < 6; i++) {
      if(!(inputArray[i] == trigger[i])) {
        matchTrigger = false;
        break;
      }
    }

    if(matchTrigger) {
      SerialUSB.println("Attacking Victim Board");
      digitalWrite(VICTIM_44, HIGH);
      digitalWrite(VICTIM_45, HIGH);
      digitalWrite(VICTIM_46, HIGH);
      delay(2000);
      digitalWrite(VICTIM_44, LOW);
      digitalWrite(VICTIM_45, LOW);
      digitalWrite(VICTIM_46, LOW);
    }
   }
}
