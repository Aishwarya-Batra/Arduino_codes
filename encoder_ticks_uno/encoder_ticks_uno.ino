#define ENCODER_PIN_A 2  // Interrupt-capable pin
#define ENCODER_PIN_B 3  // Interrupt-capable pin

volatile long counter = 0;  // Stores encoder ticks

void encoderISR_A() {
    int aState = digitalRead(ENCODER_PIN_A);
    int bState = digitalRead(ENCODER_PIN_B);

    if (aState == bState) {
        counter++;  // Clockwise
    } else {
        counter--;  // Counterclockwise
    }
}

void encoderISR_B() {
    int aState = digitalRead(ENCODER_PIN_A);
    int bState = digitalRead(ENCODER_PIN_B);

    if (aState != bState) {
        counter++;  // Clockwise
    } else {
        counter--;  // Counterclockwise
    }
}

void setup() {
    Serial.begin(9600);
    
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);

    // Attach interrupts to both pins
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), encoderISR_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), encoderISR_B, CHANGE);

    Serial.println("Encoder Ready...");
}

void loop() {
    Serial.print("Ticks: ");
    Serial.println(counter);
    delay(200);  // Adjust as needed
}
