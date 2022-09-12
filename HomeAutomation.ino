#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int trigPin = 13;
const int echoPin = 12;
const int servo = 11;
const int pir = 2;
const int yellowLed = 9;
const int yellowLed2 = 4;
const int greenLed2 =1;
const int blueLed = 5;
const int blueLed2 = 7; 
const int redLed = 3;
const int greenLed = 6;
const int buzzer =8;
const int motor = 10;
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
  pinMode(greenLed,OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  checkForPerson();
  servoClose();
  checkForMovement();
  checkForLdrSensor();
  //checkForTemperature();
}

void checkForTemperature(){
  Serial.print("Checking for temperature");
  mapTemperature();
  if (tempVal < 20){
    ledOn(blueLed2);
    Serial.println("Temperature");
    Serial.print(tempVal);
    delay(100);
  }
  else if(tempVal >= 20 && tempVal <= 24){
    ledOn(greenLed2);
    Serial.println("Temperature");
    Serial.print(tempVal);
    delay(100);
  }
  else if(tempVal >=25){
    ledOn(redLed);
    Serial.print("Temperature");
    Serial.println(tempVal);
    runMotor();
  }
}

void checkForMovement(){
  readPirSensor();
  Serial.print("PIR Status: ");
  Serial.println(pirStatus);
  if(pirStatus == true){
    buzz(buzzer);
    blink(yellowLed);
  }
}

void readPirSensor(){
  pirStatus = digitalRead(pir);
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
  int count = 30;
  if(pirStatus == true){
    for(int i = 0; i < count; i++){
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }
}

void buzz(int buzzer){
  tone(buzzer,100,3000);
}

void mapLDRValue(){
  ldrVal = analogRead(ldrPin);
  ldrVal = map(ldrVal, 3, 450, 0,255);
}

void analogWriteLeds(int value){
  analogWrite(blueLed,value);
  analogWrite(greenLed,value);
  analogWrite(redLed,value);
}

void checkForLdrSensor(){
  mapLDRValue();
  analogWriteLeds(ldrVal);
  Serial.print("LDR Value: ");
  Serial.println(ldrVal);
}

void mapTemperature(){
  tempVal = analogRead(tempPin);
  tempVal = tempVal * 0.48;
}

void runMotor(){
  analogWrite(motor, 255);
}

void ledOn(int ledPin){
  digitalWrite(ledPin, HIGH);
}
