# define sensorLinhaA 2
# define sensorLinhaB 3

bool detectaLinha();

int LinhaAState;
int LinhaBState;

/* 
Função que retorna true caso a linha esteja sendo 
detectado por um dos sensores, falso caso contrário
*/
bool detectaLinha() {
  LinhaAState = digitalRead(sensorLinhaA);
  LinhaBState = digitalRead(sensorLinhaB);

  return LinhaAState || LinhaBState;
}