#include <Servo.h>
#define Y_pin A4
#define X_pin A5
#define boton_pin 10

int valorX;
Servo servo;

void setup()
{
  pinMode(boton_pin, INPUT_PULLUP);
  Serial.begin(9600);
  servo.attach(4);
}

void loop()
{

  int valorX = analogRead(X_pin);

  if (valorX < 400)
  {
    int v = 110;
    if (valorX < 75)
    {
      v = 190;
    }
    Serial.println(v);
    servo.write(v);
  }
  else if (valorX <= 600)
  {
    servo.write(90);
  }
  else
  {
    int v = 80;
    if (valorX > 950)
    {
      v = 0;
    }
    Serial.println(v);
    servo.write(v);
  }
}
