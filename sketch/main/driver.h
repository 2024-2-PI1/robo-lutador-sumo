# define IN1 5;
# define IN2 6;
# define IN3 9;
# define IN4 10;

# define ENA 3;
# define ENB 4;

void ligarMotores(int velocidade);
/*
Liga os motores com a velocidade informada, passar
um inteiro negativo como parámetro faz o robô dar ré
*/
void ligarMotores(int velocidade) {
  if (velocidade > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (velocidade == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  } else if (velocidade < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  analogWrite(ENA, abs(velocidade));
  analogWrite(ENB, abs(velocidade));
}