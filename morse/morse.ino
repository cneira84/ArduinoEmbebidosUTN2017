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
char dataIn;
int incomingByte = 0;

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() { 
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    delay(1000);
    showMorse(incomingByte);
  } 
}

void showMorse(int caracter){
  switch(caracter){
    case (65): //a
      morseCorto();
      morseLargo();
      break;    
    case (66): //b
      morseLargo();
      morseCorto();
      morseCorto();
      morseCorto();  
      break;    
    case (67): //c
      morseLargo();
      morseCorto();
      morseLargo();
      morseCorto();  
      break;    
    case (68): //d
      morseLargo();
      morseCorto();
      morseCorto();  
      break; 
    case (69): //e
      morseCorto();  
      break; 
    case (70): //f
      morseCorto();    
      morseCorto(); 
      morseLargo();
      break; 
    case (71): //g
      morseLargo();
      morseLargo();
      morseCorto();
      break; 
    case (72): //h
      morseCorto();    
      morseCorto(); 
      morseCorto();    
      morseCorto(); 
      break; 
    case (73): //i
      morseCorto();    
      morseCorto(); 
      break; 
    case (74): //j
      morseCorto();    
      morseLargo();
      morseLargo();
      morseLargo();      
      break; 
    case (75): //k
      morseLargo();  
      morseCorto();  
      morseLargo();
      break; 
    case (76): //l
      morseCorto();  
      morseLargo();
      morseCorto();
      morseCorto();
      break; 
    case (77): //m
      morseLargo();
      morseLargo();      
      break; 
    case (78): //n
      morseLargo();
      morseCorto();
      break; 
    case (79): //o
     morseLargo();
     morseLargo();
     morseLargo();
     break; 
    case (80): //p
      morseCorto();
      morseLargo();
      morseLargo();
      morseCorto();
      break; 
    case (81): //q
      morseLargo();
      morseLargo();
      morseCorto();
      morseLargo();
      break; 
    case (82): //r
      morseCorto();
      morseLargo();
      morseCorto();
      break; 
    case (83): //s
      morseCorto();
      morseCorto();
      morseCorto();
      break; 
    case (84): //t
      morseLargo();
      break; 
    case (85): //u
      morseCorto();
      morseCorto();      
      morseLargo();
      break; 
    case (86): //v
      morseCorto();
      morseCorto();      
      morseCorto();
      morseLargo();
      break; 
    case (87): //w
      morseCorto();
      morseLargo();
      morseLargo();
      break; 
    case (88): //x
      morseLargo();
      morseCorto();
      morseCorto();
      morseLargo();
      break; 
    case (89): //y
      morseLargo();
      morseCorto();
      morseLargo();
      morseLargo();      
      break; 
    case (90): //z
      morseLargo();
      morseLargo();
      morseCorto();      
      morseCorto();
      break; 
    }
  switch(caracter){
    case (97): //a
      morseCorto();
      morseLargo();
      break;    
    case (98): //b
      morseLargo();
      morseCorto();
      morseCorto();
      morseCorto();  
      break;    
    case (99): //c
      morseLargo();
      morseCorto();
      morseLargo();
      morseCorto();  
      break;    
    case (100): //d
      morseLargo();
      morseCorto();
      morseCorto();  
      break; 
    case (101): //e
      morseCorto();  
      break; 
    case (102): //f
      morseCorto();    
      morseCorto(); 
      morseLargo();
      break; 
    case (103): //g
      morseLargo();
      morseLargo();
      morseCorto();
      break; 
    case (104): //h
      morseCorto();    
      morseCorto(); 
      morseCorto();    
      morseCorto(); 
      break; 
    case (105): //i
      morseCorto();    
      morseCorto(); 
      break; 
    case (106): //j
      morseCorto();    
      morseLargo();
      morseLargo();
      morseLargo();      
      break; 
    case (107): //k
      morseLargo();  
      morseCorto();  
      morseLargo();
      break; 
    case (108): //l
      morseCorto();  
      morseLargo();
      morseCorto();
      morseCorto();
      break; 
    case (109): //m
      morseLargo();
      morseLargo();      
      break; 
    case (110): //n
      morseLargo();
      morseCorto();
      break; 
    case (111): //o
     morseLargo();
     morseLargo();
     morseLargo();
     break; 
    case (112): //p
      morseCorto();
      morseLargo();
      morseLargo();
      morseCorto();
      break; 
    case (113): //q
      morseLargo();
      morseLargo();
      morseCorto();
      morseLargo();
      break; 
    case (114): //r
      morseCorto();
      morseLargo();
      morseCorto();
      break; 
    case (115): //s
      morseCorto();
      morseCorto();
      morseCorto();
      break; 
    case (116): //t
      morseLargo();
      break; 
    case (117): //u
      morseCorto();
      morseCorto();      
      morseLargo();
      break; 
    case (118): //v
      morseCorto();
      morseCorto();      
      morseCorto();
      morseLargo();
      break; 
    case (119): //w
      morseCorto();
      morseLargo();
      morseLargo();
      break; 
    case (120): //x
      morseLargo();
      morseCorto();
      morseCorto();
      morseLargo();
      break; 
    case (121): //y
      morseLargo();
      morseCorto();
      morseLargo();
      morseLargo();      
      break; 
    case (122): //z
      morseLargo();
      morseLargo();
      morseCorto();      
      morseCorto();
      break; 
    }
  }

void morseCorto(){
  digitalWrite(LED_BUILTIN, LOW);                        
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);                        
  }

void morseLargo(){
  digitalWrite(LED_BUILTIN, LOW);                        
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);                          
  }
