int speedOutput = 64;

const int HBRIDGE_1 = 11;
const int HBRIDGE_2 = 10;
const int HBRIDGE_3 = 9;
const int HBRIDGE_4 = 8;

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
    
  if (speedOutput >= 0) {
    // Wheel A
    digitalWrite(HBRIDGE_2, LOW);
    analogWrite(HBRIDGE_1, speedOutput);

    // Wheel B
    digitalWrite(HBRIDGE_4, LOW);
    analogWrite(HBRIDGE_3, speedOutput);
  }
  else {
    // Wheel A
    digitalWrite(HBRIDGE_1, LOW);
    analogWrite(HBRIDGE_2, abs(speedOutput));

    // Wheel B
    digitalWrite(HBRIDGE_3, LOW);
    analogWrite(HBRIDGE_4, abs(speedOutput));
  }


}

void stopAll() {
  digitalWrite(HBRIDGE_1, LOW);
  digitalWrite(HBRIDGE_2, LOW);
  digitalWrite(HBRIDGE_3, LOW);
  digitalWrite(HBRIDGE_4, LOW);
}

void turnLeft() {
  //Wheel A
  digitalWrite(HBRIDGE_1, LOW);
  analogWrite(HBRIDGE_2, speedOutput);
  //Wheel B
  digitalWrite(HBRIDGE_4, LOW);
  analogWrite(HBRIDGE_3, speedOutput);
  delay(500);
  stopAll();
}

void turnRight() {
  //Wheel A
  digitalWrite(HBRIDGE_2, LOW);
  analogWrite(HBRIDGE_1, speedOutput);
  //Wheel B
  digitalWrite(HBRIDGE_3, LOW);
  analogWrite(HBRIDGE_4, speedOutput);
  delay(500);
  stopAll();
}

void turnFullCircle() {
  //Wheel A
  digitalWrite(HBRIDGE_2, LOW);
  analogWrite(HBRIDGE_1, speedOutput);
  //Wheel B
  digitalWrite(HBRIDGE_3, LOW);
  analogWrite(HBRIDGE_4, speedOutput);
  delay(1000);
  stopAll();
}

/*
int incomingByte = 0;
int dutycycle = 0;
void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 5; i++)  Serial.println("CHANGE NEWLINE TO NO LINE ENDING IN DROP-DOWN MENU AT BOTTOM OF WINDOW");

}

void loop() {
      if(Serial.available() > 0){
          String str = "";
          char c = Serial.read();
          str += c;
      while(Serial.available()>0)
      {
        char c = Serial.read();
        str += c;
      }
      str.replace("\n", ""); //str.remove(1, str.length() - 1);
      int dutycycle = str.toInt();
      Serial.print(dutycycle);
    }
} */

