#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
// Define the pin numbers for the ultrasonic sensors
const int trigPin = 3;    // Trigger pin for ultrasonic sensor 1
const int echoPin = 4;    // Echo pin for ultrasonic sensor 1
const int trigPin2 = 5;   // Trigger pin for ultrasonic sensor 2
const int echoPin2 = 6;
const int ledPin = 21;     // Pin for the first LED indicator    // Pin for the second LED indicator
const int led2Pin = 22;
const int led3Pin = 24;   // Pin for the third LED indicator   // Pin for the fourth LED indicator
const int fanPin = 52;
const int pirPin = 2;     // Pin for the PIR sensor
const int servo1Pin = 9;
const int servo2Pin = 10;
const int servo3Pin = 40;
const int solenoidValvePin = 11;
const int solenoidValve2Pin = 13;

// Variables to store the distances and counts
long duration1;
long duration2;
int distance1;
int distance2;
int count = 0;

// Define the LCD display object
LiquidCrystal_I2C lcd(0x27, 16, 2);
 // 0x27 is the default I2C address for the LCD
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor2;

bool timerActive = false;
unsigned long timerStartTime = 0;

void setup() {
  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);  // Set trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Set echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigPin2 as an OUTPUT
  pinMode(echoPin2, INPUT);  // Set echoPin2 as an INPUT

  // Initialize the LED pins
  pinMode(ledPin, OUTPUT);   // Set ledPin as an OUTPUT  // Set led2Pin as an OUTPUT
  pinMode(led2Pin, OUTPUT);  // Set led3Pin as an OUTPUT
  pinMode(led3Pin, OUTPUT); 

  pinMode(servo1Pin, OUTPUT); // Set led7Pin as an OUTPUT
  pinMode(servo2Pin, OUTPUT);
  pinMode(servo3Pin, OUTPUT);  

  // Initialize the PIR sensor pin
  pinMode(pirPin, INPUT);    // Set pirPin as an INPUT

  // Initialize the LCD display
  lcd.init();
  lcd.backlight();

  servoMotor1.attach(servo1Pin);
  servoMotor2.attach(servo2Pin);
  servoMotor3.attach(servo2Pin);


  // Start serial communication for debugging (optional)
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  // Check if motion is detected by the PIR sensor
  if (digitalRead(pirPin) == HIGH) {
   for (pos2= 0; pos2 <= 160; pos2 += 1){
    servoMotor2.write(pos2);
    delay(15);
  }
  
  }
  // Trigger the first ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the distance from the first ultrasonic sensor
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Trigger the second ultrasonic sensor to send a pulse
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Measure the distance from the second ultrasonic sensor
  duration = pulseIn(echoPin2, HIGH);
  distance2 = duration * 0.034 / 2;

  // Print the distances for debugging (optional)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Check if an object is detected within 8 cm by the second ultrasonic sensor
  if (distance < 8) {
    digitalWrite(ledPin, HIGH);  // Turn on the first LED
    delay(1000); // Keep both LEDs on for 1 second
    digitalWrite(ledPin, LOW);   // Turn off the first LED
    count++; // Increment the count
  }

  // Check if an object is detected by ultrasonic sensor 2
  if (distance2 < 8) {
    digitalWrite(led3Pin, HIGH); // Turn on led3
    delay(5000); // Keep led3 on for 5 seconds
    digitalWrite(led3Pin, LOW);  // Turn off led3
  }

  // Check if the count reaches 10
  if (count >= 10) {
    for (pos1= 0; pos1 <= 160; pos1 += 1){
    servoMotor1.write(pos1);
    delay(15); }// Turn on led4 continuously
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("CLEANING STARTED");
    delay(5000);
    lcd.clear();// Keep led4 on for 5 seconds
    digitalWrite(led4Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("UV-C DISINFECTION"); // Turn on led5
    delay(5000);
    lcd.clear(); // Keep led5 on for 10 seconds
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("SOAP SOLUTION"); // Turn on led5
    delay(5000);
    lcd.clear();  // Keep led5 on for 10 seconds
    digitalWrite(led5Pin, LOW);
    digitalWrite(led6Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("WATER"); // Turn on led6
    delay(10000);
    lcd.clear();  // Keep led6 on for 5 seconds
    digitalWrite(led6Pin, LOW);
    digitalWrite(led7Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("SANITIZER"); // Turn on led7
    delay(5000);
    lcd.clear();  // Keep led7 on for 5 seconds
    digitalWrite(led7Pin, LOW);
    digitalWrite(led8Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("HOT AIR DRYING"); // Turn on led6
    delay(5000);
    lcd.clear();  // Keep led6 on for 5 seconds
    digitalWrite(led8Pin, LOW);
    digitalWrite(led9Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("AIR FRESHNER"); // Turn on led6
    delay(5000);  // Keep led6 on for 5 seconds
    digitalWrite(led9Pin, LOW);
    lcd.clear();
    if (digitalRead(led9Pin) == LOW){
    for (pos1=160; pos1>= 0; pos1-= 1){ 
    servoMotor1.write(pos1);
    delay(15);} // Turn off led4
    }
     for (pos2=160; pos2>= 0; pos2-= 1){ 
    servoMotor2.write(pos2);
    delay(15);}
    lcd.setCursor(0, 0);
    lcd.print(" DOOR OPENED");
    delay(2000);
    lcd.clear();
    count = 0; // Reset the count to zero
  }
}