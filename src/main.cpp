#include <Arduino.h>
#include <Tela.h>

Tela screen;

void setup() {
  // put your setup code here, to run once:
  screen = Tela();
  screen.setDisplay();
  Serial.begin(9600);
  Serial.println("SETUP COMPLETO!");
}

void loop() {
  // put your main code here, to run repeatedly:
  screen.printSerial();
  screen.setRow(0, true);
  screen.setColumn(0, true);
  screen.setPixel(2, 2, true);
}