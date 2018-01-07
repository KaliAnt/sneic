#include "OliLedMatrix.h"
//led matrix pins
#define LATCH 12
#define DATA 10
#define CLOCK 13
//button pins
#define LEFT 6
#define RIGHT 3
#define UP 4
#define DOWN 5

OliLedMatrix ledMatrix(LATCH, DATA, CLOCK);

void rectangleScreen() {
  unsigned long time = millis();
  
  ledMatrix.clear();
  
  if (time%800 < 100)
      ledMatrix.drawRectangle(3,3,2,2); 
  else if (time%800 < 200)
      ledMatrix.drawRectangle(2,2,4,4);
  else if (time%800 < 300)
      ledMatrix.drawRectangle(1,1,6,6);
  else
      ledMatrix.drawRectangle(0,0,8,8);
      
  ledMatrix.display();
}

void setup() {
  // put your setup code here, to run once:

}
//testing youtrack
//second test for youtrack
//third test for youtrack pls work
void loop() {
  rectangleScreen();

}
