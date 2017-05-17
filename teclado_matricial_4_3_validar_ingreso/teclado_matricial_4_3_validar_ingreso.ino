const byte Filas = 4; //constante para filas
const byte Cols = 3; //constante para columnas
const byte LargoPass = 6;

byte PinsFilas[] = {24, 26, 28, 30}; //Nros de pins de filas
byte PinsCols[] = {39, 41, 43}; //Nros de pins de columnas

byte i=0, NroFila=0, NroCol = 0, estado = 0, j=0;

char StringIngreso [LargoPass] = {"","","","","",""}; //definir el string de ingreso

char Teclas [ Filas ][ Cols ] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
     };

void setup() {
  Serial.begin(9600) ;  //Defino la salida para ver el output
  for (i=0; i < Filas;i++){ //Defino los pines de filas como entrada
    pinMode(PinsFilas[i], INPUT);
  }
  for (i=0; i < Cols;i++){ //Defino los pines de columnas como salida
    pinMode(PinsCols[i], OUTPUT);
  }
}

void loop() {
  estado = 0; 
  NroFila = 255;
  NroCol = 255;//Coloco un valor limite para detectar cuando no hay teclas presionadas
  for (i=0; i < Cols;i++){ //Inicializo las columnas
    digitalWrite(Pins_Cols[i], HIGH);
  }
  for (i=0; i < Cols;i++){
    digitalWrite(Pins_Cols[i], LOW); //Seteo el indice verificador
    for (j=0; j < Filas;j++){ //Recorro las filas buscando 
      estado = digitalRead(Pins_Filas[j]);
      if (estado == 0){ //Si esta en contacto guardo el nro de columna y fila
        NroCol=i;
        NroFila=j;
        }
      delay(10);
      }
    digitalWrite(PinsCols[i],HIGH); //Vuelvo a estado 0 la columna
  }
  if (NroFila != 255 && NroCol != 255){ //Verifico si tengo alguna tecla pulsada
   Serial.println(Teclas[NroFila][NroCol]);
    }
}
