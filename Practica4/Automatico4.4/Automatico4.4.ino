#include <Servo.h>

Servo servo;

int limite1 = 6;
int limite2 = 7;

unsigned long dist = 0;
int ready = 0;
int gettingReady = 0;

int lastCoord = 0;
int numCoords = 24;
long timeBetweenCoords;
int coords;

int test[] = {1, -2, 10, 28, 0};

void setup()
{
  Serial.begin(9600);
  servo.attach(8);
  pinMode(limite1, INPUT);
  pinMode(limite2, INPUT);
  servo.write(180);
}

void loop()
{

  if(ready==1)
  {
    int i=0;
    while(i<=4){
      Serial.println("coords introducida: " + String(test[i]));
      desplazarAcoords(test[i]);
      delay(2000);
      i++;
    }
  }
  else{
    if (digitalRead(limite2) == LOW)
    {
      moverServo(0);
      calibrar();
      delay(300);
    }
    else if (digitalRead(limite1) == LOW)
    {
      moverServo(180);
      calibrar();
      delay(300);
    }
  }
}

void desplazarAcoords(int coords)
{

  if (coords > 24)
  {
    coords = 24;
  }
  else if (coords < 0)
  {
    coords = 0;
  }
  Serial.println("Desplazando a coords: " + String(coords));

  int diferenciacoordss = coords - lastCoord;

  int velocidad = diferenciacoordss > 0 ? 180 : 0;
  moverServo(velocidad);
  delay(timeBetweenCoords * abs(diferenciacoordss));
  moverServo(90);
  lastCoord = coords;
}

void calibrar()
{
  if (ready == 0 && gettingReady == 0)
  {
    gettingReady = 1;
    dist = millis();
  }
  else if (ready == 0 && gettingReady == 1)
  {
    dist = millis() - dist;
    gettingReady = 0;
    ready = 1;

    timeBetweenCoords = dist / numCoords;
    moverServo(90);
  }
}

void moverServo(int velocidad)
{
  servo.write(velocidad);
}
