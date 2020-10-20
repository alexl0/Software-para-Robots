#include <Servo.h>
#define Y_pin A4
#define X_pin A5
#define boton_pin 10

int JoystickEjeX;

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
    int v = 180;
    servo.write(v);
  }
  else if (valorX <= 600)
  {
    servo.write(90); //Parar
  }

  else
  {
    int v = 0;
    servo.write(v);
  }
}
