#include <Servo.h>
#include <Wire.h>
// #include <LiquidCrystal.h>
//m1 is the direction motor
//m2 is the power motor
// L is left 
// R is right
// F is forward
// B is Backward

int m1LR = 13; 
int m2F = 12; 
int m2B = 11; 
int l1 = 10; //l1 is the green LED
int l2 = 9; //l2 is the red LED
int i2cAddress = 0x27;

//initialize PIR grid system
int pir2 = 2;
int pir3 = 3;
int pir4 = 4;
int pir5 = 5;
int pir6 = 6;
int pir7 = 7;
int pir8 = 8;

// create servo object
Servo servo1;

// LiquidCrystal lcd(i2cAddress, 16, 2);

void setup() {
  // put your setup code here, to run once:

  pinMode(m2F, OUTPUT);
  pinMode(m2B, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  servo1.attach(m1LR);
  // lcd.init();
  // lcd.backlight();

//Using a grid system of  PIR sensors to collect input motion.
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
  pinMode(pir5, INPUT);
  pinMode(pir6, INPUT);
  pinMode(pir7, INPUT);
  pinMode(pir8, INPUT);

  //Serial Monitor
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //pin 0 is at the north-west side as in the matric:
  // |2 3 4|
  // |  5  |
  // |6 7 8|
  if(!digitalRead(pir2) && !digitalRead(pir3) && !digitalRead(pir4) && !digitalRead(pir5) && !digitalRead(pir6) && !digitalRead(pir7) && !digitalRead(pir8)){
    Serial.println("No Movement!");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("No Movement");
    digitalWrite(l1, 0);
    digitalWrite(l2, 0);
    digitalWrite(m2F, 0);
    digitalWrite(m2B, 0);
    servo1.write(90);
    delay(10);
  } else {
  if(digitalRead(pir2) == 1) {
    start();
    steerLeft();
    goForward();
  } else {
    if(digitalRead(pir3) == 1) {
      start();
      goForward();
    } else {
      if(digitalRead(pir4) == 1) {
        start();
        steerRight();
        goForward();
      } else {
        if(digitalRead(pir5) == 1) {
          stop();
        } else {
          if(digitalRead(pir6) == 1) {
            start();
            steerLeft();
            goBackward();
          } else {
            if(digitalRead(pir7) == 1) {
              start();
              goBackward();
            } else {
              if(digitalRead(pir8) == 1) {
                start();
                steerRight();
                goBackward();
              }
            }
          }
        }
      }
    }
  }            
  } 
  //Proteus causes the PIR sensor to keep their pulses so this should counter it
}


void steerLeft(){
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
  servo1.write(0);
    Serial.println("Steering Left");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Steering Left");
    delay(50);
};
  
  void steerRight(){
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
  servo1.write(180);
    Serial.println("Steering Right");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Steering Right");
    delay(50);
};

  void goForward() {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m2F, 1);
    digitalWrite(m2B, 0);
    Serial.println("Going Forward");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Going Forward");
    delay(50);
  };
  
  void goBackward() {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m2F, 0);
    digitalWrite(m2B, 1);
    Serial.println("Going Backward");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Going Backward");
    delay(50);
  };

  void stop() {
    digitalWrite(l1, 0);
    digitalWrite(l2, 1);
    digitalWrite(m2F, 0);
    digitalWrite(m2B, 0);
    servo1.write(90);
    Serial.println("Stopped");
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Stopped");
    delay(50);
  }

  void start() {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    delay(50);
  }