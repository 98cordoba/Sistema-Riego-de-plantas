//Código de programación
//Incluimos las librerías

//LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

//Neopixel
#include <Adafruit_NeoPixel.h>
const int numLed=4;
const int pin8=8;
const int brillo=100;
Adafruit_NeoPixel tira = Adafruit_NeoPixel(numLed, pin8, NEO_RGB + NEO_KHZ800);

//Servomotor
#include <Servo.h>
Servo ser;

//Motor de CC
int motor=10;

//Sensor de temperatura
int sensorTemp=0;

//Datos principales
float temp=0;
int lecturaTemp=0;
int tempMaxima=35;

//Set up mensaje
void setup()
{
  //LCD
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(0,1);
  lcd.print("Estado:");
  
  //Neopixel
  tira.begin();
  tira.setBrightness(brillo);
  
  //Servomotor
  ser.attach(9);
  
  //Motor de CC
  pinMode(motor,OUTPUT);
  Serial.begin(9600);
}

//Loop
void loop()
{
  //Sensor de temperatura
  lecturaTemp=analogRead(sensorTemp);
  float voltaje=5.0/1024*lecturaTemp;
  temp=voltaje*100-50;
  lcd.setCursor(12,0);
  lcd.print(temp);
  
  if(temp>=tempMaxima)
  {
    digitalWrite(motor,HIGH);
    analogWrite(motor,255);
    lcd.setCursor(7,1);
    lcd.print("Encendido");
    ser.write(0);
    delay(800);    
    tira.setPixelColor(0,0,0,255);
    tira.show();
    tira.setPixelColor(1,0,0,255);
    tira.show();
    tira.setPixelColor(2,255,0,0);
    tira.show();
    tira.setPixelColor(3,255,0,0);
    tira.show();
  }
  else
  {
    digitalWrite(motor,LOW);
    lcd.setCursor(7,1);
    lcd.print("Apagado");
    tira.setPixelColor(0,255,255,0);
    tira.show();
    tira.setPixelColor(1,255,255,0);
    tira.show();
    ser.write(90);
    tira.setPixelColor(2,0,255,0);
    tira.show();
    tira.setPixelColor(3,0,255,0);
    tira.show();
    delay(800);
  }
}
//Fin de código
