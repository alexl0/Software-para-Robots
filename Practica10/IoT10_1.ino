// Adrián Díaz Moro          UO265431
// Raúl López Calvo          UO263918
// Alejandro León Pereira    UO258774
// Laboratorio 2-Grupo 3

#include <Ethernet.h>
#include <SPI.h>

int led = 8;

// La IP acaba en 203 porque es nuestro grupo (laboratorio 2 grupo 03)
IPAddress ip(192, 168, 61, 203);
IPAddress subnetMask(255, 255, 255, 0);
IPAddress gateWay(192, 168, 61, 13);
IPAddress serverDNS(192, 168, 50, 10);
EthernetServer server(80);
byte macAddress[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(macAddress, ip, serverDNS, gateWay, subnetMask);
  server.begin();
  Serial.println("Inicio");
  Serial.println("IP");
  Serial.println(Ethernet.localIP());
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}
void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("New petition");
    String peticion = "";
    while (client.connected())
    {
      if (client.available())
      {
        Serial.println("Working");

        char c = client.read(); //Leer petición carácter a carácter
        peticion.concat(c);      // concatenar en un string
        Serial.println(peticion);
        // Ha acabado la peticion http
        // Si contiene index responder con una web

        // la petición ha acabado '\n' y contiene la cadena "index"
        if (c == '\n' && peticion.indexOf("index") != -1)
        {
          Serial.println("Responder");
          Serial.println(peticion);

          // contiene la cadena "encender"
          if (peticion.indexOf("encender") != -1)
          {
            Serial.println("Encender Led");
            digitalWrite(led, HIGH);
          }
          else if (peticion.indexOf("apagar") != -1)
          {
            // contiene la cadena "apagar"
            Serial.println("Apagar led");
            digitalWrite(led, LOW);
          }
        }
        // Enviamos al client una respuesta HTTP
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Access-Control-Allow-Origin: *");
        client.println();
        client.println("<html>");
        client.println("<body>");
        client.println("<h1>Control de luz por internet</h1>");
        client.println("<h2><a href='index.html?p=encender'>Encender</a></h2>");
        client.println("<h2><a href='index.html?p=apagar'>Apagar</a></h2>");
        client.println("</body>");
        client.println("</html>");

        break;
      }
    }
    delay(2000);
    client.stop();
  }
}
