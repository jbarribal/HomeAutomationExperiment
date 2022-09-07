#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int trigPin = 13;
const int echoPin = 12;
const int servo = 11;
const int pir = 10;
const int yellowLed = 9;
const int blueLed = 5;
const int redLed = 3;
const int greenLed = 6;
const int buzzer =8;
const int driverInput1 = 4;
const int driverInput2 = 7;
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
  pinMode(driverInput1, OUTPUT);
  pinMode(driverInput2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  checkForPerson();
  servoClose();
  checkForMovement();
  checkForLdrSensor();
  checkForTemperature();
  delay(100);
  
}

void checkForTemperature(){
  getTemperature();
  if (tempVal < 20){
    ledOn(blueLed);

  }
  else if(tempVal >= 20 && tempVal <= 24){
    ledOn(greenLed);
  }
  else if(tempVal >24){
    ledOn(redLed);
    runMotor();
  }
}

void checkForMovement(){
  readPirSensor(pir);
  if(pirStatus == true){
    blink(yellowLed);
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

void mapLDRValue(){
  ldrVal = analogRead(ldrPin);
  ldrVal = map(ldrVal, 3, 450, 0,255);
}

void analogWriteLeds(int value){
  analogWrite(greenLed,value);
  analogWrite(blueLed,value);
  analogWrite(redLed,value);
}

void checkForLdrSensor(){
  mapLDRValue();
  analogWriteLeds(ldrVal);
}

void getTemperature(){
  tempVal = analogRead(tempPin);
}

void runMotor(){
  digitalWrite(driverInput1, HIGH);
  digitalWrite(driverInput2, LOW);
  digitalWrite(enable, HIGH);
}

void ledOn(int ledPin){
  digitalWrite(ledPin, HIGH);
}
