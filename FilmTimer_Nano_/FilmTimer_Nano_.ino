//10/19/20 - I figure I need to be a lot more productive so here I am. I'm probably going to develop some film tonight so I think I need to work out the problems in this code
// so I can get more accute results. This should just output into the serial but I will input the lcd later. Also, for kicks and giggles I might try to fix it so that it will count seconds but
// display minutes. But first I need to fix the bugs.
int developS = 305; // 3:45 = 225
                  // 5:05 = 305

int blixS = 495; //  8:15 = 495

int blixStop;
int washS = 180; // 3:00
int timerLight = 5;
const int buttonPin = 6;
int buttonState = 0;
int lightSensor = A3;
int nextInvert;
int currentTimer;

int bath_stage = 0;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//To help clarify what I'm trying to do, this is a step by step walk through in filmTimerv2.txt
void setup()
{
  Serial.begin(9600);
  pinMode(timerLight, OUTPUT);
  pinMode(buttonPin, INPUT);
  //  currentTimer = developS;
  //  developerBath = true;
  lcd.init();                      // initialize the lcd
  lcd.backlight();
}
void loop()
{
  int lightValue = analogRead(lightSensor);
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    bath_stage++;
    delay(500);
  }
  if (bath_stage == 1) {
    currentTimer = developS;
  } else if (bath_stage == 2) {
    currentTimer = blixS;
  }

  if (buttonState == HIGH) {
    for (currentTimer; currentTimer >= 0; currentTimer --) {
      int lightValue = analogRead(lightSensor);
      Serial.println(bath_stage);

      //current Time readout
      lcd.setCursor(0, 0);
      lcd.print("Time:");
      if (currentTimer < 100)
      {
        lcd.setCursor(6, 0);
        lcd.print(" ");
        lcd.setCursor(7, 0);
        lcd.print(" ");
      }
      if (currentTimer < 10)
      {
        lcd.setCursor(7, 0);
        lcd.print(" ");
        lcd.setCursor(8, 0);
        lcd.print(" ");
      }
      lcd.setCursor(6, 0);
      lcd.print(currentTimer);
      lcd.setCursor(10, 0);
      lcd.print(bath_stage);

      //Next Invert Readout
      Serial.println(lightValue);
      if (nextInvert < 100)
      {
        lcd.setCursor(13, 1);
        lcd.print(" ");

        lcd.setCursor(14, 1);
        lcd.print(" ");
      }
      lcd.setCursor(0, 1);
      lcd.print("Inversion: ");
      lcd.setCursor(12, 1);
      lcd.print(nextInvert);

      if (nextInvert < 0)
      {
        lcd.setCursor(12, 1);
        lcd.print("0");
        lcd.setCursor(13, 1);
        lcd.print(" ");
        lcd.setCursor(14, 1);
        lcd.print(" ");
      }

      if (currentTimer == developS - 30) { //40 for actual test
        digitalWrite(timerLight, HIGH);
        Serial.println("This little light of mine");
      } else if (currentTimer == blixS - 30) { //40 for actual test
        digitalWrite(timerLight, HIGH);
      }
      if (lightValue > 700) //to reverse this is actual live test
      {
        digitalWrite(timerLight, LOW);
        nextInvert = currentTimer - 30; //30 for actual test
        Serial.println("I'm gonna let it shine");
      }
      if (currentTimer == nextInvert) {
        digitalWrite(timerLight, HIGH);
        Serial.println("This little light of mine");
      }

      delay(1000);
    }
  }
}
