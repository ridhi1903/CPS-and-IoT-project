/*Code for An Arduino-based mobile robot detects nearby flames using a flame sensor. 
On detection, it stops, alerts with an LCD message and buzzer, and reverses to avoid danger. 
It is lightweight, cost-effective, and omits extinguishing and obstacle detection systems.*/
// Project by Ridhi Wadhwani, Aditi Pradeesh, Hoorya Ayrene and Sriya Rani Khadanga

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Motor A (left motor)
int ENA = 5;
int IN1 = 4;
int IN2 = 3;

// Motor B (right motor)
int ENB = 6;
int IN3 = 7;
int IN4 = 8;

// Fire sensors
int fire1 = A0;
int fire2 = A1;
int fire3 = A2;

// speed
int leftSpeed = 150;
int rightSpeed = 130;

// flag to remember if fire was detected
bool fireDetectedOnce = false;

void setup() {
  // motors
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // fire sensors
  pinMode(fire1, INPUT);
  pinMode(fire2, INPUT);
  pinMode(fire3, INPUT);

  // lcd
  lcd.init();
  lcd.backlight();
}

void loop() {
  int f1 = analogRead(fire1);
  int f2 = analogRead(fire2);
  int f3 = analogRead(fire3);

  int threshold = 1000;

  lcd.clear();
  lcd.setCursor(0,0);

  if(f1 < threshold || f2 < threshold || f3 < threshold){
    // FIRE detected
    fireDetectedOnce = true;
  }

  if(fireDetectedOnce) {
    // once fire detected, keep reversing
    lcd.print("FIRE");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);
  } else {
    // no fire detected yet, move forward
    lcd.print("NO FIRE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);
  }

  delay(200);
}