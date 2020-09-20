// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

short pinForRandom = A0;
const short numeroDeNiveles = 3;
const short botonVerde = 4;
const short botonRojo = 5;
const short ledVerde = 2;
const short ledRojo = 3;
const short ledAzul = 6;
const short zumbador = 11;
bool botonRojoEstado = false;
bool botonVerdeEstado = false;
const size_t tamMemoria = 3 + numeroDeNiveles;
short listaEnMemoria[tamMemoria];
short turno = 0;

void setup()
{
    randomSeed(analogRead(pinForRandom));
    Serial.begin(9600);

    Serial.println("######### Juego de Memoria #########");

    pinMode(botonVerde, INPUT_PULLUP);
    pinMode(botonRojo, INPUT_PULLUP);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
    pinMode(ledAzul, OUTPUT);

    pinMode(zumbador, OUTPUT);

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

void encenderLCD(short led, short tiempo)
{
    digitalWrite(led, HIGH);
    if (led == ledRojo)
        tone(zumbador, 300, tiempo);
    else if (led == ledVerde)
        tone(zumbador, 200, tiempo);
    else if (led == ledAzul)
        tone(zumbador, 100, tiempo);
    delay(tiempo);
    digitalWrite(led, LOW);
    delay(800);
}

void exposionDeColores(){
    for(int i=0; i<3;i++){
        short delay2=400;
        digitalWrite(ledAzul, HIGH);
        tone(zumbador, 100+i*10, delay2);
        delay(delay2);
        digitalWrite(ledAzul, LOW);
        digitalWrite(ledVerde, HIGH);
        tone(zumbador, 200+i*10, delay2);
        delay(delay2);
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        tone(zumbador, 300+i*10, delay2);
        delay(delay2);
        digitalWrite(ledRojo, LOW);
    }
      delay(1000);
}

void turnoDelUsuario()
{
    short vecesPulsado = 0;
    short combinacionUsuario[tamMemoria];
    while (vecesPulsado < turno + 3)
    {
        bool rojoPulsado = actualizarEstadoDelBoton(digitalRead(botonRojo), botonRojoEstado);
        bool verdePulsado = actualizarEstadoDelBoton(digitalRead(botonVerde), botonVerdeEstado);

        if (rojoPulsado != verdePulsado)
        {
            Serial.print("Has pulsado el boton: ");
            if (rojoPulsado)
            {
                Serial.println("Rojo");

                encenderLCD(ledRojo, 800);

                combinacionUsuario[vecesPulsado] = ledRojo;
            }
            else
            {
                Serial.println("Verde");

                encenderLCD(ledVerde, 800);

                combinacionUsuario[vecesPulsado] = ledVerde;
            }

            //Se ha equivocado el usuario?
            if (listaEnMemoria[vecesPulsado] != combinacionUsuario[vecesPulsado])
            {
                Serial.println("Has perdido.");
                encenderLCD(ledAzul, 2000);
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
            exposionDeColores();
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
        encenderLCD(listaEnMemoria[jugada], 800);
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

bool actualizarEstadoDelBoton(short btnValue, bool &btnState)
{
    if (!btnState and btnValue == HIGH)
    {
        btnState = true;
        return true;
    }
    else if (btnState and btnValue == HIGH)
    {
        return false;
    }
    else if (btnState and btnValue == LOW)
    {
        btnState = false;
        return false;
    }
    else
    {
        return false;
    }
}
