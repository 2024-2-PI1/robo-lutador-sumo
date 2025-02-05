# define ultraEcho 4
# define ultraTrig 7

double microsecondsToCentimeters(double duration);
long lerDistancia();

/*
Função de conversão de microsegundos para centímetros
*/
double microsecondsToCentimeters(double duration) {
  return (duration / 2) / 29.1;
}

/*
Função que retorna a distância, em centimetros, do sensor ultrassonico
até o objeto mais perto do sensor.
*/
long lerDistancia() {
  digitalWrite(ultraTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(ultraTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrig, LOW);

  long duration = pulseIn(ultraEcho, HIGH);

  if (duration == 0) return;

  return microsecondsToCentimeters(duration);
} 