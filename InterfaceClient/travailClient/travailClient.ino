const int pin=8;

void setup() {
  Serial.begin(9600); // Set baud rate
  pinMode(pin,OUTPUT);
}

void loop() {
    if (Serial.available()) {
        int signal = Serial.parseInt();
        Serial.print("Received signal: ");
        Serial.println(signal);  // Print received signal for debugging

        if (signal == 1) {
            // One ring
            digitalWrite(pin, HIGH);
            delay(200);
            digitalWrite(pin, LOW);
        } else if (signal == 2) {
            // Two rings
            digitalWrite(pin, HIGH);
            delay(200);
            digitalWrite(pin, LOW);
            delay(100);
            digitalWrite(pin, HIGH);
            delay(200);
            digitalWrite(pin, LOW);
        }
    }
}

