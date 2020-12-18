// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3
const int ledVerde = 4;
const int ledRojo = 2;
const int ledNaranja = 3;

const int ledVerde2 = 5;
const int ledRojo2 = 6;
const int ledNaranja2 = 7;

void setup()
{
    Serial.begin(9600);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
    pinMode(ledNaranja, OUTPUT);
  
    pinMode(ledVerde2, OUTPUT);
    pinMode(ledRojo2, OUTPUT);
    pinMode(ledNaranja2, OUTPUT);
}

void loop()
{
  delay(2000);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo2, HIGH);
  digitalWrite(ledRojo, LOW);
  delay(8000);//verde rojo2
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledNaranja, HIGH);
  delay(4000);//ambar rojo2
  digitalWrite(ledNaranja, LOW);
  digitalWrite(ledRojo, HIGH);
  delay(4000);//rojo rojo2
  digitalWrite(ledRojo2, LOW);
  digitalWrite(ledVerde2, HIGH);
  delay(8000);//rojo verde2
  digitalWrite(ledRojo2, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledNaranja2, HIGH);
  delay(4000);//rojo ambar2
  digitalWrite(ledRojo2, HIGH);
  digitalWrite(ledNaranja2, LOW);
  delay(2000);//rojo rojo2
}