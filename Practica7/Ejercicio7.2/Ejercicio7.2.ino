#include <Servo.h>

Servo servoIzquierdo;
Servo servoDerecho;

// Derecha
const int sensorDerechoPin = 3;
const int servoDerechoPin = 9;
// Izquierda
const int sensorIzquierdoPin = 2;
const int servoIzquierdoPin = 8;

// No detecta ninguna NEGRO:
const int BLANCO = LOW;
// Detecta NEGRO:
const int NEGRO = HIGH;

// Movimientos hacia delante
const int adelanteServoIzquierdo = 0;
const int adelanteServoDerecho = 180;

// Movimientos hacia detrás
const int atrasServoIzquierdo = 180;
const int atrasServoDerecho = 0;

// Parar el robot
const int pararServo = 90;

// Avanzar hacia la derecha lentamente
const int adelanteServoIzquierdoLentamente = 20;

// Resetear valores de giro
boolean resetearValores = true;

// Tiempo que tarda en buscar en linea
int tiempoEngirarEnEspiralBuscandoLinea; 

// Variables y constantes giros
int giro;
unsigned long auxTiempoGiro;
const int GIRO_INICIAL = 10;
const int LIMITE_DE_GIRO = 40;
const int GIRO_INCREMENTAR = 5;
const int TIEMPO_INICIAL_DE_GIRO = 5000;
const int TIEMPO_INCREMENTADO_ENTRE_GIROS = 2000;

void setup() {
  pinMode(sensorDerechoPin, INPUT);
  servoDerecho.attach(servoDerechoPin);
  
  pinMode(sensorIzquierdoPin, INPUT);
  servoIzquierdo.attach(servoIzquierdoPin);
  
}

void loop() {
  if (getSensorIzquierda() == BLANCO && getSensorDerecha() == NEGRO) {
    resetearValores = true;
    girarDerecha();
  }
  else if (getSensorIzquierda() == NEGRO && getSensorDerecha() == BLANCO) {
    resetearValores = true;
    girarIzquierda();
  }
  else if (getSensorIzquierda() == NEGRO && getSensorDerecha() == NEGRO) {
    resetearValores = true;
    avanzar();
  }
  else {
    girarEnEspiralBuscandoLinea();
  }
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

/* El robot se mueve en espiral hasta que logre encontrar una linea */
void girarEnEspiralBuscandoLinea() {
  if (millis() - auxTiempoGiro > tiempoEngirarEnEspiralBuscandoLinea && giro + GIRO_INCREMENTAR <= LIMITE_DE_GIRO ) {
    auxTiempoGiro = millis();
    giro += GIRO_INCREMENTAR;
    tiempoEngirarEnEspiralBuscandoLinea += TIEMPO_INCREMENTADO_ENTRE_GIROS;
  }
  
  if (resetearValores) {
    auxTiempoGiro = millis();
    giro = GIRO_INICIAL;
    tiempoEngirarEnEspiralBuscandoLinea = TIEMPO_INICIAL_DE_GIRO;
    resetearValores = false;
  }
  
  /* Le indica al robot que avanze en espiral, en sentido antihorario. */
  girarDerechaLentamente();
}

/* Hace que el robot gire hacía la derecha lentamente*/
void girarDerechaLentamente() {
  servoIzquierdo.write(adelanteServoIzquierdoLentamente);
  servoDerecho.write(pararServo+giro);
}
