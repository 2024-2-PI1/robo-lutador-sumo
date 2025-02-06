# include "ultrasonico.h"
# include "linha.h"
# include "driver.h"
# include "eeprom.h"

# define ROTACAO 200
# define ESQUERDO 150
# define DIREITO 150
# define DISTANCIA_LIMITE 150
# define V_MAX 255

volatile bool linhaDetectada = false;
bool girando = false;
unsigned long ultimoTempoRotacao = 0;

void detectarLinha() {
  incrementaLinha();
  linhaDetectada = true;
}

void setup() {
  Serial.begin(9600);
  initEEPROM();

  incrementaLinha();

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
    
    unsigned long tempoInicial = millis();
    while (millis() - tempoInicial < 700) { 
      andarTras(ESQUERDO, DIREITO);
    }
    
    parar();
    
    unsigned long tempoRotacao = millis();
    while (millis() - tempoRotacao < 400) {
      rotacionar(ROTACAO);
    }
    
    linhaDetectada = false;
    
  } else {
    long distancia = lerDistancia();
    
    if (distancia < DISTANCIA_LIMITE) {
      distanciaMaxima(distancia);
      if (distancia <= 5) {
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
      } else {
        andarFrente(ESQUERDO, DIREITO);
      }

    } else {

      if (millis() - ultimoTempoRotacao >= 200){ //200
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

  tempoDecorrido(millis() / 1000);
  delay(10);
}