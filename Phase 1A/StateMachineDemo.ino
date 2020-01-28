const int OFF = 0;
const int ON = 1;
const int RUN = 2;
const int SLEEP = 3;
const int GO_TO_SLEEP = 10;
const int DIAGNOSTIC = 4;
int state;

const int RED_LED_PORT = 11;
const int BLUE_LED_PORT = 12;
const int GREEN_LED_PORT = 10;

//const int STATE_SWITCH = 2;

const int ON_BUTTON = 2;
const int RUN_BUTTON = 3;
const int DIAGNOSTIC_BUTTON = 20;
const int SLEEP_BUTTON = 21;


const int SWITCH1 = 18;
const int SWITCH2 = 19;

unsigned long button_time = 0;
unsigned long last_button = 0;

bool blueFreq = LOW;

void setup() {
  // put your setup code here, to run once:
  state = OFF;

  pinMode(RED_LED_PORT, OUTPUT);
  pinMode(BLUE_LED_PORT, OUTPUT);
  pinMode(GREEN_LED_PORT, OUTPUT);
  
  //pinMode(STATE_SWITCH, INPUT_PULLUP);
  pinMode(ON_BUTTON, INPUT_PULLUP);
  pinMode(RUN_BUTTON, INPUT_PULLUP);
  pinMode(DIAGNOSTIC_BUTTON, INPUT_PULLUP);
  pinMode(RUN_BUTTON, INPUT_PULLUP);
  
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  

  attachInterrupt(digitalPinToInterrupt(DIAGNOSTIC_BUTTON), set_state_diagnostic, FALLING);
  attachInterrupt(digitalPinToInterrupt(SLEEP_BUTTON), set_state_go_to_sleep, FALLING);
  attachInterrupt(digitalPinToInterrupt(ON_BUTTON), set_state_on, FALLING);
  attachInterrupt(digitalPinToInterrupt(RUN_BUTTON), set_state_run, FALLING);

  attachInterrupt(digitalPinToInterrupt(SWITCH1), blueROF, RISING);
  attachInterrupt(digitalPinToInterrupt(SWITCH2), redON, FALLING);
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  if (state == ON){
    on_loop();
  }
  else if (state == RUN) {
    run_loop();
    //Serial.println(blueFreq);
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
  int blueSequence = millis() % 1000;
  /*
   * This blinking sequence is the most complicated of them all.  The Green LED must fade to off over 6 seconds,
   *  and then it must blink for two seconds.  And it must be prepared to exit the run state at any time (without waiting
   *  for blinking pattern to finish).
   */
  digitalWrite(RED_LED_PORT, LOW);
  if (sequence < 6000) {
    // we are in the decaying portion of the blinking pattern.
    float intensity = -sequence/1800.0; // needed for non-integer division
    analogWrite(GREEN_LED_PORT, pow(2.718, intensity)*255);
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

  // ?? What is this?
  if (blueFreq == LOW) {
    if (blueSequence < 500) {
      digitalWrite(BLUE_LED_PORT,HIGH);
    }else{
      digitalWrite(BLUE_LED_PORT,LOW);
    }
  }else{
    if (blueSequence % 100 < 50) {
      digitalWrite(BLUE_LED_PORT,HIGH);
    }else{
      digitalWrite(BLUE_LED_PORT,LOW);
    }
  }
  
}
void on_loop() {
  digitalWrite(BLUE_LED_PORT, LOW);
  digitalWrite(GREEN_LED_PORT, LOW);
  // Over one period of a 10Hz signal (0.1s), 100ms elapse

  // Red LED on for 100ms
  if ((millis() % 100) < 50){
     digitalWrite(RED_LED_PORT, HIGH);
  }
  // Red LED off for 100ms
  else{
    digitalWrite(RED_LED_PORT, LOW);
  } 
}
void go_to_sleep(){

  // Blue LED Blinks on and off four times over one second...
  for(int i = 0; i < 4; i++){
    digitalWrite(BLUE_LED_PORT, HIGH);
    delay(125);
    digitalWrite(BLUE_LED_PORT, LOW);
    delay(125);
  }
  // ... and then fades to off over one second
  for(int brightness = 255; brightness >= 0; brightness--){
    analogWrite(BLUE_LED_PORT, brightness);
    delay(3.9);
  }
  
}
void diagnostic(){
  int problem = 0;
  long guess = random(9);
  if (guess <= 4) {
    problem = 5;
  }else{
    problem = 8;
  }

  // Blink the red LED as many times as the problem number.
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

void blueROF() {
  blueFreq = !blueFreq;
}

void redON() {
  if (blueFreq == HIGH) {
    digitalWrite(RED_LED_PORT,HIGH);
  }else{
    digitalWrite(RED_LED_PORT,LOW);
  }
}

void set_state_on(){
  Serial.print("ON button pressed\n");
  state = ON;
}
void set_state_go_to_sleep(){
  Serial.print("GO TO SLEEP button pressed\n");
  state = GO_TO_SLEEP;
}
void set_state_diagnostic(){
  Serial.print("DIAGNOSTIC button pressed\n");
  state = DIAGNOSTIC;
}
void set_state_run(){
  Serial.print("RUN button pressed\n");
  state = RUN;
}
