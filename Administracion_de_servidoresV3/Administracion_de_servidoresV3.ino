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
#define DHTPIN 12
#define DHTTYPE DHT11

const int BOTON1 = 13;
const int BOTON2 = 14;
const int BOTON3 = 15;

const int LED1 = 2;
const int LED2 = 4;

// Variables
int dato1;
int dato2;
int dato3;
float t;
float TempMax = 24.0;
double Tiempo;
double VentanaTiempo=0;

// Definición de objetos
DHT dht(DHTPIN, DHTTYPE); //Objeto para manejar el DHT11

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() //Inicio de void setup ()
{
  Serial.begin(115200);
  Serial.print("Inicio");

  dht.begin();  //Iniciar comunicación con el sensor

  pinMode (BOTON1, INPUT_PULLUP);  //Configura el pin del botón como entrada
  pinMode (BOTON2, INPUT_PULLUP);
  pinMode (BOTON3, INPUT_PULLUP);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);

}// Fin de void setup

//Cuerpo del programa - Se ejecuta constantemente
void loop() // Inicio de void loop
{
  lecturaSensor();
  lecturaBotones();
  logica();
}//Fin de void loop

// Funciones del usuario

void lecturaSensor ()
{
  Tiempo = millis();
  if (Tiempo > VentanaTiempo)
  {
    t = dht.readTemperature();
    if (isnan(t))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print(t);
    Serial.println(F("°C "));
    VentanaTiempo=Tiempo+2000;
  }  
}

void lecturaBotones ()
{
  dato1 = digitalRead (BOTON1);
  dato2 = digitalRead (BOTON2);
  dato3 = digitalRead (BOTON3);  
}

void logica ()
{
  if ( !dato1 || (!dato2 && t > TempMax) || (!dato3 && t > TempMax) )
  {
    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

  if ( (dato1 && !dato2) || (dato1 && !dato3) || (dato1 && t > TempMax) )
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }  
}
