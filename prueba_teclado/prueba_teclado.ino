byte estado = 0, estado1 = 0;

void setup() {
  Serial.begin(9600) ;  //Defino la salida para ver el output
    pinMode(30, INPUT);
    pinMode(41, OUTPUT);
}

void loop() {
  digitalWrite(41, LOW);
//  delay(500);
  digitalWrite(41, HIGH);
  estado=digitalRead(30);
  delay(1000);
//  Serial.println("estado"); 
  Serial.println(estado);
  //delay(100);
//  digitalWrite(26,LOW);
//  delay(500);
//  estado1=digitalRead(24);
//  Serial.println("estado1");
//  Serial.println(estado1);
  //delay(500); //DeltaT para evitar el rebote
}
