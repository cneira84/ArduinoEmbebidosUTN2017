/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
 
/*#####Funcionalidades########
--Acceso - Egreso - Diferido con selección delta t
---Display por pantalla del teclado
---Control con teclado
----Ingreso con *xxxx#*
---->Si coincide contraseña
---------->>Activa Inmediatamente si esta desactivada *
---------->>Desactiva con retardo de 5 segundos*
---->Si no coincide al tercer intento suena alarma*
--Zona de control (3) - habitación independiente*
---Cada grupo de entradas corresponde a una zona diferente.*
----Cambio de Pass con *0000# (solo si esta desactivada o en testing)*
----Ingreso con **xy#* (x nro de zona, y nro de entrada)*
----Modo Testing #****#*
--Botón de pánico
----Al presionarlo que suene la alarma*
--Alarma
---Apagado al minuto.*
---Espera 10 minutos y arranca de nuevo.
----Sonoridad -- campana | sirena*
----Visual oscilante*
--Historial de eventos ???
--Codigo de Errores ???
--Modo de operación Test y Normal ???
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//#define LEDFLASHER 3
#define ALARMSOUNDER 5
#define ALARMBUTTON 2     // the number of the pushbutton pin

const byte Filas = 4; //constante para filas
const byte Cols = 3; //constante para columnas
const byte LargoPass = 6;
const byte Velocidad = 200;
const int TiempoMaxAlarma = 60000;
const byte CantEntradas = 6;

byte PinsFilas[] = {24, 26, 28, 30}; //Nros de pins de filas
byte PinsCols[] = {39, 41, 43}; //Nros de pins de columnas
byte Entrada1[] = {32, 1}; //Pin, zona
byte Entrada2[] = {34, 2}; //Pin, zona
byte Entrada3[] = {36, 3}; //Pin, zona
byte Entrada4[] = {38, 2}; //Pin, zona

byte i=0, NroFila=0, NroCol = 0, PosPass = 0, j=0, CambiarPass = 0, Zona=0, Entrada=0, Intentos=0;
bool Estado = 0, OpcionValida=0, Testing=1, Alarma=0, ButtonState = 0, AlarmaActiva = 0, ZonaActiva1 = 0, ZonaActiva2 = 0, ZonaActiva3 = 0, EstadoZona = 0;
int TiempoAlarma = 0;

char StringIngreso [LargoPass+1]; //definir el string de ingreso
char Password [LargoPass+1] = {'*','1','2','3','4','#'}; //definir password default
char StringCambioPass [LargoPass+1] = {'*','0','0','0','0','#'}; //definir string para cambio de pass
char StringTesting [LargoPass+1] = {'#','*','*','*','*','#'}; //definir string para modo testing

char Teclas [ Filas ][ Cols ] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
     };

byte Entradas [ CantEntradas ][ 2 ] =
    {
        {32, 1},
        {34, 2},
        {36, 3},
        {38, 2},
        {40, 1},
        {42, 1},
     };

void setup() {
  Serial.begin(9600) ;  //Defino la salida para ver el output
  setupTeclado();
  setupLcd();
  setupAlarma();
  setupZonas();
}

void loop() {
  inicializoTeclado();
  lecturaTeclado();
  lecturaZonas();
  if(lecturaBotonPanico() == 1){
    activaAlarma();
    displayAlert("Disparo Alarma", "Boton Panico");
  }
  else{
    if((AlarmaActiva == 1 && TiempoAlarma<TiempoMaxAlarma) || (Intentos > 3)) {
      activaAlarma();
      if(ZonaActiva1 == 1){displayAlert("Disparo Alarma", "Zona 1");}
      if(ZonaActiva2 == 1){displayAlert("Disparo Alarma", "Zona 2");}
      if(ZonaActiva3 == 1){displayAlert("Disparo Alarma", "Zona 3");}
    }
    if (CambiarPass == 1){
      cambioPass();}
    if (CambiarPass == 0){
      if (PosPass >= LargoPass){
          validaTesting();
          validaCambioPass();
          validaCambioZona();
          validaPassword();}
      if (CambiarPass == 0 && OpcionValida == 0){
        displayMsg("Opcion NO Valida");}
      PosPass = 0;
    }
  }
}

void setupAlarma(){
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ALARMSOUNDER, OUTPUT);
    pinMode(ALARMBUTTON, INPUT);
  }

void setupTeclado(){
  for (i=0; i < Filas;i++){ //Defino los pines de filas como entrada
    pinMode(PinsFilas[i], INPUT);
  }
  for (i=0; i < Cols;i++){ //Defino los pines de columnas como salida
    pinMode(PinsCols[i], OUTPUT);
  }
}

void setupZonas(){
  for(i=0; i<CantEntradas; i++){
    pinMode(Entradas[i][1], INPUT);
  }
}


void setupLcd(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Alarma hogareña");
}

void inicializoTeclado(){
  OpcionValida = 0;
  Estado = 0; 
  NroFila = 255;
  NroCol = 255;//Coloco un valor limite para detectar cuando no hay teclas presionadas
  for (i=0; i < Cols;i++){ //Inicializo las columnas
  digitalWrite(PinsCols[i], LOW);
  }  
}

void lecturaTeclado(){
  for (i=0; i < Cols;i++){
    digitalWrite(PinsCols[i], HIGH); //Seteo el indice verificador
    for (j=0; j < Filas;j++){ //Recorro las filas buscando 
      Estado = digitalRead(PinsFilas[j]);
      if (Estado == 1){ //Si esta en contacto guardo el nro de columna y fila
        NroCol=i;
        NroFila=j;
        }
      delay(10);
      }
    digitalWrite(PinsCols[i],LOW); //Vuelvo a estado 0 la columna
  }
  if (NroFila != 255 && NroCol != 255){ //Verifico si tengo alguna tecla pulsada
    StringIngreso[PosPass] = Teclas[NroFila][NroCol];
    if (Testing == 1){
      lcd.setCursor(0, 1);
      lcd.print(StringIngreso);}
    else {
      lcd.setCursor(0, 1);
      lcd.print('*');}
  }
}

void cambioPass(){
  if (PosPass = (LargoPass-2)){
        for(i=0; i<PosPass; i++){
          Password[i+1] = StringIngreso[i];
        }
        if (strcmp(Password, StringCambioPass) == 1){  //Validar que no sea igual a *0000#
          displayMsg("Pass modificada");
          CambiarPass = 0;
          PosPass=0;
        }
        else{
          displayMsg("Pass no permitida");
          PosPass=0;
        }
  }
  else{
  PosPass= PosPass+1;}
}

void validaCambioPass(){
  if (Alarma == 0 || Testing == 1){
    if (strcmp(StringIngreso, StringCambioPass) == 0){
      displayMsg("Nueva Pass?"); 
      CambiarPass = 1;}
  }
}

void validaCambioZona(){
  if (StringIngreso[0] == '*' && StringIngreso[1] == '#' && StringIngreso[4] == '#' && StringIngreso[5] == '*'){
    OpcionValida = 1;
    displayMsg("Zona >> ");
    Zona = int(StringIngreso[2]);
    lcd.setCursor(10, 0);
    lcd.print(char(Zona));
    displayMsg("Entrada >> ");
    Entrada = int(StringIngreso[3]);
    lcd.setCursor(12, 0);
    lcd.print(char(Entrada));
  }
}

void validaPassword(){
  if (StringIngreso[0] == '*' && StringIngreso[5] == '#'){
    OpcionValida = 1;
    if (strcmp (Password, StringIngreso) == 0){
      displayMsg("Pass OK");
      Intentos = 0;
      if (Alarma == 0){
        Alarma = 1;
        displayMsg("Alarma: ON");}
      else{
        Alarma = 0;
        displayMsg("Alarma:OFF");
        AlarmaActiva = 0;
        delay(5000);}
    }
    else{
      Intentos = Intentos + 1;
      displayMsg("Pass NO OK");
      if (Testing == 1){
        displayMsg(String(Intentos));}//Si estoy en testing muestro cantidad de intentos
    }
  }
}

void displayMsg(String mensaje){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(mensaje);
   delay(1000); //Muestro el mensaje por 3 segundos
}

void displayAlert(String mensaje1, String mensaje2){ //Dados 2 string muestro por LCD en lineas diferentes
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(mensaje1);
   lcd.setCursor(0, 1);
   lcd.print(mensaje2);
}

void validaTesting(){
  if (strcmp(StringIngreso, StringTesting) == 0){
    OpcionValida = 1;
    if (Testing == 1){
      Testing = 0;
      displayMsg("Mode: Test OFF");}
    else{
      Testing = 1;
      displayMsg("Mode: Test ON");}
  }
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

void lecturaZonas(){
  for(i=0; i<CantEntradas; i++){
    EstadoZona = digitalRead(Entradas[i][1]);
    if(EstadoZona = 1){
      if(Entradas[i][2] == 1){
          ZonaActiva1 = 1;
        }
      if(Entradas[i][2] == 2){
          ZonaActiva2 = 1;
        }
      if(Entradas[i][2] == 3){
          ZonaActiva3 = 1;
        }
      if(Alarma == 1 || Testing == 1){
        AlarmaActiva = 1;
        }
    }
  } 
}
