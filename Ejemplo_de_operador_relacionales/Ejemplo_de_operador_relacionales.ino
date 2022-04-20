/*
 * Ejemplo de operador relacionales
 * Por: Alexander Arroyo
 * Fecha: 13 de abril de 2022
 * 
 * Este es un programa para ejemplificar el uso básico del lenguaje C
 * y el microcontrolador ESP32CAM
 * 
 */

// Bibliotecas
//#include <Serial.h>;

// Constantes

// Variables
int dato = 0;
double timeStart, timeFinish;

// Definición de objetos

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() { //Inicio de void setup ()
  // Aquí va tu código
  Serial.begin(115200); //Inizialización del monitor serial
  Serial.println("Conexión iniciada");  //Mensaje de prueba
  delay (1000);

}// Fin de void setup

//Cuerpo del programa - Se ejecuta constantemente
void loop() // Inicio de void loop
{
  timeStart = micros();

  //Ejecutar ciclos n veces
  for (int i = 0; i < 10000; i++)
  {
    dato++;
    //dato = dato + 1;

    //Contador de anillo con comparación
    if (dato > 8)
    {
      dato = 0;    
    }
  }
  
  timeFinish = micros();

  Serial.println("Con comparaciones: ");
  Serial.println(timeFinish - timeStart);
  delay(10000);


  timeStart = micros();

  //Ejecutar ciclos n veces
  for (int i = 0; i < 10000; i++)
  {
    dato++;
    //dato = dato + 1;

    //Contador de anillo con comparación
    dato %= 8;
  }
  
  timeFinish = micros();

  Serial.println("Con operadores: ");
  Serial.println(timeFinish - timeStart);
  delay(10000);  

}//Fin de void loop

// Funciones del usuario
