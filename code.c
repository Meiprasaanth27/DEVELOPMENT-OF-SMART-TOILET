#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 3;    
const int echoPin = 4;   
const int trigPin2 = 5; 
const int echoPin2 = 6;
const int ledPin = 21;     
const int led2Pin = 22;
const int led3Pin = 24;   
const int fanPin = 52;
const int pirPin = 2;     
const int servo1Pin = 9;
const int servo2Pin = 10;
const int servo3Pin = 40;
const int solenoidValvePin = 11;
const int solenoidValve2Pin = 13;

long duration1;
long duration2;
int distance1;
int distance2;
int count = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor2;

bool timerActive = false;
unsigned long timerStartTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);   
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);  

  pinMode(ledPin, OUTPUT);   
  pinMode(led2Pin, OUTPUT);  
  pinMode(led3Pin, OUTPUT); 

  pinMode(servo1Pin, OUTPUT); 
  pinMode(servo2Pin, OUTPUT);
  pinMode(servo3Pin, OUTPUT);  

  pinMode(pirPin, INPUT);    
  lcd.init();
  lcd.backlight();

  servoMotor1.attach(servo1Pin);
  servoMotor2.attach(servo2Pin);
  servoMotor3.attach(servo2Pin);
  Serial.begin(9600); 
}

void loop() {
  
  if (digitalRead(pirPin) == HIGH) {
   for (pos2= 0; pos2 <= 160; pos2 += 1){
    servoMotor2.write(pos2);
    delay(15);
  }
  
  }
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH);
  distance2 = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (distance < 8) {
    digitalWrite(ledPin, HIGH);  
    delay(1000); 
    digitalWrite(ledPin, LOW);   
    count++; 
  }

  if (distance2 < 8) {
    digitalWrite(led3Pin, HIGH); 
    delay(5000); 
    digitalWrite(led3Pin, LOW);  
  }

  if (count >= 10) {
    for (pos1= 0; pos1 <= 160; pos1 += 1){
    servoMotor1.write(pos1);
    delay(15); }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("CLEANING STARTED");
    delay(5000);
    lcd.clear();
    digitalWrite(led4Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("UV-C DISINFECTION"); 
    delay(5000);
    lcd.clear(); 
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("SOAP SOLUTION"); 
    delay(5000);
    lcd.clear();  
    digitalWrite(led5Pin, LOW);
    digitalWrite(led6Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("WATER"); 
    delay(10000);
    lcd.clear(); 
    digitalWrite(led6Pin, LOW);
    digitalWrite(led7Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("SANITIZER"); 
    delay(5000);
    lcd.clear();  
    digitalWrite(led7Pin, LOW);
    digitalWrite(led8Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("HOT AIR DRYING"); 
    delay(5000);
    lcd.clear();  
    digitalWrite(led8Pin, LOW);
    digitalWrite(led9Pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("DOOR CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("AIR FRESHNER");
    delay(5000);
    digitalWrite(led9Pin, LOW);
    lcd.clear();
    if (digitalRead(led9Pin) == LOW){
    for (pos1=160; pos1>= 0; pos1-= 1){ 
    servoMotor1.write(pos1);
    delay(15);} 
    }
    for (pos2=160; pos2>= 0; pos2-= 1){ 
    servoMotor2.write(pos2);
    delay(15);}
    lcd.setCursor(0, 0);
    lcd.print(" DOOR OPENED");
    delay(2000);
    lcd.clear();
    count = 0; 
  }
}