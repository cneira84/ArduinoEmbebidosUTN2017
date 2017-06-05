//----Ingreso con *xxxx#
//----Ingreso con **xy#* (x nro de zona, y nro de entrada)
//----Ingreso con *0000# (activa cambio de pass)
const byte Filas = 4; //constante para filas
const byte Cols = 3; //constante para columnas
const byte LargoPass = 6;

byte PinsFilas[] = {24, 26, 28, 30}; //Nros de pins de filas
byte PinsCols[] = {39, 41, 43}; //Nros de pins de columnas

byte i=0, NroFila=0, NroCol = 0, PosPass = 0, Estado = 0, j=0, CambiarPass = 0, OpcionValida=0, Testing = 1;
int Zona=0, Entrada=0;

char StringIngreso [LargoPass+1]; //definir el string de ingreso
char Password [LargoPass+1] = {'*','1','2','3','4','#'}; //definir password default
char StringCambioPass [LargoPass+1] = {'*','0','0','0','0','#'}; //definir password default
char StringTesting [LargoPass+1] = {'#','*','*','*','*','#'}; //definir string para modo testing

char Teclas [ Filas ][ Cols ] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
     };

void setup() {
  Serial.begin(9600) ;  //Defino la salida para ver el output
  setupTeclado();
}

void loop() {
  inicializoTeclado();
  lecturaTeclado();
  if (CambiarPass == 1){
  cambioPass();}
  if (CambiarPass == 0){
    if (PosPass >= LargoPass){
        validaTesting();
        validaCambioPass();
        validaCambioZona();
        validaPassword();}
        if (CambiarPass == 0 && OpcionValida == 0){
        displayAlert("Opción no válida");}
        PosPass = 0;
      }
}


void setupTeclado(){
  for (i=0; i < Filas;i++){ //Defino los pines de filas como entrada
    pinMode(PinsFilas[i], INPUT);
  }
  for (i=0; i < Cols;i++){ //Defino los pines de columnas como salida
    pinMode(PinsCols[i], OUTPUT);
  }
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
    displayAlert("StringIngreso");
    displayAlert(StringIngreso);
  }
}

void cambioPass(){
  if (PosPass = (LargoPass-2)){
        for(i=0; i<PosPass; i++){
          Password[i+1] = StringIngreso[i];
        }
        if (strcmp(Password, StringCambioPass) == 1){  
          displayAlert("Nueva Password");
          displayAlert(Password);
          CambiarPass = 0;
          PosPass=0;
        }
        else
        {
         displayAlert("Contraseña no permitida. Ingresela nuevamente");
         PosPass=0;
        }
  }
  else{
  PosPass= PosPass+1;}
}

void validaCambioPass(){
  if (strcmp(StringIngreso, StringCambioPass) == 0){
              displayAlert("Cambiar password");
              displayAlert(StringIngreso);
              CambiarPass = 1;
          }
}

void validaCambioZona(){
  if (StringIngreso[0] == '*' && StringIngreso[1] == '#' && StringIngreso[4] == '#' && StringIngreso[5] == '*'){
    OpcionValida = 1;
    displayAlert("Asignando Zona");            
    Zona = int(StringIngreso[2]);
    displayAlert("Zona: ");
    displayAlert(String(Zona));
    Entrada = int(StringIngreso[3]);
    displayAlert("Entrada: ");
    displayAlert(String(Entrada));
  }
}

void validaPassword(){
  if (StringIngreso[0] == '*' && StringIngreso[5] == '#'){
    OpcionValida = 1;
    displayAlert("Validando Password");
    displayAlert(Password);
    displayAlert(StringIngreso);
    if (strcmp (Password, StringIngreso) == 0){
      displayAlert("Password OK" + StringIngreso[LargoPass]);
    }
    else{
      displayAlert("Password Incorrecta" + StringIngreso[LargoPass]);}
  }
}

void validaTesting(){
  if (strcmp(StringIngreso, StringTesting) == 0){
    OpcionValida = 1;
    if (Testing == 1){
      Testing = 0;
      displayAlert("Mode: Test OFF");}
    else{
      Testing = 1;
      displayAlert("Mode: Test ON");}
  }
}

void displayAlert(String mensaje){
  Serial.println(mensaje);
}
