#include "DHT.h"
#include "LedControl.h"
LedControl lc= LedControl(11,13,10,4);
unsigned long delayTime = 200;

#define LIGHT_PIN 9
#define HEAT_PIN 5
#define VENT_PIN 4
#define outputA 6
#define outputB 7

#define DHTPIN 2
#define DHTTYPE DHT11

byte invader1a[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};

DHT dht(DHTPIN, DHTTYPE);

int temperatureValue = 0;
int lightsValue = 0;
int openedWindow = 0;
int closedWindow = 0;
int potValue = 0;
int tired1 = 0;
int sad1 = 0;
int stressed1 = 0;
int happy1 = 0;
int productive1 = 0;
int sleep1 = 0;

float getTemperature()
{
  return dht.readTemperature();
}

float getHumidity()
{
  return dht.readHumidity();
}

void openLights(){
  lc.setIntensity(0, 0);
  lc.setIntensity(1, 0);
  lc.setIntensity(2, 0);
  lc.setIntensity(3, 0);
  for(int i= 0; i <= 3; i++)lc.clearDisplay(i);
  for(int i=0; i <=7 ; i++){
    lc.setColumn(3, i, 0xFF);
    lc.setColumn(0, 7-i, 0xFF);
    delay(10);
  }
  for(int i=0; i <=7 ; i++){
    lc.setColumn(2, i, 0xFF);
    lc.setColumn(1, 7-i, 0xFF);
    delay(10);
  }
}

void closeLights(){
  lc.setIntensity(0, 0);
  lc.setIntensity(1, 0);
  lc.setIntensity(2, 0);
  lc.setIntensity(3, 0);
  for(int i=0; i <=7 ; i++){
    lc.setColumn(1, i, 0x00);
    lc.setColumn(2, 7-i, 0x00);
    delay(10);
  }
  for(int i=0; i <=7 ; i++){
    lc.setColumn(0, i, 0x00);
    lc.setColumn(3, 7-i, 0x00);
    delay(10);
  }
  
}

void openCurtain() {
  lc.clearDisplay(0); // Clear all displays for the effect
  
  lc.setIntensity(0, 1);
  int totalColumns = 32; // Assuming 4 modules with 8 columns each
  int centerColumn = totalColumns / 2;

  for (int step = 0; step <= centerColumn; step++) {
    // Left side opening
    if (centerColumn - step >= 0) {
      int columnIndex = centerColumn - step;
      lc.setColumn(0, columnIndex % 8, 0xFF); // Light up the column
      lc.setColumn(4, columnIndex % 8, 0xFF);
    }

    // Right side opening
    if (centerColumn + step < totalColumns) {
      int columnIndex = centerColumn + step;
      lc.setColumn(columnIndex / 8, columnIndex % 8, 0xFF); // Light up the column
    }

    delay(100); // Adjust delay for effect speed
  }
}

void closeCurtain() {
  lc.clearDisplay(0); // Clear all displays for the effect
    lc.setIntensity(0, 1);

  int totalColumns = 32; // Assuming 4 modules with 8 columns each
  int leftEdge = 0;
  int rightEdge = totalColumns - 1;

  while (leftEdge <= rightEdge) {
    // Left side closing
    lc.setColumn(leftEdge / 8, leftEdge % 8, 0xFF); // Light up the column
    leftEdge++;

    // Right side closing
    lc.setColumn(rightEdge / 8, rightEdge % 8, 0xFF); // Light up the column
    rightEdge--;

    delay(100); // Adjust delay for effect speed
  }
}

void temperatureHigh(){
    while(temperatureValue < 255){
      temperatureValue++;
      analogWrite(HEAT_PIN, temperatureValue);
    }
    digitalWrite(VENT_PIN, LOW);
}

void temperatureLow(){
  while(temperatureValue < 50){
    temperatureValue--;
    analogWrite(HEAT_PIN, temperatureValue);
  }
  analogWrite(HEAT_PIN, 50);
  digitalWrite(VENT_PIN, HIGH);
}

void lightsOnLow(){
  while(lightsValue < 50){
    lightsValue--;
    analogWrite(LIGHT_PIN, lightsValue);
  }
  analogWrite(LIGHT_PIN, 50);
}

void lightsOff(){
  while(lightsValue > 0){
    lightsValue--;
    analogWrite(LIGHT_PIN, lightsValue);
  }
}

void happy(){
  if(openedWindow == 0){
    openLights();
    openedWindow = 1;
    closedWindow = 0;
  }
  sad1 = 0;
  stressed1 = 0;
  tired1 = 0;
  productive1 = 0;
  sleep1 = 0;
  if(happy1 == 0){
    happy1 = 1;
    Serial.println("Happy");
  }
  analogWrite(LIGHT_PIN, 255);
  temperatureHigh();
  
}

void tired(){
  if(closedWindow == 0){
      closeLights();
      openedWindow = 0;
      closedWindow = 1;
  }
  closeLights();
  lightsOnLow();
  sad1 = 0;
  stressed1 = 0;
  happy1 = 0;
  productive1 = 0;
  sleep1 = 0;
  if(tired1 == 0){
    tired1 = 1;
    Serial.println("Tired");
  }
  temperatureLow();
}

void sad(){
    if(closedWindow == 0){
      closeLights();
      openedWindow = 0;
      closedWindow = 1;
  }
  lightsOnLow();
  stressed1 = 0;
  happy1 = 0;
  productive1 = 0;
  sleep1 = 0;
  tired1 = 0;
  if(sad1 == 0){
    sad1 = 1;
    Serial.println("Sad");
  }
  temperatureHigh();
}

void stressed(){
    if(openedWindow == 0){
    openLights();
    openedWindow = 1;
    closedWindow = 0;
  }
  lightsOnLow();
  sad1 = 0;
  happy1 = 0;
  productive1 = 0;
  sleep1 = 0;
  tired1 = 0;
  if(stressed1 == 0){
    stressed1 = 1;
    Serial.println("Stressed");
  }
  temperatureLow();
}

void productive(){
    if(openedWindow == 0){
    openLights();
    openedWindow = 1;
    closedWindow = 0;
  }
  //lightsOnHigh()
  stressed1 = 0;
  sad1 = 0;
  happy1 = 0;
  sleep1 = 0;
  tired1 = 0;
  if(productive1 == 0){
    productive1 = 1;
    Serial.println("Productive");
  }
  temperatureHigh();
}

void sleep(){
    if(closedWindow == 0){
      closeLights();
      openedWindow = 0;
      closedWindow = 1;
  }
  lightsOff();
  stressed1 = 0;
  sad1 = 0;
  happy1 = 0;
  productive1 = 0;
  tired1 = 0;
  if(sleep1 == 0){
    sleep1 = 1;
    Serial.println("Sleep");
  }
  temperatureLow();
}


void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(HEAT_PIN, OUTPUT);
  pinMode(VENT_PIN, OUTPUT);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  dht.begin();
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,3);
  lc.setIntensity(1,3);
  lc.setIntensity(2,3);
  lc.setIntensity(3,3);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

void loop() {

  potValue = analogRead(A0);
  if(potValue > 0 && potValue < 175){
    tired();
  }
  else{
      if(potValue >= 175 && potValue < 350){
        sad();
      }
      else{
          if(potValue >= 350 && potValue < 525){
            happy();
          }
          else{
              if(potValue >= 525 && potValue < 700){
                stressed();
              }
              else{
                  if(potValue >= 700 && potValue < 875){
                    productive();
                  }
                  else{
                      if(potValue >=875){
                        sleep();
                      }
                  }
              }
          }
      }
  }

}
