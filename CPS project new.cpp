/*Code for An Arduino-based mobile robot detects nearby flames using a flame sensor. 
On detection, it stops, alerts with an LCD message and buzzer, and reverses to avoid danger. 
It is lightweight, cost-effective, and omits extinguishing and obstacle detection systems.*/
// Project by Ridhi Wadhwani, Aditi Pradeesh, Hoorya Ayrene and Sriya Rani Khadanga

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// ----- Motor A (left motor) -----
int ENA = 5;
int IN1 = 4;
int IN2 = 3;

// ----- Motor B (right motor) -----
int ENB = 6;
int IN3 = 7;
int IN4 = 8;

// ----- Fire sensors -----
int fire1 = A0;
int fire2 = A1;
int fire3 = A2;
int fireThreshold = 100; // Lower = more sensitive, adjust based on your testing

// ----- Relay (buzzer control) -----
int relayPin = 10;

// ----- Motor speeds -----
int leftSpeed = 150;
int rightSpeed = 130;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(fire1, INPUT);
  pinMode(fire2, INPUT);
  pinMode(fire3, INPUT);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  int f1 = analogRead(fire1);
  int f2 = analogRead(fire2);
  int f3 = analogRead(fire3);

  Serial.print(f1); Serial.print(" | ");
  Serial.print(f2); Serial.print(" | ");
  Serial.println(f3);

  lcd.clear();
  lcd.setCursor(0,0);

  // Detect fire only if sensor value is WELL below the normal sunlight reading
  if ((f1 < fireThreshold) || (f2 < fireThreshold) || (f3 < fireThreshold)) {
    lcd.print("FIRE");

    // Reverse
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);

    // Beep for 3 seconds
    unsigned long startTime = millis();
    while (millis() - startTime < 3000) {
      digitalWrite(relayPin, HIGH);
      delay(200);
      digitalWrite(relayPin, LOW);
      delay(200);
    }

    // Move forward again
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NO FIRE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);
    digitalWrite(relayPin, LOW);
  } 
  else {
    lcd.print("NO FIRE");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);
    digitalWrite(relayPin, LOW);
  }

  delay(200);
}