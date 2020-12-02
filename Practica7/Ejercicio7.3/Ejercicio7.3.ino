#include <Servo.h>

Servo servoIzquierdo;
Servo servoDerecho;

// Derecha
const int sensorDerechoPin = 3;
const int servoDerechoPin = 9;
// Izquierda
const int sensorIzquierdoPin = 2;
const int servoIzquierdoPin = 8;

const int BLANCO = LOW;
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

// Variables sensor ultrasonidos 
const int pinTrig = 4;
const int pinEcho = 5;

//Distancia a la que el sensor empieza a detectar si hay algun obtaculo delante (centimetros).
const long DISTANCIA_SENSOR_ULTRASONIDOS = 20;
//Milisegundos entre que el sensor hace una medición y otra.
const int DELAY_SENSOR_ULTRASONIDOS = 50;
unsigned long tiempoUltimaComprobacion;

// Variables para el tiempo al esquivar un objeto
const int TIEMPO_PARADA = 500;
const int TIEMPO_GIRAR_IZQUIERDA = 1000;
const int TIEMPO_GIRAR_DERECHA = 1000;
const int TIEMPO_AVANZAR = 500; // 


void setup() {
  pinMode(sensorDerechoPin, INPUT);
  servoDerecho.attach(servoDerechoPin);
  
  pinMode(sensorIzquierdoPin, INPUT);
  servoIzquierdo.attach(servoIzquierdoPin);

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  getDistanciaSensorUltrasonidos();
}

void loop() {
   comprobarSiHayObstaculo();
   
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

/* Hace que el robot pare*/
void pararRobot() {
  servoIzquierdo.write(pararServo);
  servoDerecho.write(pararServo);
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

/* Comprueba si hay un obtaculo delante del robot. */
void comprobarSiHayObstaculo() {
  if (millis() - tiempoUltimaComprobacion >= DELAY_SENSOR_ULTRASONIDOS) {
     tiempoUltimaComprobacion = millis();
     if (getDistanciaSensorUltrasonidos() <= DISTANCIA_SENSOR_ULTRASONIDOS) {
         esquivar();
     }
  }
}

/* Esquiva el obstáculo que tiene delante. */
void esquivar() {
  pararRobot();
  delay(TIEMPO_PARADA);
  girarIzquierda();
  delay(TIEMPO_GIRAR_IZQUIERDA);
  avanzar();
  delay(TIEMPO_AVANZAR);
  girarDerecha();
  delay(TIEMPO_GIRAR_DERECHA);

  // Mientras no encuentre línea, se mueve hacia la derecha ligeramente
  servoIzquierdo.write(60);
  servoDerecho.write(110);
  while (getSensorIzquierda() == BLANCO && getSensorDerecha() == BLANCO);
}

long getDistanciaSensorUltrasonidos() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(6);

  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(12);

  long tiempo = pulseIn(pinEcho, HIGH);

  long distancia = int(0.01716 * tiempo);
  //Serial.println("Distancia sensor ultrasonidos: " + String(distancia) + "cm");

  return distancia;
}
