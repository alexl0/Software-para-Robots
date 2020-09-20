//Adrián Díaz Moro          UO265431
//Raúl López Calvo          UO263918
//Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

int pinForRandom = A0;

int led1 = 2;
int led2 = 3;
int led3 = 4;

int boton = 5;
int pulsado = 0;

void setup() {
  Serial.begin(9600);
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(boton, INPUT);
  
  randomSeed(analogRead(pinForRandom));
}

void loop() {

  int lectura = digitalRead(boton);
  
  if(lectura == HIGH && pulsado == 0){
    pulsado = 1;

    switch(random(3)){
      case 0:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
      break;
      case 1:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
      break;
      case 2:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
      break;
    }
    
  }
  else if(lectura == LOW){
    pulsado = 0;
  }
  
}