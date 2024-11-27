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
int buzzerFreq = 1500; //frequency in Hertz at which buzzer sounds. chosen based on amplitude, according to buzzer documentation
int delayTime = 500; //time in milliseconds for arduino to delay until loop() restarts
int maxDist = 50; //the approximate length of the biscuit tube. used to determine "open" or "closed" state of lid.

void setup() {
  // set baud rate to match arduino for debugging
  Serial.begin(9600);
  // define pins as inputs or outputs
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets buzzerPin as output
}

int initDist = readcurrentDist(); //placeholder value for initial distance. properly initialised in loop()

void loop() {
  //scan for current distance to object
  int currentDist = readcurrentDist();
  //print readings to console for debugging
  Serial.print("Distance in cm: ");
  Serial.println(currentDist);
  Serial.print("The initialised distance is: ");
  Serial.println(initDist);

  // buzzer test: triggers buzzer if the following conditions are met: 
  if (lidOpen(currentDist) == true){
    noTone(buzzerPin);
  } else if (currentDist != initDist){
    tone(buzzerPin, buzzerFreq);
  } else {
    noTone(buzzerPin);
  }
  delay(delayTime); //wait for the delay time, in milliseconds, for update
}

int readcurrentDist(){ //reads the current distance between rangefinder and closest object when called
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH); 
  return 34400*duration/2000000; // returns the currentDist to object in centimeters
}

bool lidOpen(int a){ //checks if lid is open or not, by comparing parameter with maxDist
  if (a > maxDist){ //condition implies rangefinder is generating data from objects outside the tin...
    return true; //...therefore lid must be open
  } else { //condition implies rangefinder values are below maxDist...
    return false; //...therefore lid must be closed
  }
}