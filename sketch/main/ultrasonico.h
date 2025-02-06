# define ultraEcho 4
# define ultraTrig 7

double microsecondsToCentimeters(double duration);
long lerDistancia();

/*
Função de conversão de microsegundos para centímetros.
*/
double microsecondsToCentimeters(double duration) {
  return (duration / 2) / 29.1;
}

/*
Função que retorna a distância, em centimetros, do sensor ultrassonico até o objeto 
mais perto do sensor. Esta função calcula a distância até o objeto convertendo o tempo em
que o pino ultraEcho ficou em nível lógico alto, em microsegundos, e convertendo o tempo medido
para centímetros com a função microsecondsToCentimeters. A função foi implementada dessa forma
seguindo o manual de funcionamento do componente, que após o pino ultraTrig for colocado em nível 
lógico alto manda uma onda sonara e coloca o pino ultraEcho em nível lógico alto enquanto a onda enviado
não retornar ao sensor.
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