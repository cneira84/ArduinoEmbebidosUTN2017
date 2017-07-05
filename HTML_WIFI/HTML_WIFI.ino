/* 
 *  Prueba del modulo wIFI ESP8266
 *  Conexión del modulo WIFI, según la grilla
 *  {1,2}
 *  {3,4}
 *  {5,6}
 *  {7,8}
 *  1 - DIGITAL PWD 3
 *  2 -GND
 *  3 - VCC 3.3
 *  7 - VCC 3.3
 *  8 - DIGITAL PWD 2
 *  Configuración inicial
 *  AT //Valido que el modulo responda
 *  AT+CIOBAUD=9600 //Cambio la velocidad de transmisión
 *  AT+CWMODE? //Valido el modo del modulo wifi
 *  AT+CWMODE=3 //Cambio a modo 3
 *  AT+CWLAP //Busca Redes WIFI
 *  AT+CWJAP=”SSID”,”Password” //Conexión a RED WIFI
 *  
 *  El funcionamiento es:
 *  Modo Mantenimiento: Permite modificar e ingresar valores desde el puerto Serial.
 *  Modo Testing: Permite disparar actuadores
 *  Modo Normal: Muestra una página con la medición de sensores.
 */

#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
String entWIFI = "";
bool serverWeb = 0;
bool debug = 1;
bool mantenimiento = 0, testing = 0;
bool serverWiFiIniciado = 1;
int lecturaTemperatura = 25, lecturaHumedad=38, lecturaLumens=100;
int refreshHTML=500;

void setup()
  {  Serial.begin(9600);
     BT1.begin(9600);
  }

void loop()
  { if(serverWiFiIniciado == 0){
      inicioServer();
    }
    else{
      if(mantenimiento == 1){
        mantenimientoWIFI();
       }
       if(testing == 1){
        testingWIFI();
        }
      while (BT1.available() >0 && mantenimiento == 0 && testing == 0)
            {char c = BT1.read();
            if (c == 71) 
              {Serial.println("peticion web enviada");
              delay(refreshHTML);
              servidorWIFI();
              }
            }       
        }
  }

void logDebug(String texto){
  if(debug == 1){Serial.println(texto);}
  }

void validarAccionWIFI(){
     if (entWIFI.indexOf("GET /actuador1 HTTP/1.1\r") > 0){ //Busco el GET de actuador1
       if(mantenimiento == 1){Serial.println("\r\nRecibi orden de Actuador 1");}
       alertaActuadorWIFI("motor");
       delay(refreshHTML*2);
     }
 }    

void leerWIFI(){
  logDebug("En lectura WIFI");
  if (BT1.available())
         { char c = BT1.read();
           Serial.print(c);           
           parser(c);
         }
  }

void leerSerial(){
  logDebug("En lectura serial");
      if (Serial.available())
      {  char c = Serial.read();
         BT1.print(c); //Escribe al WIFI
      }
  }

void mantenimientoWIFI(){
     //logDebug("En mantenimiento WIFI");
     String B= "." ;
     if (BT1.available())
        { char c = BT1.read();
          parser(c);
      }
     if (Serial.available())
     {  char c = Serial.read();
        BT1.print(c); //Escribe al WIFI
     }
  }

void testingWIFI(){
     String B= "." ;
     if (BT1.available())
        { char c = BT1.read();
          parser(c);
      }
     if (entWIFI.indexOf("GET /actuador1 HTTP/1.1\r") > 0){ //Busco el GET de actuador1
       if(mantenimiento == 1){Serial.println("\r\nRecibi orden de Actuador 1");}
       alertaActuadorWIFI("motor");
       delay(refreshHTML*2);
     }
  }

void inicioServer(){
     String B= "." ;
     if (BT1.available())
         { char c = BT1.read() ;
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
        serverWiFiIniciado = 1;
      }
  }

void parser(char c){     
     entWIFI = entWIFI + c;
     if (c == 10){
      if(mantenimiento == 1){Serial.println(entWIFI);}
      entWIFI = "";     
     }
  }

void servidorWIFI(void) 
    { escribir("<!DOCTYPE HTML>");
      escribir("<html>");                                                  //una pagina web necesita esto <HTML> y </HTML> es el inicio y fin del documento
      escribir("<head><title>Invernadero Inteligente :D</title>");    //nombre de la pestaña que llevara la pagina
      escribir("<meta http-equiv=\"refresh\" content=\"10\"></head>");    //tiempo para refrescar la pagina web
      escribir("<body><h1> <FONT SIZE=\"10\" COLOR=\"#000066\">Mediciones Invernadero </h1>");                              //titulo del inicio de la pagina
      escribir("<p> <FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"#993333\">Temperatura: "+String(lecturaTemperatura)+"C</FONT> </p>"); //Muestro lectura de Temperatura
      escribir("<p> <FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"#993333\">Humedad: "+String(lecturaHumedad)+"%</FONT> </p>"); //Muestro lectura de Humedad
      escribir("<p> <FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"#993333\">Lumens: "+String(lecturaLumens)+"</FONT> </p>"); //Muestro lectura Lumens
      escribir("</BODY>");
      escribir("</body>");
      escribir("</html>");
       delay(1);
       BT1.println("AT+CIPCLOSE=0");
       delay(500);
    }

void alertaActuadorWIFI(String nombreActuador) 
    { escribir("<!DOCTYPE HTML>");
      escribir("<html>");                                                  //una pagina web necesita esto <HTML> y </HTML> es el inicio y fin del documento
      escribir("<head><title>Invernadero Inteligente :D</title></head>");    //nombre de la pestaña que llevara la pagina
      escribir("<body><h1> <FONT SIZE=\"10\" COLOR=\"#000066\">Comando Activado </h1>");                              //titulo del inicio de la pagina
      escribir("<p> <FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"#cc0000\">El actuador disparado fue: "+nombreActuador+"</FONT> </p>"); //Muestro actuador activado
      escribir("</BODY>");
      escribir("</body>");
      escribir("</html>");
       delay(1);
       BT1.println("AT+CIPCLOSE=0");
       delay(500);
    }

    
void escribir(String text)
{BT1.print("AT+CIPSEND=0,");  
 BT1.println(text.length());
 if (BT1.find(">"))             // Si se recibe el mensaje
 {Serial.println(text);
  BT1.println(text);            //mandamos el mensaje por el wifi 
  delay(10);
  while ( BT1.available() > 0 ) 
  {if (  BT1.find("SEND OK") )  //buscamos "ok" y luego salimos
   break; 
  }
 }
}

