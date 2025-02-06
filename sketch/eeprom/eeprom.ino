#include <EEPROM.h>

const int eepromLinhaId = 0;
int eepromLinha;

void setup() {
  EEPROM.begin();
  Serial.begin(9600);

  EEPROM.get(eepromLinhaId, eepromLinha);

  Serial.print("Quantidade de vezes que a linha foi detectada: ");
  Serial.println(eepromLinha);
}

void loop() {}
