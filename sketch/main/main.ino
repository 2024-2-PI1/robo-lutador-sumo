#include <NewPing.h>
#include "ultrasonico.h"
#include "linha.h"
#include "driver.h"

void setup() {
  Serial.begin(9600);

  pinMode(ultraEcho, INPUT);
  pinMode(ultraTrig, OUTPUT);            

  pinMode(sensorLinhaA, INPUT);
  pinMode(sensorLinhaB, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Pinos configurados");
}

int velocidade = 100;

void loop() {
  /*
  while (!detectaLinha()) {
    int distancia = lerUltra();
    if (distancia <= 150) {
      ligarMotores(velocidade);
    }
    delay(10);
  }
  */

  ligarMotores(velocidade);

  delay(50);
}
