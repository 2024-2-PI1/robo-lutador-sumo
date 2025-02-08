#include <EEPROM.h>

// Posições na memória EEPROM em que os dados
// coletados em tempo de execução estão armazenados
const int eepromTempoId = 0;
int unsigned eepromTempo;

const int eepromLinhaId = 4;
int unsigned eepromLinha;

const int eepromDistaId = 8;
int unsigned eepromDista;


// Função que lê os dados coletados enquanto o robô estava ligado
// e imprime esses valores no terminal.
void setup() {
  Serial.begin(9600);

  EEPROM.get(eepromTempoId, eepromTempo);
  EEPROM.get(eepromLinhaId, eepromLinha);
  EEPROM.get(eepromDistaId, eepromDista);

  Serial.println();

  Serial.print("Tempo de funcionamento do robô: ");
  Serial.print(eepromTempo);
  Serial.println(" segundos");
  Serial.println();

  Serial.print("Quantidade de vezes que a linha foi detectada: ");
  Serial.print(eepromLinha);
  Serial.println(" vezes");
  Serial.println();

  Serial.print("Distância máxima detectada pelo sensor ultrasonico: ");
  Serial.print(eepromDista);
  Serial.println(" centimetros");
  Serial.println();

  EEPROM.write(13, 1);

  delay(1000);
}

void loop() {
  delay(1000);
}
