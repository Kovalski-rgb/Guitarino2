#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoQueue.h>
#include "tonePlayer.h"

// ---------------------------------------------- CONSTANTS AND GLOBAL VARIABLES
#define LED_PIN 3 // for data transfer to strip

#define ROW0_IN 12
#define ROW1_IN 11
#define ROW2_IN 10
#define ROW3_IN 9
#define ROW4_IN 8

#define LED_COUNT 64

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DELAY_DROP 300

#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8
#define BOARD_WIDTH 5
#define BOARD_HEIGHT 8
#define LINE_HEIGHT 6
#define BUTTON_COUNT 5

int life;
int initialLife;
#define LIFE_LED DISPLAY_WIDTH-1

// ---------------------------------------------- STRUCTS, QUEUES AND ARRAYS

struct RGB {
    byte r;
    byte g;
    byte b;
};

/*Data to process pixels on display */
struct ScreenPixel{
  byte yPos;
  byte xPos;
  unsigned long time;
  bool offScreen;
  bool pressed;
  RGB color;
};


ArduinoQueue<ScreenPixel> pixelQueue(LED_COUNT);
ArduinoQueue<ScreenPixel> auxQueue(LED_COUNT);

bool buttonPressed[5];
byte buttons[5];
RGB lifeStates[3];

// ---------------------------------------------- FUNCTION DECLARATIONS

ScreenPixel dropPixel(ScreenPixel pixel);
void drawLine(byte height, RGB color);
void lifeUpdater();
void screenProcessor();

// ---------------------------------------------- MAIN FUNCTIONS

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(10);

  initialLife = 3;
  life = initialLife;

  lifeStates[0] = {0, 255, 0};
  lifeStates[1] = {255, 255, 0};
  lifeStates[2] = {255, 0, 0};

  strip.show();

  pinMode(ROW0_IN, INPUT);
  pinMode(ROW1_IN, INPUT);
  pinMode(ROW2_IN, INPUT);
  pinMode(ROW3_IN, INPUT);
  pinMode(ROW4_IN, INPUT);

  buttons[0] = ROW0_IN;
  buttons[1] = ROW1_IN;
  buttons[2] = ROW2_IN;
  buttons[3] = ROW3_IN;
  buttons[4] = ROW4_IN;
  buttonPressed[0] = false;
  buttonPressed[1] = false;
  buttonPressed[2] = false;
  buttonPressed[3] = false;
  buttonPressed[4] = false;

  playMelody();
}

void loop(){
  drawLine(LINE_HEIGHT, {255, 128, 64});
  
  if(pixelQueue.isEmpty()){
    pixelQueue.enqueue({0, 0, millis(), false, false, {0, 255, 0}});
    pixelQueue.enqueue({0, 1, millis(), false, false, {255, 0, 0}});
    pixelQueue.enqueue({0, 2, millis(), false, false, {0, 0, 255}});
    pixelQueue.enqueue({0, 3, millis(), false, false, {255, 255, 0}});
    pixelQueue.enqueue({0, 4, millis(), false, false, {255, 100, 0}});
  }
  
  // playMelody();
  while(!pixelQueue.isEmpty()){
    screenProcessor();
  }
  lifeUpdater();

  while(!auxQueue.isEmpty()){
    pixelQueue.enqueue(auxQueue.dequeue());
  }

}

void screenProcessor(){
  ScreenPixel pixel = pixelQueue.dequeue();

  pixel = dropPixel(pixel);

  for(int i = 0; i < BUTTON_COUNT; i++){
    if(digitalRead(buttons[i])){
      if(pixel.xPos == i){
        if((!buttonPressed[i] && pixel.yPos == LINE_HEIGHT) || pixel.yPos-1 == LINE_HEIGHT){
          pixel.pressed = true;
          if(pixel.yPos == LINE_HEIGHT){
            strip.setPixelColor((pixel.yPos*DISPLAY_WIDTH)-DISPLAY_WIDTH+pixel.xPos, 0, 0, 0);  
            life++;
          }else{
            life+=2;
          }
          strip.setPixelColor(14, pixel.color.r, pixel.color.g, pixel.color.b);
          strip.show();
        } else {
          if(!buttonPressed[i])
            life--;
        }
        buttonPressed[i] = true;
      }
    } else {
      buttonPressed[i] = false;
    }
  }

  if(!pixel.offScreen && !pixel.pressed){
    auxQueue.enqueue(pixel);
  } else {
    if(!pixel.pressed || pixel.offScreen)
      life--;
  }
}

/*
  Updates the life led on display, when with less than 2/3 of the initial life, it shifts to the second lifeState
  and at 1/3, it shifts to the third lifeState 
*/
void lifeUpdater(){
  if(life < 0)
    life = 0;
  Serial.print("Life: ");
  Serial.println(life);
  int state = 0;
  int currentPercent = (100*life)/initialLife;
  if(currentPercent < 66 && currentPercent >= 33){
    state = 1;
  } else {
    if(currentPercent < 33)
      state = 2;
  }
  strip.setPixelColor(LIFE_LED, lifeStates[state].r, lifeStates[state].g, lifeStates[state].b);
  strip.show();
}

/*
  This function makes a specified pixel "fall" from the top of the display to the bottom, and returns the same pixel with updated position values 
*/
ScreenPixel dropPixel(ScreenPixel pixelData){
  byte stripPos = (pixelData.yPos*DISPLAY_WIDTH)+pixelData.xPos;

  if(stripPos-DISPLAY_WIDTH < LED_COUNT){
    if(millis()-pixelData.time >= DELAY_DROP || pixelData.yPos == 0){

      pixelData.time = millis();

      if(stripPos >= DISPLAY_WIDTH){
        strip.setPixelColor(stripPos-DISPLAY_WIDTH, 0, 0, 0);   
      }

      RGB color = pixelData.color;
      strip.setPixelColor(stripPos, color.r, color.g, color.b);
      strip.show();

      pixelData.yPos++;
    }
    return pixelData;
  } else {
    pixelData.offScreen = true;
    strip.setPixelColor(stripPos-DISPLAY_WIDTH, 0, 0, 0);
    strip.show();
    return pixelData;
  }
}

/*
  This simply draws a line at specified height, with specified RGB color
*/
void drawLine(byte height, RGB color){
  int pos = height*DISPLAY_HEIGHT;
  for(int i = 0; i<BOARD_WIDTH; i++){
    strip.setPixelColor(pos+i, color.r, color.g, color.b);
  }
  strip.show();
}