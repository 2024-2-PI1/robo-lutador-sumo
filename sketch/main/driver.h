/*/
Definição de quais pinos do arduino estão conectados a quais pinos do driver os pinos 
IN1 e IN3, especificamente, estão conectados a pinos que conseguem enviar sinais PWM 
utilizando a função analogWrite() da biblioteca padrão do Arduino.
*/
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

#define ENA 8
#define ENB 11

void andarFrente(int velocidade);
void andarTras(int velocidade);
void rotacionar(int velocidade);
void parar();

/*
Faz o robô andar para frente com a velocidade informada. A decisão de passar valores discretos
para IN1 e IN3 foi feita pois o driver aceita o controle de potência por meio de um sinal PWM,
que pode assumir valores no intervalo de 0 a 255 inclusive.
*/
void andarFrente(int esquerdo, int direito){
  analogWrite(IN1, direito);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, esquerdo);
  digitalWrite(IN4, LOW);
}

/*
Faz o robô andar para trás com a velocidade informada. A diferença em quais pinos recebem o sinal
PWM quando comparado a função andarFrente se dá pois o sentido em que o motor gira depende de quais
pinos do driver estão recebendo sinal alto ou baixo.
*/
void andarTras(int esquerdo, int direito){
  digitalWrite(IN1, LOW);
  analogWrite(IN2, direito);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, esquerdo);  
}

/*
Faz o robô rotacionar com a velocidade informada
*/
void rotacionar(int velocidade){
  digitalWrite(IN1, LOW);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, velocidade);
  digitalWrite(IN4, LOW);  
}

/*
Faz o robô parar colocando todos os pinos do driver em nível lógico baixo
*/
void parar(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
}