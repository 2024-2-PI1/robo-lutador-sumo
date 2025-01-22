#include <NewPing.h>

// const int buttonPin = 2;
// const int ultraEcho = 6;
// const int ultraTrig = 7;

const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

const int ENB = 6;
const int ENA = 9;

// const int sensorLinhaA = 8; // Entrada
// const int sensorLinhaB = 9; // Entrada

// const int maxDistance = 200;

/*
NewPing sonar(ultraTrig, ultraEcho, maxDistance);

double microsecondsToCentimeters(double duration) {
  return (duration / 2) / 29.1;
}

long readUltra() {
  digitalWrite(ultraTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(ultraTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrig, LOW);

  long duration = pulseIn(ultraEcho, HIGH);
  long cm = microsecondsToCentimeters(duration);

  return cm;
} 
*/

void setup() {
  // Serial.begin(9600);

//  pinMode(ultraEcho, INPUT);
//  pinMode(ultraTrig, OUTPUT);

//  pinMode(sensorLinhaA, INPUT);
//  pinMode(sensorLinhaB, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Serial.println("Pinos configurados");
}

int LinhaAState = 1;
int LinhaBState = 1;
int velocidade = 100;

void loop() {
  // Ultrasom
  // long cm = readUltra();

  // delay(50);

  // unsigned int cm = sonar.ping_cm();

  // Serial.println(cm + " cm");
  // delay(1000);

  // Driver
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

  delay(50);
}
