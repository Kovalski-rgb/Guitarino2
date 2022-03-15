#include <Arduino.h>
#include <Tela.h>

Tela screen;

int shape[5]{1, 1, 1, 1, 1};

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
  screen.drawShape(shape, 3, 3);
}