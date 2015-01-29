#include <Bounce2.h>

int data = 8;
int clock = 9;
int latch = 10;
int button1 = 7;
int button2 = 6;
int button3 = 5;
int potPin = 0;

int shiftDelay = 1;
int letterDelay = 10;

unsigned long lastMillis = 0;
unsigned long lastPush = 0;
int gameSpeed = 500;

int currentDirection = 0; 

int score = 0;

int maze[8][8];

int headX = 0;
int headY = 0;

int snakeLength = 1;
int snakeX[64];
int snakeY[64];

int eggX = 0;
int eggY = 0;

int tempX = 0;
int tempY = 0;

 byte red   = B00000000;
 byte green = B00000000; 
 byte row   = B00000000; 
 int dot = 0;
 
 int val; // The value coming from the sensor
 int percent; // The mapped value
 
 byte b;
 byte temp [8] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
 #define A {B00000000,B01110000,B10001000,B10001000,B11111000,B10001000,B10001000,B00000000}
 #define C {B00000000,B01111000,B10000000,B10000000,B10000000,B10000000,B01111000,B00000000}
 #define E {B00000000,B11111000,B10000000,B10000000,B11110000,B10000000,B11111000,B00000000}
 #define G {B00000000,B01110000,B10001000,B10000000,B10111000,B10001000,B01110000,B00000000}
 #define I {B00000000,B11111000,B00100000,B00100000,B00100000,B00100000,B11111000,B00000000}
 #define M {B00000000,B10001000,B11011000,B10101000,B10101000,B10001000,B10001000,B00000000}
 #define O {B00000000,B01110000,B10001000,B10001000,B10001000,B10001000,B01110000,B00000000}
 #define R {B00000000,B11110000,B10001000,B10001000,B11110000,B10001000,B10001000,B00000000}
 #define S {B00000000,B01110000,B10001000,B01100000,B00010000,B10001000,B01110000,B00000000}
 #define U {B00000000,B10001000,B10001000,B10001000,B10001000,B10001000,B01110000,B00000000}
 #define V {B00000000,B10001000,B10001000,B10001000,B10001000,B01010000,B00100000,B00000000}
 #define Y {B00000000,B10001000,B10001000,B01010000,B00100000,B00100000,B00100000,B00000000}
 #define COL {B00000000,B01100000,B01100000,B00000000,B00000000,B01100000,B01100000,B00000000}
 #define SPACE {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}
byte numbers[10][8] = {{B00000000,B01110000,B10011000,B10101000,B10101000,B11001000,B01110000,B00000000},
                       {B00000000,B00100000,B01100000,B10100000,B00100000,B00100000,B01110000,B00000000},
                       {B00000000,B01110000,B10001000,B00001000,B01110000,B10000000,B11111000,B00000000},
                       {B00000000,B11110000,B00001000,B00001000,B01111000,B00001000,B11110000,B00000000},
                       {B00000000,B10001000,B10001000,B10001000,B01111000,B00001000,B00001000,B00000000},
                       {B00000000,B11111000,B10000000,B11110000,B00001000,B10001000,B01110000,B00000000},
                       {B00000000,B01110000,B10000000,B11110000,B10001000,B10001000,B01110000,B00000000},
                       {B00000000,B11111000,B00001000,B00001000,B01111000,B00001000,B00001000,B00000000},
                       {B00000000,B01110000,B10001000,B01110000,B10001000,B10001000,B01110000,B00000000},
                       {B00000000,B01110000,B10001000,B01111000,B00001000,B00001000,B01110000,B00000000}};

 const int lettersCount =24;//this is the number of patterns you want to display
 byte letters[][8]={G,A,M,E,SPACE,O,V,E,R,SPACE,Y,O,U,R,SPACE,S,C,O,R,E,SPACE,I,S,COL,SPACE};// the patterns order


Bounce  bouncer1  = Bounce();
Bounce  bouncer2  = Bounce();
Bounce  bouncer3  = Bounce();

int button1value = HIGH;
int button2value = HIGH;
int button3value = HIGH;


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(data, OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(potPin,INPUT);
  Serial.begin(9600); // add this to the setup function
  
  pinMode(button1,INPUT_PULLUP);
  bouncer1.attach( button1 );
  bouncer1.interval(25);

  pinMode(button2,INPUT_PULLUP);
  bouncer2.attach( button2 );
  bouncer2.interval(25);
  
  pinMode(button3,INPUT_PULLUP);
  bouncer3.attach( button3 );
  bouncer3.interval(25);
  
  
  randomSeed(analogRead(0));
  reset();
}

// the loop function runs over and over again forever
void loop() {
  bouncer1.update();
  bouncer2.update();
  bouncer3.update();
//  if (millis()-lastPush >=50){
    if(bouncer1.read() == LOW && button1value == HIGH){
       if(currentDirection==0){ // RIGHT
           currentDirection = 3;
       }else if(currentDirection==1){ // UP 
            currentDirection = 0;      
       }else if(currentDirection==2){ // LEFT
            currentDirection = 3;
       } else{ // DOWN
            currentDirection = 0; 
       }
    }
    button1value = bouncer1.read();
    
    if(bouncer2.read() == LOW && button2value == HIGH){
        if(currentDirection==0){ // RIGHT
           currentDirection = 1;
       }else if(currentDirection==1){ // UP 
            currentDirection = 2;      
       }else if(currentDirection==2){ // LEFT
            currentDirection = 1;
       } else{ // DOWN
            currentDirection = 2; 
       }
    }
    button2value = bouncer2.read();
    
    if(bouncer3.read() == LOW && button3value == HIGH){
      reset(); 
    }
    button3value = bouncer3.read();
//    lastPush = millis();
//  }
//score = 89;
//printGOver();
  updategameSpeed();
  moveSnake();
  updateMaze();
  draw();

// letters[26] = numbers[0];
//  delay(10);
}

//int a = 0;
void moveSnake(){
  if (millis()-lastMillis >=gameSpeed){
     // change direction  
     if(currentDirection==0){ // RIGHT
        headY =abs(headY-1+8)%8;
     }else if(currentDirection==1){ // UP 
         headX =(headX+1)%8; 
     }else if(currentDirection==2){ // LEFT
      headY =(headY+1)%8;
         
     } else{ // DOWN
         headX =abs(headX-1+8)%8;  
     }
     
    // check for eating egg 
    if(headX == eggX && headY == eggY){
      score++;
      snakeLength++;
      generateEgg();
    }

      
    // check for eating itself
    for(int i = 1;i<snakeLength;i++){
     if (headX == snakeX[i] && headY == snakeY[i]){ 
       gameOver();
     } 
    }

    updateSnake();
    updateMaze(); 

    lastMillis = millis(); 
  }
  
}


 void clearMaze(){
  for(int i =0;i<8;i++){
    for(int j = 0; j<8;j++){
     maze[i][j]=0;   
    }  
   } 
 }
 

void drawSnake(){
   maze[snakeX[0]][snakeY[0]] = 3;
  for(int i = 1;i<snakeLength;i++){
   maze[snakeX[i]][snakeY[i]] = 1;
  } 
 }
 
void drawEgg(){
  maze[eggX][eggY] = 2; 
 }
 
 
void generateEgg(){
 eggX = random(8);
 eggY = random(8);

 while(!checkEgg()){
//    eggX = random(8);
//    eggY = random(8); 
    generateEgg();
  }
    
}
 
boolean checkEgg(){
  for(int i = 0 ; i < snakeLength ; i++){
    if(snakeX[i]==eggX&&snakeY[i]==eggY){
      return false;
    }    
  } 
//   Serial.println("IN");
  return true;  
}

void updateSnake(){
  for (int i = 0;i<snakeLength;i++){  
    tempX = snakeX[i];
    tempY = snakeY[i];
    
    snakeX[i] = headX;
    snakeY[i] = headY;
    
    headX = tempX;
    headY = tempY;    
  }
  
    headX =  snakeX[0];
    headY =  snakeY[0] ;
}

void updateMaze(){
   clearMaze();  
 
  drawSnake();
   drawEgg();
//   draw(); 
}

void gameOver(){
  for(int k = 0;k<50;k++){
for(int i =0;i<8;i++){
    for(int j = 0; j<8;j++){
     maze[i][j]=random(4);   
    }  
   }
  draw(); 
  }
  
  clearMaze();
  printGOver();
  reset();
}

void reset(){
   currentDirection = 1; 
   score = 0; 
   
  for(int i = 0;i<64;i++){
   snakeX[i]=-1;
   snakeY[i]=-1;
  }
  
   headX = 4;
   headY = 4;
  
   snakeLength = 1;
  
   snakeX[0]=4;
   snakeY[0]=4;
   
   generateEgg();
   
   updateMaze();
   draw(); 

 }
 
void updategameSpeed(){
// 
 val = analogRead(potPin); // read the voltage on the pot (val ranges from 0 to 1023)
 gameSpeed = map(val,0,1023,100,2000); // percent will range from 100 to 2000. 
  
}
 
void draw(){ 
 for(int i = 0;i<8;i++){
  red   = B00000000;
  green = B00000000; 
  row   = B00000000; 
  for(int j = 0;j<8;j++){
    dot = maze[i][j];
     if(dot==0){         // Turn off (0)
        red&=(~(1<<j));
      green&=(~(1<<j)); 
     }else if(dot==1){   // Turn to Red (1)
        red|=(1<<j);
      green&=(~(1<<j));
     }else if(dot==2){   // Turn to Green (2)
        red&=(~(1<<j));
      green|=(1<<j); 
     }else{              // Turn to Orange
        red|=(1<<j);
      green|=(1<<j); 
     }
   }
   row|=(1<<i);
   shift(green, red, row);
  }
 }
 
 void shift(byte green,byte red,byte row){
      digitalWrite(latch, LOW);
      shiftOut(data, clock, MSBFIRST, ~green);
      shiftOut(data, clock, MSBFIRST, ~red); 
      shiftOut(data, clock, MSBFIRST, row);  
      digitalWrite(latch, HIGH);
      delay(shiftDelay);    
 } 
 
void printGOver(){ 
  
  int tens = score/10;
  int ones = score%10;
//  for(int i = 0;i>8;i++){
//   letters[lettersCount-3][i] = numbers[tens][i];
//   letters[lettersCount-2][i] = numbers[ones][i];  
//  }
  red   = B00000000;
  green = B00000000; 
  row   = B00000000; 
 for(int i = 0;i<lettersCount;i++){ // number of letters
  for(int j = 0;j<6;j++){ // index of current column
  if((i==4||i==9||i==14||i==20)&&j==2){
   break; 
  }
     for(int k = 0;k<8;k++){ // index of current row to change
       temp[k]<<=1;
       b= (letters[i][k] >> (8-j))&1;
       temp[k]|= b;
       shift2(green, temp[k], 1<<k);
     }
      for(int t = 0; t<letterDelay;t++){
        for(int k = 0;k<8;k++){ // index of curren row to change
           shift2(green, temp[k], 1<<k);
        }
      }
    }
   } 
   
   if(tens!=0){
//    for(int i = 0;i<lettersCount;i++){ // number of letters
  for(int j = 0;j<6;j++){ // index of current column
     for(int k = 0;k<8;k++){ // index of current row to change
       temp[k]<<=1;
       b= (numbers[tens][k] >> (8-j))&1;
       temp[k]|= b;
       shift2(green, temp[k], 1<<k);
     }
      for(int t = 0; t<letterDelay;t++){
        for(int k = 0;k<8;k++){ // index of curren row to change
           shift2(green, temp[k], 1<<k);
        }
      }
    }
}
    for(int j = 0;j<6;j++){ // index of current column
     for(int k = 0;k<8;k++){ // index of current row to change
       temp[k]<<=1;
       b= (numbers[ones][k] >> (8-j))&1;
       temp[k]|= b;
       shift2(green, temp[k], 1<<k);
     }
      for(int t = 0; t<letterDelay;t++){
        for(int k = 0;k<8;k++){ // index of curren row to change
           shift2(green, temp[k], 1<<k);
        }
      }
    }
     for(int j = 0;j<6;j++){ // index of current column
     for(int k = 0;k<8;k++){ // index of current row to change
       temp[k]<<=1;
       b= (letters[lettersCount][k] >> (8-j))&1;
       temp[k]|= b;
       shift2(green, temp[k], 1<<k);
     }
      for(int t = 0; t<letterDelay;t++){
        for(int k = 0;k<8;k++){ // index of curren row to change
           shift2(green, temp[k], 1<<k);
        }
      }
    } 
 }
 
 void shift2(byte green,byte red,byte row){
      digitalWrite(latch, LOW);
      shiftOut(data, clock, LSBFIRST, ~green);
      shiftOut(data, clock, LSBFIRST, ~red); 
      shiftOut(data, clock, MSBFIRST, row);  
      digitalWrite(latch, HIGH);
      delay(shiftDelay);    
 }
