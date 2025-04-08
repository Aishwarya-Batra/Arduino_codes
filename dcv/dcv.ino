#define DCV_PIN 10      // Pin connected to relay
#define BUTTON_ON 2     // Pin connected to ON button
#define BUTTON_OFF 3    // Pin connected to OFF button

void setup() {
  pinMode(DCV_PIN, OUTPUT);       // Set relay pin as OUTPUT
  digitalWrite(DCV_PIN, LOW);     // Initialize valve as OFF

  pinMode(BUTTON_ON, INPUT_PULLUP);  // Set ON button as INPUT with pull-up
  pinMode(BUTTON_OFF, INPUT_PULLUP); // Set OFF button as INPUT with pull-up

  Serial.begin(9600); // Optional: For debugging
  Serial.println("Press ON or OFF button to control the valve.");
}

void loop() {
  // Read the button states
  bool onButtonState = digitalRead(BUTTON_ON);
  bool offButtonState = digitalRead(BUTTON_OFF);

  // If ON button is pressed
  if (onButtonState == LOW) { // Button is active LOW
    digitalWrite(DCV_PIN, HIGH); // Turn the valve ON
    Serial.println("Valve is ON");
    delay(200); // Debounce delay
  }

  // If OFF button is pressed
  if (offButtonState == LOW) { // Button is active LOW
    digitalWrite(DCV_PIN, LOW); // Turn the valve OFF
    Serial.println("Valve is OFF");
    delay(200); // Debounce delay
  }
}
