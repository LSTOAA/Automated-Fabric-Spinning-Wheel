/**
 * @SpinWheel.ino
 *
 * Automated Spinning Wheel maker using Arduino Uno
 * @version 0.2
 * @date 21-10-2019
 * @authors A. Saikia
 * @copyright Copyright (c) 2019 LSTOAA
 *
 */

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define I2C_ADDRESS 0x3C
#define RST_PIN -1
SSD1306AsciiWire oled;



int UP_PB = 12;
int DOWN_PB = 11;
int START_PB = 10;

int rawval;
int val;
int state0 = 0;
  int state1 = 0;
  int state2 = 0;
int b=0;
#define  MOT1_STP   4       // Motor 1 step
#define  MOT1_DIR   3       // Motor 1 direction
int  MOT1_E = 8;      // Motor 1 direction

#define  MOT2_STP   6       // Motor 2 step
#define  MOT2_DIR   5       // Motor 2 direction

#define  M_RIGHT    HIGH    // set cutter motor direction
#define  M_LEFT     HIGH
int FEED_STEPS=0; 
#define  HOLDER_STEP      1070 // 12-tooth pulley 
 
   

   
//---------------------------- setup() ----------------------------------------
   
void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  //Serial.begin(9600);
#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);
  oled.clear();
  pinMode(UP_PB, INPUT_PULLUP);
  pinMode(DOWN_PB, INPUT_PULLUP);
   pinMode(START_PB, INPUT_PULLUP);
 

  pinMode( MOT1_DIR, OUTPUT );
  pinMode( MOT1_STP, OUTPUT );
pinMode( MOT1_E, OUTPUT );
  pinMode( MOT2_DIR, OUTPUT );
  pinMode( MOT2_STP, OUTPUT );
  state0 = 0;
 state1 = 0;
 state2 = 0;
  FEED_STEPS=0; 
  digitalWrite(MOT1_E,HIGH);
  
}

//---------------------------- loop() -----------------------------------------
//--- Wait for a button press and then call matching function
  
void loop() {
 
  
   staticmenu();
  
digitalWrite(MOT1_E,HIGH);
    
     if(!digitalRead(UP_PB) && state0 == 0){
     
    set_turns();
   state1 += 1;
   delay(40);
   
    oled.setCursor(55, 10);

    oled.print(state1, DEC);
     }
    if(!digitalRead(DOWN_PB) && state0 == 0){
      set_turns();
   state1 -= 1;
   delay(40);
   
    oled.setCursor(55, 10);
    
    oled.print(state1, DEC);
  
    }
  
  
   if(state0 == 0 || state0 ==3) {
     if (!digitalRead(START_PB)){
     digitalWrite(MOT1_E,LOW);
   stepA();
   state0 = 2;
   b=0;
   digitalWrite(MOT1_E,HIGH);
  }
  
   }
  
 if(state0 == 2 || state0==2){
if (!digitalRead(START_PB)){
  
  stepB();
   state0 = 3;
 }
  
 }
  
  
  
  
  
  
  
}
  
  
  
    



  
  

void staticmenu() {
  oled.set2X();
  oled.setCursor(0, 0);
  oled.println("WINDING M/C");
  oled.set1X();
  oled.setCursor(0, 13);
  oled.println("---------------------");
  //oled.display();

}

void set_turns() {
  oled.set2X();
  oled.setCursor(35, 25);
  oled.println("TURNS");
  //oled.display();
}

void coil1() {
  oled.set1X();
    oled.println();
    oled.set2X();
    oled.setCursor(30, 45);
    oled.print("COIL-1");
}

void coil2() {
  oled.set1X();
    oled.println();
    oled.set2X();
    oled.setCursor(30, 45);
    oled.print("COIL-1");
}

void coil3() {
  oled.set1X();
    oled.println();
    oled.set2X();
    oled.setCursor(30, 45);
    oled.print("COIL-1");
}





void stepA() {
  oled.clear(); 
     staticmenu();
     
  state0 = 1;
  
  for (int a = 0; a <state1; a++){
    oled.clear();
    staticmenu();
    set_turns();
     oled.set2X();
    oled.setCursor(55, 65);
    
    oled.print(b++, DEC);
  
    digitalWrite(MOT1_DIR,HIGH);
    for(int y = 0; y < 3400; y++) {
      digitalWrite(MOT1_STP,HIGH);
      delayMicroseconds(200);
      digitalWrite(MOT1_STP,LOW);
      delayMicroseconds(200);
    }
   
  }
    
    
}
  


void stepB(){

digitalWrite(MOT2_DIR,HIGH);
    for(int y = 0; y < HOLDER_STEP; y++) {
      digitalWrite(MOT2_STP,HIGH);
      delayMicroseconds(500);
      digitalWrite(MOT2_STP,LOW);
      delayMicroseconds(500);
    }
  
 
  
}
