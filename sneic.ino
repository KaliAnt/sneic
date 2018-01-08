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

typedef struct dotCoordinate{
  uint8_t x;
  uint8_t y;
}dot_t;

dot_t sneic[64];

dot_t food;
uint8_t orientation;
uint8_t gamestatus = 0; //press any key for the game to start;
uint8_t sneicLen;
unsigned long elapsedTime = millis();
unsigned long previousTime;
unsigned long time;
int eaten = 0;

dot_t getRandomPosition() {
  dot_t someDot;
  someDot.x =  random(ARENA_WIDTH-1);
  someDot.y = random(ARENA_HEIGHT-1);
  return someDot;
}

void newGame() {
  gamestatus = 1; //game has started
  orientation=RIGHT;
  sneic[0].x = 4;
  sneic[0].y = 3;
  sneic[1].x = 3;
  sneic[1].y = 3;
  sneicLen = 2; 

  food.x = 5;
  food.y = 5;
  int i;
  int eaten=0;
  for(i = 2; i<64; i++) {
    sneic[i].x = 0;
    sneic[i].y = 0;
  }
}

void displaySneic() {
  int i;
  ledMatrix.clear(); 
  for(i = 0; i<sneicLen; i++) {
    ledMatrix.drawPixel(sneic[i].x,sneic[i].y);
  }
  
  ledMatrix.drawPixel(food.x,food.y); //nomnom
}

dot_t getPosition(dot_t dot, uint8_t input) {
  if(input == LEFT) {
    if(dot.x==0) { dot.x = ARENA_WIDTH-1; }
    else { dot.x = dot.x-1;}
  }
  if(input == RIGHT) {
    dot.x = dot.x+1;
    if(dot.x>ARENA_WIDTH-1) dot.x = 0;
  }
  if(input == UP) {
    if(dot.y==0) { dot.y = ARENA_WIDTH-1; }
    else { dot.y = dot.y-1; }
  }
  if(input == DOWN) {
    dot.y = dot.y+1;
    if(dot.y > ARENA_HEIGHT-1) dot.y = 0;
  }
  return dot;
}

void moveSneic(uint8_t input) {
  if(input == orientation) {
    
  } else {
    int i = 0;
    if(input == 0) input = orientation;
    if(eaten != 0) {
      sneic[sneicLen] = sneic[sneicLen-1]; //adds a body
      sneicLen++;
      eaten = 0;
    }
    for(i=1; i<sneicLen; i++) { //prev dot becomes the next one
      sneic[i] = sneic[i-1];
    }
    sneic[0] = getPosition(sneic[0],input);
    orientation = input;
  }
}
int check(dot_t dot) { //check collision with body
  int i = 0;
  for(i = 0; i<sneicLen; i++) {
    if((dot.x == sneic[0].x) && (dot.y == sneic[0].y)) { //collision
      return -1; 
    }
    return 0;
  }
}

void eat() {
  if((food.x == sneic[0].x) && (food.y == sneic[0].y)) {
    ledMatrix.erasePixel(food.x, food.y); //erase eaten food
    sneic[sneicLen] = sneic[sneicLen-1]; // add a new body
    sneicLen++;
    eaten = 1;
    food = getRandomPosition(); //spawns new food
    while(check(food) == -1) {
      food = getRandomPosition();
    }
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
  time = millis();
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

void pressAnyKey() {
  uint8_t input = readInput(); 
    if(input != 0) {
      ledMatrix.clear();
      newGame();
    } else {
      rectangleScreen();
    }
}

void setup() {
  
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  
}

void loop() {
  time = millis();
  if(gamestatus == 0) {
    pressAnyKey();//wait for player to start the game
    elapsedTime = 0;
    previousTime = 0;
  } else { //game has started
    elapsedTime+= time - previousTime;
    if(elapsedTime > 500) {
      uint8_t input = readInput();
      if(input==0) {
        moveSneic(orientation);
        orientation = input; 
      } else {
        moveSneic(input);
        orientation = input;
      }
      eat();
      displaySneic();
    }
  }
  previousTime = 0;
  ledMatrix.display();
}
