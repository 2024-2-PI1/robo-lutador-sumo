#include "ultrasonico.h"
#include "linha.h"
#include "driver.h"

volatile bool linhaDetectada = false;
void detectarLinha() {
  linhaDetectada = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(ultraEcho, INPUT);
  pinMode(ultraTrig, OUTPUT);            

  pinMode(sensorLinhaA, INPUT_PULLUP);
  pinMode(sensorLinhaB, INPUT_PULLUP);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  attachInterrupt(digitalPinToInterrupt(sensorLinhaA), detectarLinha, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorLinhaB), detectarLinha, FALLING);
}

void loop() {

  while (!detectaLinha()) {
    andarFrente(esquerdo, direito);
  }
  parar();
  delay(2000);
  long tempoInicial = millis(); 
  while (millis() - tempoInicial < 500) { 
    andarTras(esquerdo, direito); 
  }
  parar();
  long tempoRotacao = millis();
  while (millis() - tempoRotacao < 400){
    rotacionar(velocidade);
  }
  delay(100);
}
