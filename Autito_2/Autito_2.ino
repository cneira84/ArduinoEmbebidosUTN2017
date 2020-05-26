#include "IRremote.h" //For IRControl

#define IN1_PIN 6   // PWMB
#define IN2_PIN 10  // DIRB  ---  right
#define IN4_PIN 9   // PWMA
#define IN3_PIN 5   // DIRA  ---  left

IRremote irControl(11);

//CONSTANTES INFRAROJO
const int LeftAvoidancePin = 12;
const int RightAvoidancePin = A5;
//CONSTANTES MEDICION LUZ
const int LeftLightPin = A3;
const int RightLightPin = A4;
//CONSTANTES CONTROL IR
const int up = 0x40;
const int ok = 0x15;
const int down = 0x19;
const int left = 0x7;
const int right = 0x9;

int leftAvoid, rightAvoid, LL, LR;

void setup() {
  Serial.begin(9600);
  //Inicializar L298N
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  //Inicializar pin infrared
  pinMode(LeftAvoidancePin, INPUT);
  pinMode(RightAvoidancePin, INPUT);
  pinMode(LeftLightPin, INPUT);
  pinMode(RightLightPin, INPUT);
  //Inicializo IRremote
  irControl.begin(); 
}

void loop() {
  byte keycode = 0;
  keycode = irControl.getCode();
  leftAvoid = digitalRead(LeftAvoidancePin);
  rightAvoid = digitalRead(RightAvoidancePin);
  Serial.println(keycode);
  Serial.print("LeftAvoidance:");
  Serial.print(leftAvoid);
  Serial.print("   ");
  Serial.print("RightAvoidance:");
  Serial.println(rightAvoid);
  if (keycode = irControl.getCode()) {
    if (keycode == 0x15){ //ok -- Ponerlo en auto
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, HIGH);
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, HIGH);
    }
    else if (keycode == up && leftAvoid == 1 && rightAvoid == 1){ //up
      analogWrite(IN1_PIN, 100); //right gears
      analogWrite(IN2_PIN, LOW); //right gears
      analogWrite(IN3_PIN, LOW); //left gears
      analogWrite(IN4_PIN, 100); //left gears
      delay(500);
    }
    else if (keycode == down){ //down
      analogWrite(IN1_PIN, LOW);
      analogWrite(IN2_PIN, 100);
      analogWrite(IN3_PIN, 100);
      analogWrite(IN4_PIN, LOW);
      delay(500);
    }
    else if (keycode == left && leftAvoid == 1){ //left
      analogWrite(IN1_PIN, 100);
      analogWrite(IN2_PIN, LOW);
      analogWrite(IN3_PIN, 100);
      analogWrite(IN4_PIN, LOW);
      delay(200);
    }
    else if (keycode == right && rightAvoid == 1){ //right
      analogWrite(IN1_PIN, LOW);
      analogWrite(IN2_PIN, 100);
      analogWrite(IN3_PIN, LOW);
      analogWrite(IN4_PIN, 100);
      delay(200);
    }
  }
  else {
    //Si no presiono ninguna tecla se frena
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, HIGH);
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, HIGH);
  }
}
