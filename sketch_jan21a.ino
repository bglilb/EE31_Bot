const int OFF = 0;
const int ON = 1;
const int RUN = 2;
const int SLEEP = 3;
const int GO_TO_SLEEP = 10;
const int DIAGNOSTIC = 4;
int state;

const int RED_LED_PORT = 11;
const int BLUE_LED_PORT = 12;
const int GREEN_LED_PORT = 13;

void setup() {
  // put your setup code here, to run once:
  state = RUN;

  pinMode(RED_LED_PORT, OUTPUT);
  pinMode(BLUE_LED_PORT, OUTPUT);
  pinMode(GREEN_LED_PORT, OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  if (state == ON){
    on_loop();
  }
  else if (state == RUN) {
    run_loop();
  }
  else if (state == GO_TO_SLEEP){
    clear_LEDs();
    go_to_sleep();
    state = SLEEP;
  }
  else if (state == DIAGNOSTIC) {
    clear_LEDs();
    diagnostic();
    state = ON;
  }

  // else, we are in the sleep state.  DO NOTHING.
}

void run_loop(){
  int sequence = millis() % 8000;
  if (sequence < 6000) {
    // we are in the decaying portion of the blinking pattern.
    float intensity = -sequence/1800.0;
    analogWrite(GREEN_LED_PORT, pow(2.718, intensity)*255); //exp(-sequence/600)*255
  }
  else {
    // we are in the blinking portion of the blinking pattern
    if((sequence < 6500) || (sequence > 7000 && sequence < 7500)){
      digitalWrite(GREEN_LED_PORT, HIGH);
    }
    else {
      digitalWrite(GREEN_LED_PORT, LOW);
    }
  }
  
}
void on_loop() {

  // Over one period of a 10Hz signal (0.1s), 100ms elapse

  if ((millis() % 100) < 50){
     digitalWrite(RED_LED_PORT, HIGH);
  }
  else{
    digitalWrite(RED_LED_PORT, LOW);
  } 
}
void go_to_sleep(){

  for(int i = 0; i < 4; i++){
    digitalWrite(BLUE_LED_PORT, HIGH);
    delay(125);
    digitalWrite(BLUE_LED_PORT, LOW);
    delay(125);
  }
  for(int brightness = 255; brightness >= 0; brightness--){
    analogWrite(BLUE_LED_PORT, brightness);
    delay(3.9);
  }
  
}
void diagnostic(){

  int problem = 5;
  for(int i = 0; i < problem; i++){
    digitalWrite(RED_LED_PORT, HIGH);
    delay(500);
    digitalWrite(RED_LED_PORT, LOW);
    delay(500);
  }
}

void clear_LEDs(){
  digitalWrite(RED_LED_PORT, LOW);
  digitalWrite(GREEN_LED_PORT, LOW);
  digitalWrite(BLUE_LED_PORT, LOW);
}
