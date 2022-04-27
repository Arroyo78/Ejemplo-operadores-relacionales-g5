/*
   Administración de servidores
   Por: Alexander Arroyo
   Fecha: 27 de abril de 2022

   Características
  +Sensor de temperatura y humedad
  +Boton1: Manual. Activa la refrigeración al ser presionado
  +Boton2: Alta demanda
  +Boton3: Sobre carga de funcionamiento
  +
  +Led1: Refrigeracion manual
  +Led2: Refrigeración automática
  +
  +Que se encienda la refrigeracion manual cada que se presione el boton de manual
  +
  +La refrigeracion manual tiene prioridad a la refrigeracion automática.
  +
  +Si la termperatura es alta (mayor a 28, por ejemplo), se activa la refrigeracion automática
  +
  +Si tengo alta demanda o sobre carga, se activa la refrigeración automática
  +
  +Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones
  +
  +Botones 14, 15, 13
  +Leds 4, 2
  +DHT11 12

*/

// Bibliotecas
#include "DHT.h"  //Biblioteca del DTH11

// Constantes para manejar el DHT11
#define DHTPIN 12         //La señal del DHT11 se conecta al pin 12 del ESP32 CAM
#define DHTTYPE DHT11

const int BOTON1 = 13;    //Pines del ESP32 CAM donde se conectará cada uno de los pulsadores que se utilziarán.
const int BOTON2 = 14;
const int BOTON3 = 15;

const int LED1 = 2;       //Pines del ESP32 CAM donde se conectará cada uno de los LED's que se utilziarán.
const int LED2 = 4;

// Variables
int dato1;                //Variable donde se guardará el estado de cada uno de los pulsadores.
int dato2;
int dato3;
float t;                  //Variable donde se guardará el valor de la tempatura que se lee cada 2 segundos.
float TempMax = 24.0;     //Variable que se emplea para establecer la temperatura de referencia.
double Tiempo;            //Variable dodne se guardará el tiempo leído del tiempo en cada ciclo.
double VentanaTiempo=0;   //Variable que se emplea para establecer la ventana de tiempo de 2 segundos en cada ciclo.

// Definición de objetos
DHT dht(DHTPIN, DHTTYPE); //Objeto para manejar el DHT11

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() //Inicio de void setup ()
{
  Serial.begin(115200);   //Se establece la velocidad de comunicación entre el ESP32 CAM y la computadora.
  Serial.print("Inicio");

  dht.begin();  //Iniciar comunicación con el sensor

  pinMode (BOTON1, INPUT_PULLUP);  //Configura el pin del botón como entrada
  pinMode (BOTON2, INPUT_PULLUP);
  pinMode (BOTON3, INPUT_PULLUP);
  pinMode (LED1, OUTPUT);          //Configura los LEDś como salida
  pinMode (LED2, OUTPUT);

}// Fin de void setup

//Cuerpo del programa - Se ejecuta constantemente
void loop() // Inicio de void loop
 {
  Tiempo = millis();              // Con esta instrucción se guarda un valor, el cual se incrementa cada milisegundo, en la variable Tiempo.
  if (Tiempo > VentanaTiempo)     // Se crea una condición donde se pregunta si ya ha pasado un intervalo de tiempo, en este ejemplo 2 segundos (ver línea 88 de este código). 
  {
    t = dht.readTemperature();    // Se obtiene el valor de la temperatura desde el sensor DHT11 y se guarda en la variable "t".
    if (isnan(t))                 // Se condiciona el valor de la variable "t", si no es un número nos envía un mensaje de error.
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print(t);              //Se imprime el valor de la temperatura que se ha leído.
    Serial.println(F("°C "));
    
    VentanaTiempo=Tiempo+2000;    // Se crea la ventana de tiempo de una forma sencilla, al tiempo leído se le suman 2000 milisegundos.
  }


  dato1 = digitalRead (BOTON1);   //Con esta función se lee el valor booleano de cada uno de los botones y se guarda en cada variable el estado que presentan dichos botones.
  dato2 = digitalRead (BOTON2);
  dato3 = digitalRead (BOTON3);

  if ( !dato1 || (!dato2 && t > TempMax) || (!dato3 && t > TempMax) )   //En este apartado se estable la función booleana que se ha obtenido para controlar el LED 1.
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

  if ( (dato1 && !dato2) || (dato1 && !dato3) || (dato1 && t > TempMax) )   //En este apartado se estable la función booleana que se ha obtenido para controlar el LED 2.
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }

}//Fin de void loop

// Funciones del usuario
