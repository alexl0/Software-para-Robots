// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

short pinForRandom = A0;
const short numeroDeNiveles = 5;
const short botonVerde = 4;
const short botonRojo = 5;
const short ledVerde = 2;
const short ledRojo = 3;
bool botonRojoEstado = false;
bool botonVerdeEstado = false;
const size_t tamMemoria = 3 + numeroDeNiveles;
short listaEnMemoria[tamMemoria];
short turno = 0;
short delayValorDefecto = 800;

void setup()
{
    randomSeed(analogRead(pinForRandom));
    Serial.begin(9600);

    Serial.println("######### Juego de Memoria #########");

    pinMode(botonVerde, INPUT_PULLUP);
    pinMode(botonRojo, INPUT_PULLUP);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
}

void loop()
{
    if (turno == 0)
    {
        inicializarVector(listaEnMemoria, 3);
        Serial.println("Inicializando...");
    }
    mostrarListaCorrecta();
    delay(800);
    turnoDelUsuario();
    if (turno != 0)
        memoPlay();
}

void memoPlay()
{
    listaEnMemoria[turno + 3 - 1] = random(ledVerde, ledRojo + 1);
}

void encenderLCD(short led, short delayValor)
{
    digitalWrite(led, HIGH);
    delay(delayValorDefecto);
    digitalWrite(led, LOW);
    delay(delayValorDefecto);
}

void turnoDelUsuario()
{
    short combinacionUsuario[tamMemoria];
    short vecesPulsado = 0;
    while (vecesPulsado <= turno + 2)
    {
        bool rojoPulsado = actualizarEstadoDelBoton(digitalRead(botonRojo), botonRojoEstado);

        if (actualizarEstadoDelBoton(digitalRead(botonVerde), botonVerdeEstado) != rojoPulsado)
        {
            Serial.print("Has pulsado el boton: ");
            if (rojoPulsado)
            {
                encenderLCD(ledRojo, delayValorDefecto);
                combinacionUsuario[vecesPulsado] = ledRojo;
                Serial.println("Rojo");
            }
            else
            {
                encenderLCD(ledVerde, delayValorDefecto);
                combinacionUsuario[vecesPulsado] = ledVerde;
                Serial.println("Verde");
            }

            //Se ha equivocado el usuario?
            if (listaEnMemoria[vecesPulsado] != combinacionUsuario[vecesPulsado])
            {
                Serial.println("Has perdido.");
                reiniciarJuego();

                //Salir del bucle
                break;
            }

            vecesPulsado++;
        }
    }
    comprobarHaTerminado(combinacionUsuario);
}

void comprobarHaTerminado(short combinacionUsuario[])
{
    short aciertos = 0;
    size_t jugada = 0;
    while (jugada < turno + 3)
    {
        if (listaEnMemoria[jugada] == combinacionUsuario[jugada])
        {
            aciertos++;
        }
        jugada++;
    }
    if (aciertos == turno + 3)
    {
        if (turno == numeroDeNiveles)
        {
            Serial.println("Has ganado.");
            reiniciarJuego();
        }
        else
        {
            turno++;
        }
    }
}

void reiniciarJuego()
{
    memset(listaEnMemoria, 0, sizeof(listaEnMemoria));
    turno = 0;
    botonVerdeEstado = false;
    botonRojoEstado = false;
}

void mostrarListaCorrecta()
{
    Serial.println("Secuencia (0 = Rojo y 1 = Verde): ");
    size_t jugada = 0;
    while (jugada < turno + 3)
    {
        Serial.print(listaEnMemoria[jugada] == 3 ? 0 : 1);
        encenderLCD(listaEnMemoria[jugada], delayValorDefecto);
        jugada++;
    }
    Serial.println();
}

void inicializarVector(short array[], short count)
{
    size_t jugada = 0;
    while (jugada < count)
    {
        array[jugada] = random(ledVerde, ledRojo + 1);
        jugada++;
    }
}

bool actualizarEstadoDelBoton(short botonValor, bool &botonEstado)
{
    if (botonValor == HIGH and !botonEstado)
    {
        botonEstado = true;
        return true;
    }
    if (botonValor == HIGH and botonEstado)
    {
        return false;
    }
    if (botonValor == LOW and botonEstado)
    {
        botonEstado = false;
        return false;
    }
    return false;
}
