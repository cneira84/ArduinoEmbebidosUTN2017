const byte CantEntradas = 6;

byte i=0, Testing = 1, Alarma =0, AlarmaActiva =0;
byte ZonaActiva1 = 0, ZonaActiva2 = 0, ZonaActiva3 = 0, EstadoZona =0;

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
  setupZonas();

}

void loop() {
  lecturaZonas();
}

void setupZonas(){
  for(i=0; i<CantEntradas; i++){
    pinMode(Entradas[i][1], INPUT);
  }
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


