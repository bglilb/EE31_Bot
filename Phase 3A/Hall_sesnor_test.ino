int speedOutput = 64;

const int HBRIDGE_1 = 10;
const int HBRIDGE_2 = 11;
const int HBRIDGE_3 = 8;
const int HBRIDGE_4 = 9;

const int BLUE_LED = 2;
const int RED_LED = 3;
const int LIGHT_SENSOR = A0;
const int HALL_SENSOR = A15;

// Colors!
const int RED = 1;
const int BLUE = 2;
const int YELLOW = 3;
const int BLACK = 4;

void setup() {
  speedOutput = 0;
  // put your setup code here, to run once:
  pinMode(HBRIDGE_1, OUTPUT);
  pinMode(HBRIDGE_2, OUTPUT);
  pinMode(HBRIDGE_3, OUTPUT);
  pinMode(HBRIDGE_4, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(HALL_SENSOR, INPUT); //Analog
    
  Serial.begin(9600);
  Serial.setTimeout(25);
  for(int i = 0; i < 5; i++)  Serial.println("CHANGE NEWLINE TO NO LINE ENDING IN DROP-DOWN MENU AT BOTTOM OF WINDOW");
  Serial.println("Enter number between -255 and 255 in input box above to set motor speed");
}

const int STOP_AT_BLUE_LINE = 1; // Design Phase 3A, bulletpoint 2
const int ARC_LEFT_TURN = 2; // Design Phase 3A, bulletpoint 4
int state = STOP_AT_BLUE_LINE;
int magfield = 0;
void loop() {
  /*
  if (Serial.available() > 0) {
    String str = Serial.readString();
    speedOutput = str.toInt();
    if (speedOutput > 255) speedOutput = 255;
    if (speedOutput < -255) speedOutput = -255;
  
    String msg = "New Speed: ";
    Serial.println(msg + speedOutput);
  }
  */
  int detected_color = light_sensor_loop();
  Serial.println(detected_color);

  magfield = analogRead(HALL_SENSOR);
  Serial.println(magfield);
  //magField = map(magField

  if (state == STOP_AT_BLUE_LINE) {
    // Drive straight until you hit blue
    if (detected_color != BLUE){
      drive_loop(45, 45);
    }
    else {
      drive_loop(0, 0);
    }
  }

  if (state == ARC_LEFT_TURN) {
    if (detected_color == BLUE) {
      drive_loop(0, 45); // turn left
    }
    else {
      drive_loop(35, 35);
    }
  }
}

void drive_loop(int leftOutput, int rightOutput){
  if (leftOutput >= 0) {
    // Left Wheel
    digitalWrite(HBRIDGE_2, LOW);
    analogWrite(HBRIDGE_1, leftOutput);
  }
  else {
    // Left Wheel
    digitalWrite(HBRIDGE_1, LOW);
    analogWrite(HBRIDGE_2, abs(leftOutput));    
  }

  if (rightOutput >= 0) {
    // Right Wheel
    digitalWrite(HBRIDGE_4, LOW);
    analogWrite(HBRIDGE_3, rightOutput);
  }
  else {
    // Right Wheel
    digitalWrite(HBRIDGE_3, LOW);
    analogWrite(HBRIDGE_4, abs(rightOutput));
  }
}

int last_red_value = 0;
int last_blue_value = 0;

int light_sensor_loop(){
    int sequence = millis() % 100;

  //flash red LED for 33ms
  if (sequence < 33) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    last_red_value = analogRead(LIGHT_SENSOR);
  }
  else if (sequence > 67) { // Flash blue LED for 33ms
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    last_blue_value = analogRead(LIGHT_SENSOR);
  }
  else {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }

  bool red = last_red_value < 840; // These values were determined through measurement.  Sean's notebook has the details
  bool blue = last_blue_value < 720;

  if (red && blue) {
    return YELLOW;
  }
  else if (red && !blue) {
    return RED;
  }
  else if (!red && blue) {
    return BLUE;
  }
  else {
    return BLACK;
  }
}
