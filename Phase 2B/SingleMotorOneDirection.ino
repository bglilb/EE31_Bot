#define ONEA 13
#define TWOA 12
//const int SPEED_UP = 10;
//const int SPEED_DOWN = 9;
#define DIRECTION_BUTTON 2
bool direct = false;
int speedOutput = 64;

void setup() {
  // put your setup code here, to run once:
  pinMode(ONEA, OUTPUT);
  pinMode(TWOA, OUTPUT);
  Serial.begin(9600);
  //pinMode(SPEED_UP, INPUT_PULLUP); //These are used to control the speed of the motor
  //pinMode(SPEED_DOWN, INPUT_PULLUP);
  //pinMode(DIRECTION_BUTTON, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(DIRECTION_BUTTON), directionChange, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ONEA, LOW); //When hold 1A Low
  analogWrite(TWOA,speedOutput); //PWM 2A and should turn motor clockwise
  Serial.println(speedOutput);
  //if (direct == false) {
  //  digitalWrite(ONEA, LOW); //When hold 1A Low
  //  analogWrite(TWOA,speedOutput); //PWM 2A and should turn motor clockwise
  //}else{
  //  digitalWrite(TWOA, LOW); //When Hold 2A Low
  //  analogWrite(ONEA,speedOutput); //PWM 1A and hould turn motor counter
  //}

}

void directionChange() {
  direct = !direct;
}
