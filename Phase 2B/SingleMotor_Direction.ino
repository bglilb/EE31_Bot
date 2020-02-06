const int 1A_PIN = 13;
const int 2A_PIN = 12;
//const int SPEED_UP = 10;
//const int SPEED_DOWN = 9;
const int DIRECTION_BUTTON = 2
bool direct = false;
int speedOutput = 64;

void setup() {
  // put your setup code here, to run once:
  pinMode(1A_PIN, OUTPUT);
  pinMode(2A_PIN, OUTPUT);
  //pinMode(SPEED_UP, INPUT_PULLUP); //These are used to control the speed of the motor
  //pinMode(SPEED_DOWN, INPUT_PULLUP);
  pinMode(DIRECTION_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DIRECTION_BUTTON), directionChange, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (direct == false) {
    digitalWrite(1A_PIN, LOW); //When hold 1A Low
    analogWrite(2A_PIN,speedOutput); //PWM 2A and should turn motor clockwise
  }else{
    digitalWrite(2A_PIN, LOW); //When Hold 2A Low
    analogWrite(1A_PIN,speedOutput); //PWM 1A and hould turn motor counter
  }

}

void directionChange() {
  direct = !direct
}
