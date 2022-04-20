/*
 * Encender un led y leer un botón
 * Por: Alexander Arroyo
 * Fecha: 18 de abril de 2022 32 ºC
 * 
 * Este programa prende un led cuando se presiona un botón * 
 */

// Bibliotecas

// Constantes
const int BOTON = 2;
const int LED = 4;

// Variables
bool dato;

// Definición de objetos

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() //Inicio de void setup ()
{ 
  // Aquí va tu código
  pinMode (BOTON, INPUT_PULLUP);  //Configura el pin del botón como entrada
  pinMode (LED, OUTPUT);          //Configura el pin del led como salida de voltaje
  digitalWrite (LED, LOW);        //Empieza con el led apagado (1, true, HIGH; 0, false, LOW)
  Serial.begin (115200);

}// Fin de void setup

//Cuerpo del programa - Se ejecuta constantemente
void loop() // Inicio de void loop
{
  dato = digitalRead (BOTON); //Leer el pin del botón
  digitalWrite(LED, !dato);   //Prender o apagar el led
//  if (dato)
//  {
//    Serial.println("Encendido");    
//  }
//  else
//  {
//    Serial.println("Apagado");    
//  }
//  
//  delay(50);

}//Fin de void loop

// Funciones del usuario
