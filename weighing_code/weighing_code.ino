// Segment pins (A, B, C, D, E, F, G, DP)
const int segPins[] = {6,7,8,9,10,11,12,13};

// Digit control pins (left to right for 6 digits)
const int digitPins[] = {0,1,2,3,4,5};

// Digit patterns for 0-9 (same as cathode)
const byte digitSegments[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

// Custom weight values //22.975  // 
const char* weights[] = {
  "2750", "6150", "4700", "10300", "10550", "10580", "11300", "12000",
  "12.600", "12600", "16300", "16.300", "16.200", "15900", "15.900", "15.950",
  "18150", "18850", "19300", "19.700", "21950", "21.900", "24000", "24.050",
  "24.100", "24.200", "24.250", "24.100", "24.200", "24.350", "24.600"
};

int weightIndex = -1;
unsigned long lastUpdate = 0;
const unsigned long fastInterval = 100;
const unsigned long slowInterval = 300;
const unsigned long startupDelay = 3000;

void setup() {
  for (int i = 0; i < 8; i++) pinMode(segPins[i], OUTPUT);
  for (int i = 0; i < 6; i++) pinMode(digitPins[i], OUTPUT);

  // Show 0 only on rightmost digit for 3 seconds
  unsigned long startTime = millis();
  while (millis() - startTime < startupDelay) {
    for (int i = 0; i < 6; i++) {
      if (i == 5) setSegments(0, false);
      else clearSegments();

      digitalWrite(digitPins[i], HIGH); // Turn ON this digit (common anode)
      delay(2);
      digitalWrite(digitPins[i], LOW);  // Turn OFF digit
    }
  }

  weightIndex = 0;
  lastUpdate = millis();
}

void loop() {
  unsigned long now = millis();
  int totalWeights = sizeof(weights) / sizeof(weights[0]);
  unsigned long interval = (weightIndex < totalWeights - 7) ? fastInterval : slowInterval;

  if (now - lastUpdate >= interval) {
    lastUpdate = now;
    weightIndex++;
    if (weightIndex >= totalWeights) weightIndex = totalWeights - 1;
  }

  showWeight(weights[weightIndex]);
}

void showWeight(const char* valStr) {
  int displayDigits[6] = {-1, -1, -1, -1, -1, -1};
  bool dpFlags[6] = {false};

  int len = strlen(valStr);
  int digitPos = 5;

  for (int i = len - 1; i >= 0 && digitPos >= 0; i--) {
    if (valStr[i] == '.') {
      if (digitPos < 6) dpFlags[digitPos] = true;
    } else if (isdigit(valStr[i])) {
      displayDigits[digitPos] = valStr[i] - '0';
      digitPos--;
    }
  }

  for (int i = 0; i < 6; i++) {
    if (i == 0 || displayDigits[i] == -1) {
      clearSegments();  // Blank
    } else {
      setSegments(displayDigits[i], dpFlags[i]);
    }

    digitalWrite(digitPins[i], HIGH); // Common anode: ON
    delay(2);
    digitalWrite(digitPins[i], LOW);  // OFF
  }
}

void setSegments(int num, bool showDP) {
  for (int i = 0; i < 8; i++) {
    if (i == 7)
      digitalWrite(segPins[i], showDP ? LOW : HIGH); // DP: invert logic
    else
      digitalWrite(segPins[i], digitSegments[num][i] ? LOW : HIGH); // Invert for common anode
  }
}

void clearSegments() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segPins[i], HIGH); // All OFF for common anode
  }
}