// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3
const int ledRojo = 2;
const int ledVerde = 3;

const int ledRojo2 = 4;
const int ledVerde2 = 5;

const int peatonesRojo = 6;
const int peatonesVerde = 7;
const int zumbador = 11;

const int delayGrande=12000;
const int delayMediano=6000;
const int delayPeque=3000;

void setup()
{
    Serial.begin(9600);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
  
    pinMode(ledVerde2, OUTPUT);
    pinMode(ledRojo2, OUTPUT);
  
    pinMode(peatonesRojo, OUTPUT);
    pinMode(peatonesVerde, OUTPUT);
    pinMode(zumbador, OUTPUT);
}

void loop()
{
  delay(delayPeque);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo2, HIGH);
  digitalWrite(ledRojo, LOW);
  digitalWrite(peatonesRojo, HIGH);
  digitalWrite(peatonesVerde, LOW);
  delay(delayGrande);//verde rojo2
  digitalWrite(ledRojo, HIGH);
  delay(delayMediano);//ambar rojo2
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, HIGH);
  delay(delayMediano);//rojo rojo2
  digitalWrite(ledRojo2, LOW);
  digitalWrite(ledVerde2, HIGH);
  digitalWrite(peatonesRojo, LOW);
  digitalWrite(peatonesVerde, HIGH);
  tone(zumbador, 300, delayGrande);
  delay(delayGrande);//rojo verde2
  digitalWrite(ledRojo2, HIGH);
  
  //Parpadeo peatones
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, LOW);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, HIGH);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, LOW);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, HIGH);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, LOW);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, HIGH);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, LOW);
  delay(750);
  tone(zumbador, 300, 375);
  digitalWrite(peatonesVerde, HIGH);
  delay(750);
  tone(zumbador, 300, 375);
  
  digitalWrite(ledVerde2, LOW);
  digitalWrite(peatonesRojo, HIGH);
  digitalWrite(peatonesVerde, LOW);
  delay(delayPeque);//rojo rojo2
}