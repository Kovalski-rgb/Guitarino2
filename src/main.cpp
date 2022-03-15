#include <Arduino.h>
#include <Tela.h>
#include <Shape.h>

Tela screen;
Shape shape;

void setup() {
  // put your setup code here, to run once:
  screen = Tela();
  Serial.begin(9600);
  Serial.println("SETUP COMPLETO!");
}

void loop() {
  // put your main code here, to run repeatedly:
  screen.printSerial();
  screen.setDisplay(false);
  // passa o endereço de shape como paramentro
  screen.drawShape(&shape, 3, 3);
}