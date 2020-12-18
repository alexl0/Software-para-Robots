// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

const int ledRojo2 = 3;
const int ledVerde2 = 5;
const int ledAzul2 = 6;

#define Poten1 A5

void setup()
{
    Serial.begin(9600);
  
    pinMode(ledVerde2, OUTPUT);
    pinMode(ledRojo2, OUTPUT);
    pinMode(ledAzul2, OUTPUT);
  
}

void loop()
{
  //Leer potenciometro1
  int p1=map(analogRead(Poten1),0,1023,0,255);

  if(p1==0){
    analogWrite(ledRojo2,0);
    analogWrite(ledAzul2,0);
    analogWrite(ledVerde2,0);
  } else
  if(p1>=1 and p1<=85){
    analogWrite(ledRojo2,p1*3);
    analogWrite(ledAzul2,0);
    analogWrite(ledVerde2,0);
  } else
  if(p1>=85 and p1<=170){
    analogWrite(ledRojo2,255);
    analogWrite(ledAzul2,(p1-85)*3);
    analogWrite(ledVerde2,0);
  } else
  if(p1>=170 and p1<=255){
    analogWrite(ledRojo2,255);
    analogWrite(ledAzul2,255);
    analogWrite(ledVerde2,(p1-170)*3);
  }
  
}