# define IN1 5
# define IN2 6
# define IN3 9
# define IN4 10

# define ENA 8
# define ENB 11

void ligarMotores(int velocidade);
void andarFrente(int velocidade);
void andarTras(int velocidade);
void rotacionar(int velocidade);
void parar();
/*
Liga os motores com a velocidade informada, passar
um inteiro negativo como parámetro faz o robô dar ré
*/

void andarFrente(int esquerdo, int direito){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, esquerdo);
  analogWrite(ENB, direito);
}
void andarTras(int esquerdo, int direito){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
  analogWrite(ENA, esquerdo);
  analogWrite(ENB, direito);
}
void rotacionar(int velocidade){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, LOW);  
}
void parar(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
}