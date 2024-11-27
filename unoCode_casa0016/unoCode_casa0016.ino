/*  Ethan Taylor 2024
 *  Based on:
 *  https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/ 
 *  Templated from CASA0016 Workshop 3
 */

//map numbered pins to circuit component functions
#define trigPin 2 //pin 2 mapped to trigger pin on rangefinder
#define echoPin 3 //pin 3 mapped to echo pin on rangefinder
#define buzzerPin 4 //pin 4 mapped to buzzer (voltage input)

// initialise variables to global scope
int distThreshold = 200; //distance in cm for buzzer to trigger
int buzzerFreq = 1500; //frequency in Hertz at which buzzer sounds

void setup() {
  // set baud rate to match arduino for debugging
  Serial.begin(9600);
  // define pins as inputs or outputs
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets buzzerPin as output
  // declare initial rangefinder value
  // int initDist = distance; //this detects current capacity of biscuits to compare with in loop
}


void loop() {
  int distance = readDistance();
  
  Serial.print("Distance in cm: ");
  Serial.println(distance);
  // Serial.print("The initialised distance is: ");
  // Serial.println(initDist);


  // buzzer test - triggers buzzer if distance is over 2 metres
  if (distance > distThreshold){
    tone(buzzerPin, buzzerFreq);
  } else {
    noTone(buzzerPin); //turn off buzzer when distance falls back below distThreshold 
  }
  delay(1000); //wait every 500milliseconds for update
}

int readDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH); 
  return 34400*duration/2000000; // returns the distance to object in centimeters
}