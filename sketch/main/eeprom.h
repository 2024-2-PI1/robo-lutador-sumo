#include <EEPROM.h>

/*
Inicializamos as variáveis que armazenam os dados que serão coletados durante a execução
do robô, como volatile * para garantir que caso essas variáveis mudem de forma assincrona,
quando uma interrupção for chamada, elas serão atualizados de forma certa. Também, definimos
os endereços do EEPROM em que essas informações serão armazenadas.
*/
const int eepromLinhaId = 0;
volatile int eepromLinha = 0;

/*
Função de inicialização do EEPROM, no qual todas os endereços são zerados a fim de previnir que
lixo de memória afete a coleta de dados do robô.
*/
void initEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

/*
Função que incrementa quantas vezes a linha foi detectada pelo sensor infravermelho, chamada
na seção de tratamento do interrupt gerado pela detecção da linha.
*/
void incrementaLinha() {
  EEPROM.put(eepromLinhaId, ++eepromLinha)
}