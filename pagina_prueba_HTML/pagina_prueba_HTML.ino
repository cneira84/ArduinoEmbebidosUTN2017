#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
int lecturaTemperatura = 25, lecturaHumedad=38, lecturaLumens=100;


void setup()
  {Serial.begin(9600);
   BT1.begin(9600);
   }



void loop() 
{ while (BT1.available() >0 )
  {char c = BT1.read();
  if (c == 71) 
  {Serial.println("peticion web enviada");
   delay(500);
   servidor();
     }
 }
 
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

void servidor(void) 
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
