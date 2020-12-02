#include <Servo.h>

Servo servoIzquierdo;
Servo servoDerecho;

// Derecha
const int sensorDerechoPin = 3;
const int servoDerechoPin = 9;
// Izquierda
const int sensorIzquierdoPin = 2;
const int servoIzquierdoPin = 8;

// No detecta ninguna NEGROa:
const int BLANCO = LOW;
// Detecta NEGROa:
const int NEGRO = HIGH;

// Movimientos hacia delante
const int adelanteServoIzquierdo = 0;
const int adelanteServoDerecho = 180;

// Movimientos hacia detrás
const int atrasServoIzquierdo = 180;
const int atrasServoDerecho = 0;

// Parar el robot
const int pararServo = 90;



void setup() {
  pinMode(sensorDerechoPin, INPUT);
  servoDerecho.attach(servoDerechoPin);
  
  pinMode(sensorIzquierdoPin, INPUT);
  servoIzquierdo.attach(servoIzquierdoPin);
  
}

void loop() {
  if (getSensorIzquierda() == BLANCO && getSensorDerecha() == NEGRO) {
    girarDerecha();
  }
  else if (getSensorIzquierda() == NEGRO && getSensorDerecha() == BLANCO) {
    girarIzquierda();
  }
  else if (getSensorIzquierda() == NEGRO && getSensorDerecha() == NEGRO) {
    avanzar();
  }
  else {
    pararRobot();
  }
}

/* Hace que el robot pare */
void pararRobot() {
  servoDerecho.write(pararServo);
  servoIzquierdo.write(pararServo);
}

/* Hace que el robot gire hacía la derecha*/
void girarDerecha() {
  servoDerecho.write(pararServo);
  servoIzquierdo.write(adelanteServoIzquierdo);
}

/* Hace que el robot gire hacía la izquierda*/
void girarIzquierda() {
  servoDerecho.write(adelanteServoDerecho);
  servoIzquierdo.write(pararServo);
}

/* Hace que el robot avance hacía delante*/
void avanzar() {
  servoDerecho.write(adelanteServoDerecho);
  servoIzquierdo.write(adelanteServoIzquierdo);
}

/* Devuelve el valor del sensor derecho según si detecta el color negro (linea) o no (blanco)*/
int getSensorDerecha() {
  return digitalRead(sensorDerechoPin);
}

/* Devuelve el valor del sensor izquierdo según si detecta el color negro (linea) o no (blanco)*/
int getSensorIzquierda() {
  return digitalRead(sensorIzquierdoPin);
}
