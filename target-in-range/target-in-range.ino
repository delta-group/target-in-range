/************************************************************************/
/*                           PIN assignments                            */
/************************************************************************/

// Sonar Pins
const int trigPin   = 2;
const int echoPin   = 4;

// LED Pins
const int redPin    = 11;
const int greenPin  = 12;
const int bluePin   = 13;

// Buzzer
const int buzzPin   = 9;

// Button
const int buttonPin = 5;

/************************************************************************/
/*                     Device function definitions                      */
/************************************************************************/

// Sonar 
int getDistance() {
  // establish variables for duration of the ping, 
  // and the distance result in centimeters:
  long duration, centimeters;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  centimeters = duration / 29 / 2;

  // display distance on Serial Monitor (when hooked up to a computer)
  Serial.print(centimeters);
  Serial.print("cm");
  Serial.println();

  return centimeters;
}

// Buzzer
void buzzEnable(void) {
  // read the current state of the button (1 if pressed, 0 if not)
  int buttonPressed = digitalRead(buttonPin);

  if (buttonPressed) {
    // only buzz the buzzer if button pressed
    tone(buzzPin, 1000);  
  }
  else {
    // otherwise turn it off
    noTone(buzzPin);
  }
}

void buzzDisable(void) {
  // turn off the buzzer (called when target is out of range)
  noTone(buzzPin);
}

// LED
int LEDColor(int distance) {
  if (distance >= 200) {
    // RED is represented by 2
    return 2;           
  }
  else if (distance >= 130) {
    // YELLOW is represented by 1
    return 1;
  }
  else {
    // GREEN is represented by 0
    return 0;
  }
}

void turnOnLED(int color) {
  switch(color){
    case 0: 
      // GREEN
      digitalWrite(redPin, LOW);   
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, HIGH);
      buzzEnable();
      break;
    case 1: 
      // YELLOW
      digitalWrite(redPin, HIGH);  
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, HIGH);
      buzzDisable();
      break;
    case 2: 
      // RED
      digitalWrite(redPin, HIGH);
      digitalWrite(bluePin, LOW);
      digitalWrite(greenPin, LOW);
      buzzDisable();
      break;
  }
}

/************************************************************************/
/*                           SETUP function                             */
/************************************************************************/
void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  // setup LED pins for output
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // setup Buzzer pin for output
  pinMode(buzzPin, OUTPUT);

  // setup Button pin for input
  pinMode(buttonPin, INPUT);
}

/************************************************************************/
/*                           MAIN loop                                  */
/************************************************************************/
void loop()
{
  // measure distance in cm
  int distance = getDistance();
  int color = LEDColor(distance);
  turnOnLED(color);
  
  delay(250);
}
