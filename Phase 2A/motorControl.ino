#define GATE 2
#define SPEED 3
int speedOutput = 0;

setup() {
  pinMode(GATE, OUTPUT);
  pinMode(SPEED, INPUT);
}

loop() {
  analogWrite(GATE, SpeedOutput);
  if (SPEED == LOW) {
    speedOutput += 10;
  }
}
