// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3
const int ledRojo = 2;
const int ledVerde = 3;
const int ledAzul = 7;

const int ledRojo2 = 4;
const int ledVerde2 = 5;
const int ledAzul2 = 6;


const int zumbador = 11;

const int delayGrande=12000;
const int delayMediano=6000;
const int delayPeque=3000;

#define Poten1 A5
#define Poten2 A4

void setup()
{
    Serial.begin(9600);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
    pinMode(ledAzul, OUTPUT);
  
    pinMode(ledVerde2, OUTPUT);
    pinMode(ledRojo2, OUTPUT);
    pinMode(ledAzul2, OUTPUT);
  
    pinMode(zumbador, OUTPUT);
}

void loop()
{
  //Leer potenciometro1
  int p1=map(analogRead(Poten1),0,1023,0,70);
  //Leer potenciometro2
  int p2=map(analogRead(Poten2),0,1023,0,70);
  
  if(p1>=0 and p1<=10){
  	  digitalWrite(ledRojo, HIGH);
  	  digitalWrite(ledVerde, LOW);
  	  digitalWrite(ledAzul, LOW);
  	  digitalWrite(ledRojo2, LOW);
  	  digitalWrite(ledVerde2, HIGH);
  	  digitalWrite(ledAzul2, HIGH);
  }
  else if(p1>10 and p1<=20){
  	  digitalWrite(ledRojo, LOW);
  	  digitalWrite(ledVerde, HIGH);
  	  digitalWrite(ledAzul, LOW);
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, HIGH);
  }
  else if(p1>20 and p1<=30){
  	  digitalWrite(ledRojo, LOW);
  	  digitalWrite(ledVerde, LOW);
  	  digitalWrite(ledAzul, HIGH);
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, HIGH);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>30 and p1<=40){
  	  digitalWrite(ledRojo, HIGH);
  	  digitalWrite(ledVerde, HIGH);
  	  digitalWrite(ledAzul, LOW);
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, HIGH);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>40 and p1<=50){
  	  digitalWrite(ledRojo, HIGH);
  	  digitalWrite(ledVerde, LOW);
  	  digitalWrite(ledAzul, HIGH);
  	  digitalWrite(ledRojo2, LOW);
  	  digitalWrite(ledVerde2, HIGH);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>50 and p1<=60){
  	  digitalWrite(ledRojo, LOW);
  	  digitalWrite(ledVerde, HIGH);
  	  digitalWrite(ledAzul, HIGH);
  	  digitalWrite(ledRojo2, HIGH);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, LOW);
  }
  else if(p1>60 and p1<=70){
  	  digitalWrite(ledRojo, HIGH);
  	  digitalWrite(ledVerde, HIGH);
  	  digitalWrite(ledAzul, HIGH);
  	  digitalWrite(ledRojo2, LOW);
  	  digitalWrite(ledVerde2, LOW);
  	  digitalWrite(ledAzul2, LOW);
  }
delay(10);
  tone(zumbador, p2*5);
  
}