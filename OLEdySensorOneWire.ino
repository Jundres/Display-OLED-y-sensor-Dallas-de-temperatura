//Dsiplay OLED + Sensor Dallas
//Librerias OLED
#include <Wire.h>//Comunicacion I2C
#include <Adafruit_GFX.h>//Libreria GFX
#include <Adafruit_SSD1306.h>//Libreria SSD1306
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Librerias sensor Dallas
#include<OneWire.h> //Libreria One Wire
#include<DallasTemperature.h> //Libreria del sensor
#define sensor 2 //Pin donde se conectara el sensor
OneWire ourWire(sensor); // Configuracion de sensor
DallasTemperature sensors(&ourWire); // Configuracion de sensor

//Control de tiempo
int periodo = 1000;
unsigned long tiempoanterior = 0;
//Variable control temperatura
float tmp;

//Codigo facil para pantalla OLED y sensor de temperatura dalas v1.0
//Hecho para nimo2.blospot
//Por ANR Estudiante de ingenieria en sistemas electronicos industriales
//17/11/2018
//"Homo sum, humani nihil a me alienum puto"
//"Nada humano me es ajeno"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin(); //Iniciamos el sensor de temperatura
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//Inicio y direccion hexadecimal del OLED
  display.clearDisplay(); //Limpia el buffer del display
}

void loop() {
  // put your main code here, to run repeatedly:
   if(millis()-tiempoanterior >= periodo){
   sensorDallas(); //Mandamos llamar la funcion del sensor
   displayOLED(); //Mandamos llamar la funcion del display
   tiempoanterior = millis();
  }
}

void sensorDallas(){
    sensors.requestTemperatures();
   //Funcion para imprimir los datos 0 para Celcious, 1 para Farenheit
   tmp = sensors.getTempCByIndex(0);
   Serial.println(tmp);
}

void displayOLED(){
  display.clearDisplay();//Limpiamos el buffer de nuevo
  display.setTextColor(WHITE);//Color del texto
  display.setCursor(0,0);//Posicion del texto
  display.setTextSize(2);//Tamaño del texto
  display.print("CPU:"); //Texto en pantalla
  display.setCursor(45,0);//Posicion del texto
  display.setTextSize(2);//Tamaño del texto
  display.print(tmp); //Texto en pantalla
  display.setCursor(108,0);//Posicion del texto
  display.setTextSize(1);//Tamaño del texto
  display.print("o");
  display.setCursor(115,0);//Posicion del texto
  display.setTextSize(2);//Tamaño del texto
  display.print("C");
  //Control de temperatura para mandar ciertos mensajes al display
    if(tmp >= 0.0 && tmp <= 25.0){
      display.setCursor(0,20);//Posicion del texto
      display.setTextSize(1);//Tamaño del texto
      display.print("TEMPERATURA SIN CARGA DE TREBAJO");
    }
    else if(tmp > 25.0 && tmp <= 47.0){
      display.setCursor(0,20);//Posicion del texto
      display.setTextSize(1);//Tamaño del texto
      display.print("TEMPERATURA EN REPOSO");
    }
    else if(tmp > 47.0 && tmp <= 72.0){
      display.setCursor(0,20);//Posicion del texto
      display.setTextSize(1);//Tamaño del texto
      display.print("TEMPERATURA NORMAL");
    }
    else{
      display.setCursor(0,20);//Posicion del texto
      display.setTextSize(1);//Tamaño del texto
      display.print("CPU EN PELIGRO"); //Texto en pantallatexto
    }
  display.display();//Actualizar informacion en el display
}

//Codigo facil para pantalla OLED y sensor de temperatura dalas v1.0
//Hecho para nimo2.blospot
//Por ANR Estudiante de ingenieria en sistemas electronicos industriales
//17/11/2018
//"Homo sum, humani nihil a me alienum puto"
//"Nada humano me es ajeno"

