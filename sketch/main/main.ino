# include "ultrasonico.h"
# include "linha.h"
# include "driver.h"
# include <EEPROM.h>

# define ROTACAO 100
# define ESQUERDO 150
# define DIREITO 150
# define DISTANCIA_LIMITE 150
# define V_MAX 255

volatile bool linhaDetectada = false;
bool girando = false;
unsigned long ultimoTempoRotacao = 0;
volatile uint8_t eepromLinha = 0; 

void detectarLinha() {
  linhaDetectada = true;
}

void setup() {
  EEPROM.begin();
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
  if (linhaDetectada) {

    parar();
    delay(200);

    EEPROM.write(0, ++eepromLinha);
    
    unsigned long tempoInicial = millis();
    while (millis() - tempoInicial < 700) { 
      andarTras(ESQUERDO, DIREITO);
    }
    
    parar();
    
    unsigned long tempoRotacao = millis();
    while (millis() - tempoRotacao < 600) {
      rotacionar(ROTACAO);
    }
    
    linhaDetectada = false;
    
  } else {
    
    long distancia = lerDistancia(); 

    if (distancia < DISTANCIA_LIMITE) {
      if (distancia <= 15) {
        unsigned long comecouEmpurrar = millis(); //teste
        andarFrente(V_MAX, V_MAX);

        /*while (comecouEmpurrar - millis() >= 5000) {
            andarFrente(V_MAX, V_MAX);
            while (millis() - comecouEmpurrar < 5700) {
              andarTras(ESQUERDO, DIREITO);
            }
            andarFrente(V_MAX, V_MAX);
          } */
        // teste
      }:
      else {
      andarFrente(ESQUERDO, DIREITO);
      }

    } else {
      if (millis() - ultimoTempoRotacao >= 300){ //200
        ultimoTempoRotacao = millis();

        if (girando){
          parar();
        } else {
          rotacionar(ROTACAO);
        }
        girando = !girando;
      }
    }
  }
  
  delay(10);
}