bool detectaLinha();

const int sensorLinhaA = 8;
const int sensorLinhaB = 9;

int LinhaAState = 1;
int LinhaBState = 1;

/* 
Função que retorna true caso a linha esteja sendo 
detectado por um dos sensores, falso caso contrário
*/
bool detectaLinha() {
  LinhaAState = digitalRead(sensorLinhaA);
  LinhaBState = digitalRead(sensorLinhaB);

  return !(LinhaAState && LinhaBState);
}