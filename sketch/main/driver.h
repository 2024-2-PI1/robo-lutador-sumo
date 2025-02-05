# define IN1 5
# define IN2 6
# define IN3 9
# define IN4 10

# define ENA 8
# define ENB 11

void andarFrente(int velocidade);
void andarTras(int velocidade);
void rotacionar(int velocidade);
void parar();

/*
Faz o robô andar para frente com a velocidade informada
*/
void andarFrente(int esquerdo, int direito){
  analogWrite(IN1, direito);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, esquerdo);
  digitalWrite(IN4, LOW);
}
/*
Faz o robô andar para trás com a velocidade informada
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
Faz o robô parar
*/
void parar(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
}