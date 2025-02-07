#include "ultrasonico.h"
#include "linha.h"
#include "driver.h"
#include "eeprom.h"


// Velocidades padrões definidos experimentalmente.
#define ROTACAO 200
#define ESQUERDO 150
#define DIREITO 150
#define DISTANCIA_LIMITE 150
#define V_MAX 255


// Variáveis de controle usadas para controlar a atuação do robô.
volatile bool linhaDetectada = false;
bool girando = false;
unsigned long ultimoTempoRotacao = 0;


// Função associada ao interrupt mapeado nos pinos conectados ao sensor infravermelho,
// garante que o robô age para se afastar da linha logo que ela é detectada.
void detectarLinha() {
  incrementaLinha();
  linhaDetectada = true;
}


// Função de inicialização do robô onde são configurados os pinos e são chamadas  
// funções para iniciar a gravação de dados.
void setup() {
  // Serial.begin(9600);
  initEEPROM();

  // Pinos do sensor ultrassónico configurados conforme o datasheet.
  pinMode(ultraEcho, INPUT);
  pinMode(ultraTrig, OUTPUT);            

  // Pinos do sensor infravermelho, configurados como Pull Up para previnir
  // oscilações indesejadas na leitura do sensor.
  pinMode(sensorLinhaA, INPUT_PULLUP);
  pinMode(sensorLinhaB, INPUT_PULLUP);

  // Pinos do driver configurados conforme o datasheet.
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  /*
  Pinos ENA e ENB do driver colocados em alto para que o controle
  da potência possa ser feito usando os pinos IN1-4, simplificando
  as funções de controle do motor.
  */
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  /*
  Interrupção associada aos pinos dos sensores infravermelhos, foram escolhidas
  esses pinos por se tratar de um elemento crítico do sistema, já que o robô não
  deve em qualquer momento sair da área delimitada pela linha.
  */
  attachInterrupt(digitalPinToInterrupt(sensorLinhaA), detectarLinha, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorLinhaB), detectarLinha, FALLING);
}



// Loop principal do sistema, define o comportamento que será tomado pelo robô  
// após a execução da rotina de setup.
void loop() {
  /*
  Caso a linha seja detectada é executada essa rotina em que o robô, anda para trás por
  700 milisegundos e depois rotaciona por 400 milisegundos, esses tempos foram escolhidos
  durante os testes realizados com o robô
  */
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

  /*
  Caso contrário o robô utiliza o sensor ultrasonico para detectar o objeto mais proximo,
  se esse objeto estiver dentro da distância limite de 150 centimetros o robô anda para
  frente com aproximadamente 70% da velocidade máxima, apenas acelerando ao máximo quando
  o objeto está a 5 centimetros ou menos do sensor. Caso não seja detectado um objeto dentro
  da distância limite o robô roda até encontrar o objeto.
  */
  } else {
    long distancia = lerDistancia();
    
    if (distancia < DISTANCIA_LIMITE) {
      distanciaMaxima(distancia);
      if (distancia <= 5) {
        unsigned long comecouEmpurrar = millis();
        andarFrente(V_MAX, V_MAX);
      } else {
        andarFrente(ESQUERDO, DIREITO);
      }
    } else {
      if (millis() - ultimoTempoRotacao >= 200) {
        ultimoTempoRotacao = millis();

        if (girando) {
          parar();
        } else {
          rotacionar(ROTACAO);
        }
        girando = !girando;
      }
    }
  }

  // Função para armazenar o tempo de execução do progama na memória 
  // EEPROM do Arduino
  int tempoExecucao = millis() / 1000;
  tempoDecorrido(tempoExecucao);

  delay(10);
}