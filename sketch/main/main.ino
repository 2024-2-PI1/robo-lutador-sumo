#include "ultrasonico.h"
#include "linha.h"
#include "driver.h"

#define velocidade 200
#define esquerdo 600
#define direito 800

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

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  Serial.println("Pinos configurados");
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
