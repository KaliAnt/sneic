#include "OliLedMatrix.h"
#include <stdint.h>
//led matrix pins
#define LATCH 12
#define DATA 10
#define CLOCK 13
//button pins
#define LEFT 6
#define RIGHT 3
#define UP 4
#define DOWN 5
//input values

OliLedMatrix ledMatrix(LATCH, DATA, CLOCK);

typedef struct dot{
  int x;
  int y;
}dot_t;

int orientation;

uint8_t readInput() {
  int left = digitalRead(LEFT);
  int right = digitalRead(RIGHT);
  int up = digitalRead(UP);
  int down = digitalRead(DOWN);

  if(left == HIGH) {
    return LEFT;
  }
  else if(right == HIGH) {
    return RIGHT;
  }
  else if(up == HIGH) {
    return UP;
  }
  else if(down == HIGH) {
    return DOWN;
  }
  else return 0; //nothing read
}

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
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
}

void loop() {
  rectangleScreen();
  uint8_t input = readInput();
  

}
