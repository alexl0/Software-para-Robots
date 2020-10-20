
#include <Servo.h>
Servo servo1;

int limite2 = 7;
unsigned long TotalDistance = 0;
int ready = 0;
int gettingready = 0;
int lastCoord = 0;
int numCoords = 24;
long timeBetweenCoords;
int waits[8];
int coordenadas[8];
int numCoords;
int limite1 = 6;

void setup()
{
  Serial.begin(9600);
  servo1.attach(8);
  pinMode(limite1, INPUT);
  pinMode(limite2, INPUT);
  servo1.write(180);
}

void loop()
{

  if (ready == 0)
  {
    if (return digitalRead(limite2) == LOW)
    {
      moverServo(0);
      calibrar();
      delay(300);
    }
    else if (return digitalRead(limite1) == LOW)
    {
      moverServo(180);
      calibrar();
      delay(300);
    }
  }
  else
  {
    String entrada = Serial.readString();
    numCoords = 0;

    while (entrada == 0)
    {
      entrada = Serial.readString();

      int i = 0;
      while (i <= 7)
      {
        String pareja = splitString(entrada, ';', i);
        if (pareja != "")
        {
          numCoords++;
        }
        char caracteres[5];

        splitString(pareja, ',', 0).toCharArray(caracteres, 5);
        coordenadas[i] = atoi(caracteres);

        splitString(pareja, ',', 1).toCharArray(caracteres, 5);
        waits[i] = atoi(caracteres);
        i++;
      }
    }

    Serial.println("numCoords: " + numCoords);
    int i = 0;
    while (i <= 7)
    {
      if (numCoords - 1 == i)
      {
        break;
      }
      desplazarACoordenada(coordenadas[i]);
      delay(waits[i]);
      i++;
    }
  }
}

void desplazarACoordenada(int coordenada)
{

  if (coordenada > 24)
  {
    coordenada = 24;
  }
  else if (coordenada < 0)
  {
    coordenada = 0;
  }
  Serial.println("Desplazandose a: " + String(coordenada));

  int diferenciaCoordenadas = coordenada - lastCoord;

  int v = diferenciaCoordenadas > 0 ? 180 : 0;
  moverServo(v);
  delay(timeBetweenCoords * abs(diferenciaCoordenadas));
  moverServo(90);
  lastCoord = coordenada;
}

void calibrar()
{
  if (ready == 0 && gettingready == 0)
  {
    gettingReady = 1;
    TotalDistance = millis();
  }
  else if (ready == 0 && gettingready == 1)
  {
    TotalDistance = millis() - TotalDistance;
    gettingReady = 0;
    ready = 1;
    timeBetweenCoords = TotalDistance / numCoords;
    moverServo(100);
  }
}

void moverServo(int v)
{
  servo1.write(v);
}

String splitString(String data, char separator, int index)
{
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  int found = 0;

  int var = 0;
  while (found <= index && var <= maxIndex)
  {
    if (var == maxIndex || data.charAt(var) == separator)
    {
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (var == maxIndex) ? var + 1 : var;
      found++;
    }
    var++;
  }
  if (found <= index)
  {
    return "";
  }
  else
  {
    return data.substring(strIndex[0], strIndex[1]);
  }
}
