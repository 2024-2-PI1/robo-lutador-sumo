const int buttonPin = 2; // Entrada
const int ultraEcho = 6;
const int ultraTrig = 7;
const int sensorLinhaA = 8; // Entrada
const int sensorLinhaB = 9; // Entrada

void setup() {
  Serial.begin(9600);

  pinMode(ultraEcho, INPUT);
  pinMode(ultraTrig, OUTPUT);

  pinMode(sensorLinhaA, INPUT);
  pinMode(sensorLinhaB, INPUT);

  Serial.println("Pinos configurados");
}

int LinhaAState = 1;
int LinhaBState = 1;
int ultra = 0;
long cm = 0;

void loop() {
  digitalWrite(ultraTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultraTrig, LOW);

  ultra = pulseIn(ultraEcho, HIGH);

  // Serial.println(duration);

  cm = microsecondsToCentimeters(ultra);

  Serial.print(cm);
  Serial.println(" cm");
  
  // delay(1000);
}

double microsecondsToCentimeters(double duration) {
  return duration / 29 / 2;
}
