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

void setup() {
  for (int i = 0; i < 8; i++) pinMode(segPins[i], OUTPUT);
  for (int i = 0; i < 6; i++) pinMode(digitPins[i], OUTPUT);

  for(int i=0;i<6;i++){
    digitalWrite(digitPins[i],HIGH);
  }
}

void loop(){

}