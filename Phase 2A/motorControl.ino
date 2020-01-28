#define GATE 2 
#define SPEEDUP 3
#define SPEEDDOWN 4
unsigned long button_time = 0;
unsigned long last_button = 0;
int speedOutput = 0;

void setup() {
  pinMode(GATE, OUTPUT);
  pinMode(SPEEDUP, INPUT_PULLUP);
  pinMode(SPEEDDOWN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  analogWrite(GATE, speedOutput);
  button_time = millis(); //This is used for debouncing the button
  if (button_time - last_button > 250) {
    if (digitalRead(SPEEDUP) == LOW && speedOutput <= 255) { //Adds 5 to duty cycle with button press
      speedOutput += 5;
    }else if(digitalRead(SPEEDDOWN) == LOW && speedOutput > 0) { //Removes 1 from duty cycles on button press
      speedOutput--;
    }
    last_button = button_time;
  }
  Serial.println(speedOutput);
}
