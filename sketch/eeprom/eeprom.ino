#include <EEPROM.h>

void setup() {
  EEPROM.begin();
  Serial.begin(9600);

  int8_t eepromLinha = EEPROM.read(0);
  Serial.print("Linhas detectadas: ");
  Serial.println(eepromLinha);
}

void loop() {
}
