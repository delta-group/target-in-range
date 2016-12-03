// Sonar Pins
const int trigPin = 2;
const int echoPin = 4;

/************************************************************************/
/*                     Device function definitions                      */
/************************************************************************/
int getDistance() {
  // establish variables for duration of the ping, 
  // and the distance result in centimeters:
  long duration, cm;

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
  cm = duration / 29 / 2;

  // display distance on Serial Monitor (when hooked up to a computer)
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // poll the sensor 10 times a second
  delay(100);
}

/************************************************************************/
/*                           SETUP function                             */
/************************************************************************/
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

/************************************************************************/
/*                           MAIN loop                                  */
/************************************************************************/
void loop()
{

}
