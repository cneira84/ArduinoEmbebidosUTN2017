/*  The circuit:
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
 * Sensor Humidity Temp DATA - Right PIN - Pin8
 * Sensor Humidity Temp GND - Left PIN
 * Sensor Humidity Temp - Middle PIN
 * LED - PIN 9
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// the PWM pin the LED is attached to
int led = 9;
int brightness = 255; 

//Variable Test Inicializada en 0
bool test = 0;
byte pin_llave_test = 52;

//KY015 DHT11 Temperature and humidity sensor 
int DHpin = 8;
byte dat [5];
byte read_data () {
  byte data;
  for (int i = 0; i < 8; i ++) {
    if (digitalRead (DHpin) == LOW) {
      while (digitalRead (DHpin) == LOW); // wait for 50us
      delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1'
      if (digitalRead (DHpin) == HIGH)
        data |= (1 << (7-i)); // high front and low in the post
      while (digitalRead (DHpin) == HIGH); // data '1 ', wait for the next one receiver
     }
  }
return data;
}
 
void inicializar_sensor_humidity () {
  digitalWrite (DHpin, LOW); // bus down, send start signal
  delay (30); // delay greater than 18ms, so DHT11 start signal can be detected
 
  digitalWrite (DHpin, HIGH);
  delayMicroseconds (40); // Wait for DHT11 response
 
  pinMode (DHpin, INPUT);
  while (digitalRead (DHpin) == HIGH);
  delayMicroseconds (80); // DHT11 response, pulled the bus 80us
  if (digitalRead (DHpin) == LOW);
  delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data
 
  for (int i = 0; i < 4; i ++) // receive temperature and humidity data, the parity bit is not considered
    dat[i] = read_data ();
 
  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
}

void display_header(byte columna, byte fila, String texto){
  lcd.setCursor(columna, fila);
  lcd.print(texto);
  }

void display_humidity(byte columna, byte fila){
  display_header(0,0,"Humedad:");
  lcd.setCursor(columna, fila);
  lcd.print (dat [0], DEC); // display the humidity-bit integer;
  lcd.print ('.');
  lcd.print (dat [3], DEC);
  lcd.print ('C');
}

void display_temperature(byte columna, byte fila){
  display_header(0,0,"Temperatura:");
  lcd.setCursor(columna, fila);
  lcd.print (dat [2], DEC); // display the humidity-bit integer;
  lcd.print ('.');
  lcd.print (dat [1], DEC);
  lcd.print ('%');
}

void control_serial_humidity(){
  Serial.print ("Current humdity =");
  Serial.print (dat [0], DEC); // display the humidity-bit integer;
  Serial.print ('.');
  Serial.print (dat [1], DEC); // display the humidity decimal places;
  Serial.println ('%');
  }

void control_serial_temperatura(){
  Serial.print ("Current temperature =");
  Serial.print (dat [2], DEC); // display the temperature of integer bits;
  Serial.print ('.');
  Serial.print (dat [3], DEC); // display the temperature of decimal places;
  Serial.println ('C');
  }

void display_test_mode(){
  test = digitalRead(pin_llave_test);
  if(test == 1){
    analogWrite(led, brightness);
    control_serial_humidity();
    control_serial_temperatura();
    }
  else{
    analogWrite(led, 0);
    }
  }
  
void setup_lcd(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Invernadero");
  delay(2000);
}
 
void setup () {
  Serial.begin (9600);
  pinMode (DHpin, OUTPUT);
  setup_lcd();
  pinMode(led, OUTPUT);
  pinMode(pin_llave_test, INPUT);
}
 
void loop () {
  inicializar_sensor_humidity ();
  display_test_mode();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  display_humidity(0,1);
  delay(1000); //original del sensor de 700
  display_temperature(0,1);
  delay(1000);
}
