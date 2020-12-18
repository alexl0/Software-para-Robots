// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

const int ledRojo2 = 4;
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
  int p1=map(analogRead(Poten1),0,1023,0,70);
  
  if(p1>=0 and p1<=20){
  	  digitalWrite(ledRojo2, LOW);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>20 and p1<=40){
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>40 and p1<=60){
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, HIGH);
  }
  else if(p1>60 and p1<=70){
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, HIGH);
  	  digitalWrite(ledAzul2, HIGH);
  }


  
}