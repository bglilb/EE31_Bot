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

    if (str == "left") {
      speedOutput = 64;
      turnLeft(); 
    } else if (str == "right") {
      speedOutput = 64;
      turnRight();
    } else if (str == "circle") {
      speedOutput = 64;
      turnFullCircle();
    }
    else {
    
    speedOutput = str.toInt();
    if (speedOutput > 255) speedOutput = 255;
    if (speedOutput < -255) speedOutput = -255;
    
    String msg = "New Speed: ";
    Serial.println(msg + speedOutput);
    }

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

void turnRight() {
  Serial.println("Turning Left");
  //Wheel A
  digitalWrite(HBRIDGE_2, LOW);
  analogWrite(HBRIDGE_1, speedOutput);
  //Wheel B
  digitalWrite(HBRIDGE_3, LOW);
  digitalWrite(HBRIDGE_4, LOW);
  delay(3350);
  speedOutput = 0;
  stopAll();
}

void turnLeft() {
  Serial.println("Turning Right");
  //Wheel A
  digitalWrite(HBRIDGE_1, LOW);
  digitalWrite(HBRIDGE_2, LOW);
  //Wheel B
  digitalWrite(HBRIDGE_4, LOW);
  analogWrite(HBRIDGE_3, speedOutput);
  delay(3350);
  speedOutput = 0;
  stopAll();
}

void turnFullCircle() {
  //Wheel A
  digitalWrite(HBRIDGE_2, LOW);
  analogWrite(HBRIDGE_1, speedOutput);
  //Wheel B
  digitalWrite(HBRIDGE_3, LOW);
  analogWrite(HBRIDGE_4, speedOutput);
  delay(4500);
  speedOutput = 0;
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
