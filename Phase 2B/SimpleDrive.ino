int speedOutput = 64;

const int HBRIDGE_1 = 10;
const int HBRIDGE_2 = 11;
const int HBRIDGE_3 = 8;
const int HBRIDGE_4 = 9;

void setup() {
  speedOutput = 0;
  // put your setup code here, to run once:
  pinMode(HBRIDGE_1, OUTPUT);
  pinMode(HBRIDGE_2, OUTPUT);
  pinMode(HBRIDGE_3, OUTPUT);
  pinMode(HBRIDGE_4, OUTPUT);
    
  Serial.begin(9600);
  Serial.setTimeout(25);
  for(int i = 0; i < 5; i++)  Serial.println("CHANGE NEWLINE TO NO LINE ENDING IN DROP-DOWN MENU AT BOTTOM OF WINDOW");
  Serial.println("Enter number between -255 and 255 in input box above to set motor speed");
}

void loop() {
  if (Serial.available() > 0) {
    String str = Serial.readString();
    speedOutput = str.toInt();
    if (speedOutput > 255) speedOutput = 255;
    if (speedOutput < -255) speedOutput = -255;
  
    String msg = "New Speed: ";
    Serial.println(msg + speedOutput);

  }
  drive_loop(speedOutput, speedOutput);
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
