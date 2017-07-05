/* Prueba del modulo wIFI ESP8266
Conexión del modulo WIFI, según la grilla
{1,2}
{3,4}
{5,6}
{7,8}
1 - DIGITAL PWD 3
2 -GND
3 - VCC 3.3
7 - VCC 3.3
8 - DIGITAL PWD 2

Configuración inicial
AT //Valido que el modulo responda
AT+CIOBAUD=9600 //Cambio la velocidad de transmisión
AT+CWMODE? //Valido el modo del modulo wifi
AT+CWMODE=3 //Cambio a modo 3
AT+CWLAP //Busca Redes WIFI
AT+CWJAP=”SSID”,”Password” //Conexión a RED WIFI
*/

#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
String entWIFI = "";
bool serverWeb = 0;

void setup()
  {  Serial.begin(9600);
     BT1.begin(9600);
     delay(2000);
     //BT1.println(AT+CIPMUX=1);
     //BT1.println(AT+CIPSERVER=1,80);
  }

void loop()
  {  String B= "." ;
     if (BT1.available())
         { char c = BT1.read() ;
       //    Serial.print(c);
           parser(c);
         }
     if (Serial.available())
         {  char c = Serial.read();
            BT1.print(c);
         }
     if (entWIFI.equals("WIFI GOT IP\r") && serverWeb == 0){ //Una vez obtenida la IP, levanto el webserver
        Serial.println("\r\nActivar Web Server");
        BT1.println("AT+CIPMUX=1");
        delay(1000);
        BT1.println("AT+CIPSERVER=1,80");
        delay(1000);
        BT1.println("AT+CIFSR");      
      }
    if (entWIFI.indexOf("GET /actuador1 HTTP/1.1\r") > 0){ //Busco el GET de actuador1
        Serial.println("\r\nRecibi orden de Actuador 1");
     }
   }

void parser(char c){     
     entWIFI = entWIFI + c;
     if (c == 10){
      Serial.println(entWIFI);
      entWIFI = "";     
     }
  }
