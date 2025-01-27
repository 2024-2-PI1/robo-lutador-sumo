void ligarMotores(int velocidade);

const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;

const int ENA = 3;
const int ENB = 8;
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