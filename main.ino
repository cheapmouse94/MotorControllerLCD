#include <LiquidCrystal.h> 
#include <Wire.h>
#include "max6675.h"

LiquidCrystal lcd(2,3,4,5,6,7);
int emergency_button = 0;
int toggle_motor_button = 8;
int enabled_motor = 9;
int led_motor = 1;
int analogTacho = A0;

int EBs, EMBs;

// Temperature config - thermocouple type K
MAX6675 Module(11, 12, 13);
float temp;
float Ts;

// Motor config - DC Motor 12 VDC 2A
int enabled_motor_state = LOW;
float slope = 0.06;
int analogSpeed;
float motor_speed;

void setup() {
  lcd.begin(16, 2); 
  Serial.begin(9600);
  pinMode(emergency_button, INPUT);
  pinMode(toggle_motor_button, INPUT);
  pinMode(enabled_motor, OUTPUT);
  pinMode(led_motor, OUTPUT);
  digitalWrite(enabled_motor, LOW);
  digitalWrite(led_motor, LOW);
  lcd.clear()
}


int toggle_enable_motor_button(){
  EMBl = EMB;
  EMB = digitalRead(emergency_button);
  if (EMBl == LOW && EMB == HIGH){
    enabled_motor_state = !enabled_motor_state;
  }
  return enabled_motor_state;
}

int get_temperature_emergency(t){
  if t > 70.0{return true;}
  else {return false;}
}

float get_motor_speed(float s, int a){
  return (a*(5.0 / 1023.0))/s;
  }

void loop(){
  
  analogSpeed = analogRead(A0);
  temp = Module.readCelsius();
  EBs = digitalRead(emergency_button);
  EMBs = toggle_enable_motor_button();
  Ts = get_temperature_emergency(temp);

  if (EBs == LOW){
    if (EMBs == HIGH){
      if (Ts){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Motor is ");
        lcd.setCursor(0,1);
        lcd.print("overheating!");
        digitalWrite(enabled_motor, LOW);
        digitalWrite(led_motor, LOW);
      }
      else{ 
        motor_speed = get_motor_speed(slope, analogSpeed);
        digitalWrite(enabled_motor, HIGH);
        digitalWrite(led_motor, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Motor speed: ");
        lcd.print(motor_speed);
        lcd.setCursor(0,1);
        lcd.print("Temperature: ");
        lcd.print(temp);}
    }
    else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Motor is diabled");
    digitalWrite(enabled_motor, LOW);
    digitalWrite(led_motor, LOW);
    }
  }
  else{
    lcd.clear();
    Serial.print("Emergency stop!");
    lcd.setCursor(0,0);
    lcd.print("Emergency stop!")
    lcd.setCursor(0,1);
    digitalWrite(enabled_motor, LOW);
    digitalWrite(led_motor, LOW);
    }
  delay(500);
}
