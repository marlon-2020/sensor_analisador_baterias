#include <LiquidCrystal.h>
#include <Servo.h>
#define servo 13
#define bateria A0
#define pilha A1
#define batCel A2
#define ledBateria 9
#define ledPilha 8
#define ledBatCel 7
#define botao 10
Servo motor;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void abre_e_fecha_porta(){
  Serial.println("Abrindo");
  motor.write(180);
  delay(5000);
  Serial.println("Fechando");
  motor.write(0);
}

void setup() {  
  motor.attach(servo,500,2450);
  motor.write(0);
  pinMode(botao, INPUT_PULLUP);
  lcd.begin(16, 2);
  pinMode(ledBateria, OUTPUT);
  pinMode(ledPilha, OUTPUT);
  pinMode(ledBatCel, OUTPUT);
  lcd.print("Tensao em Volts");
  Serial.begin(9600);
}

void loop() {
  float lerBateria = analogRead(A0);
  float lerPilha = analogRead(A1);
  float lerBatCel = analogRead(A2);
  lerBateria = lerBateria*5/1023;
  lerPilha = lerPilha*5/1023;
  lerBatCel = lerBatCel*5/1023;
  if(lerBateria >= 4.3){
    digitalWrite(ledBateria, HIGH);
  }
  if(lerPilha >= 1.3){
    digitalWrite(ledPilha, HIGH);
  }
  if(lerBatCel >= 2.8){
    digitalWrite(ledBatCel, HIGH);
  }
  lcd.setCursor(0, 1);
  lcd.print("B");
  lcd.setCursor(1,1);
  lcd.print(float(lerBateria*2),1);
  lcd.setCursor(5, 1);
  lcd.print("P");
  lcd.setCursor(6,1);
  lcd.print(float(lerPilha),1);
  lcd.setCursor(10, 1);
  lcd.print("C");
  lcd.setCursor(11,1);
  lcd.print(float(lerBatCel),1);
  if(digitalRead(botao)==LOW && lerBateria < 4.3 ){
    abre_e_fecha_porta();
  }
  if(digitalRead(botao)==LOW && lerPilha < 1.3 ){
    abre_e_fecha_porta();
  }
  if(digitalRead(botao)==LOW && lerBatCel < 2.8 ){
    abre_e_fecha_porta();
  }
}
 