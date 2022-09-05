#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int trigPin = 13;
const int echoPin = 12;
const int servo = 11;
const int pir = 10;
const int led1 = 9;
const int led2 = 8;
const int led3 = 7;
const int led4 = 6;
const int buzzer =5;
const int driverInput1 = 4;
const int driverInput2 = 3;
const int enable = 2;
const int ldrPin = A0;
const int tempPin = A1;
int pos = 0;    // variable to store the servo position
long duration;
int distance;
int ldrVal;
int tempVal;
boolean pirStatus;

void setup() {
  myservo.attach(servo);  // attaches the servo on pin 9 to the servo object
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(driverInput1, OUTPUT);
  pinMode(driverInput2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  checkForPerson();
  servoClose();
  checkForMovement();
  checkForLdrSensor();
  delay(100);
  
}

void checkForMovement(){
  readPirSensor(pir);
  if(pirStatus == true){
    blink(led1);
    buzz(buzzer);
    delay(3000);
  }
}

void readPirSensor(int pirSensor){
  pirStatus = digitalRead(pirSensor);
}

void checkForPerson(){
  ultraSonicScan(trigPin, echoPin);
  if(distance > 5 && distance <=40){
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.println("Person");
      servoOpen();
      delay(2000);
      checkForPerson();
  }
}


void ultraSonicScan(int trigPin, int echoPin){
      // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
}

void servoOpen(){
    myservo.write(180);
}

void servoClose(){
    myservo.write(0);
}

void blink(int ledPin){
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

void buzz(int buzzer){
  tone(buzzer,100,3000);
}

void readLdr(){
  ldrVal = analogRead(ldrPin);
  ldrVal = map(ldrVal, 3, 450, 0,200);
  Serial.println(ldrVal);
}

void analogWriteLed(int value){
  analogWrite(led2,value);
  analogWrite(led3,value);
  analogWrite(led4,value);
}

void checkForLdrSensor(){
  readLdr();
  analogWriteLed(ldrVal);
}

void readTemperature(){
  tempVal = analogRead(tempPin);
}

int setSpeed(){
  
}


void runMotor(int speed){
  analogWrite(enable, speed);
  digitalWrite(driverInput1, HIGH);
  digitalWrite(driverInput2, LOW);
}