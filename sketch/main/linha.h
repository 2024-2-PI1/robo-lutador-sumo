/*
A decisão de quais pinos os sensores de linha seriam conectados foi estratégica,
pois, no Arduino Uno R3, apenas os pinos 2 e 3 podem ser utilizados para mandar interrupções,
caractéristica essencial para que o robô pare imediatamente quando detectar a linha.
*/
#define sensorLinhaA 2
#define sensorLinhaB 3

/*
O nível lógico enviado pelos sensores quando não detectam algo é 1(HIGH), portanto
inicializamos as variáveis como 1 para que o robô não execute a rotina de tratamento de 
interrupção logo que é ligado.
*/
int LinhaAState = 1;
int LinhaBState = 1;

/* 
Função que retorna true caso a linha não esteja sendo detectado por um dos sensores, 
true caso contrário. A decisão de qual nível lógico é enviado pela função se justifica
pela ativação da função interrupt associada aos sensores quando é detectada uma borda 
de descida na forma de onda.
*/
bool detectaLinha() {
  LinhaAState = digitalRead(sensorLinhaA);
  LinhaBState = digitalRead(sensorLinhaB);

  return LinhaAState || LinhaBState;
}