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
#define ARENA_WIDTH 8
#define ARENA_HEIGHT 8

OliLedMatrix ledMatrix(LATCH, DATA, CLOCK);

typedef struct dot{
  uint8_t x;
  uint8_t y;
}dot_t;

dot_t sneic[64];

uint8_t orientation;
uint8_t gamestatus = 0; //press any key for the game to start;
uint8_t sneicLen;

dot_t getRandomPosition() {
  dot_t someDot;
  someDot.x =  random(ARENA_WIDTH-1);
  someDot.y = random(ARENA_HEIGHT-1);
  return someDot;
}

void newGame() {
  gamestatus = 1; //game has started
  sneic[0].x = 4;
  sneic[0].y = 3;
  sneic[1].x = 3;
  sneic[1].y = 3;
  sneicLen = 2; 
  int i;
  for(i = 2; i<64; i++) {
    sneic[i].x = 0;
    sneic[i].y = 0;
  }
}

void displaySneic() {
  int i;
  for(i = 0; i<sneicLen; ++i) {
    ledMatrix.drawPixel(sneic[i].x,sneic[i].y);
  }
}

void endGame() {
  gamestatus = 0; //game has ended
}

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
//  rectangleScreen();
  if(gamestatus == 0) {
    uint8_t input = readInput(); 
    if(input != 0) {
      ledMatrix.clear();
      newGame();
    } else {
      rectangleScreen();
      //ledMatrix.display();
      //delay(1000);
    }
  }
  if(gamestatus == 1) {
    uint8_t input = readInput();
    displaySneic();
    ledMatrix.display();
  }
}
