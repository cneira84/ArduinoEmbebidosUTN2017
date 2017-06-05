/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/

//#define LEDFLASHER 3
#define ALARMSOUNDER 5
#define ALARMBUTTON 2     // the number of the pushbutton pin

bool ButtonState = 0, AlarmaActiva = 0;
const byte Velocidad = 200;
int TiempoAlarma = 0;
const int TiempoMaxAlarma = 60000;


// the setup function runs once when you press reset or power the board
void setup() {
  setupAlarma();
}

// the loop function runs over and over again forever
void loop() {
  if(lecturaBotonPanico() == 1){
    activaAlarma();
    }
  else{
    if(AlarmaActiva == 1 && TiempoAlarma<TiempoMaxAlarma) {
      activaAlarma(); }
   }
}

void setupAlarma(){
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ALARMSOUNDER, OUTPUT);
    pinMode(ALARMBUTTON, INPUT);
    }

bool lecturaBotonPanico(){
  ButtonState = digitalRead(ALARMBUTTON);
  return ButtonState;
  }

void activaAlarma(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  analogWrite(ALARMSOUNDER, 255);
  delay(Velocidad);
  TiempoAlarma = TiempoAlarma + (Velocidad); // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  analogWrite(ALARMSOUNDER, 255);  
  delay(Velocidad);
  TiempoAlarma = TiempoAlarma + (Velocidad);
  }
