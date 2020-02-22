const int BLUE_LED = 10;
const int RED_LED = 11;
const int LIGHT_SENSOR = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

    
  Serial.begin(9600);
  Serial.setTimeout(25);
  for(int i = 0; i < 5; i++)  Serial.println("CHANGE NEWLINE TO NO LINE ENDING IN DROP-DOWN MENU AT BOTTOM OF WINDOW");
  Serial.println("Enter number between -255 and 255 in input box above to set motor speed");
}


bool light_sensor_on = true;
void loop(){
  int detected_color = light_sensor_loop();
  Serial.println(detected_color);
}


const int RED = 1;
const int BLUE = 2;
const int YELLOW = 3;
const int BLACK = 4;

int last_red_value = 0;
int last_blue_value = 0;
int light_sensor_loop(){
    int sequence = millis() % 100;
  
  if (sequence < 33) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    last_red_value = analogRead(LIGHT_SENSOR);
  }
  else if (sequence > 67) {
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    last_blue_value = analogRead(LIGHT_SENSOR);
  }
  else {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }

  bool red = last_red_value < 840;
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
