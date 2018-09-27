/* Christian Moreno Ramirez
   Instituto Tecnologico de León
   Ingeniería en Sistemas Computacionales
   Sistemas Programables
   26/09/2018
   Alarma notificadora de entrada de individuos
*/
#include <Keypad.h> // utilizamos la libreria keypad para poder utilizar el teclado matricial
//#include "LowPower.h"

#define reed 2 // reed switch
#define ledverde 22 // led verde
#define ledrojo 24 // led rojo
#define buzzer 3 // buzzer

////codigo necesario cundo se este trabajando con la liberia del teclado lo unico que debemos editar en este codigo son los pines de las filas y columnas
const byte  filas = 4; // variable de filas
const byte  columnas = 4;  //variable de columnas

byte pinfilas[filas]  = {11, 10, 9, 8};  //pines para las filas la fila 1 esta conenctada al pin 11, la fila 2 al pin 10 y asi sucesibamente
byte pincolumnas[columnas] = {7, 6, 5, 4}; //pines para las Columnas

char teclas[filas][columnas] = {  // matriz de tipo caracter aqui se define acomodo de los caracteres del teclado
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), pinfilas, pincolumnas, filas, columnas); /*objeto de tipo Keypad llamado teclado se inicializa
  con el mapeo de los caracteres con los pines de las filas, columnas seguido del numero de filas y columnas
  termina el codigo necesario
*/

char tecla; //creamos unavariable donde se van guardando las teclas que presionamos
char contrasena[] = "2222"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigo[4]; // Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
int cont = 0; // Esta es una variable que nos servirá más adelante

void setup() {

  pinMode(reed, INPUT_PULLUP);
  pinMode(ledverde, OUTPUT);
  pinMode(ledrojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ingrese la contraseña");

}

void loop() {
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  //LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  int valor = digitalRead(reed);

  tecla = teclado.getKey(); //esta linea indica que el carácter presionado se guardara en la variable teclado
  if (tecla != NO_KEY) //Con este siclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
  {
    codigo[cont] = tecla; //se guardaran los caracteres presionados en codigo[cont]
    Serial.print(codigo[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigo[cont]
    cont = cont + 1; //incrementamos la variable cont (esto con el fin de tener los 4 dígitos que requerimos)
    if (cont == 4) //Ahora comienza otro siclo if, en el cual se pregunta si ya hay 4 datos guardados y si es así entonce el siclo continua

    {

      if (codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3])
      {
        digitalWrite(2, LOW);
        digitalWrite(ledverde, !digitalRead(ledverde)); //si lo anterior es verdad entonces se encenderá el led, si se ingresa nuevamente la contraseña entonces se apagara
        digitalWrite(ledrojo, LOW);
        Serial.println(" Password correcta"); //si la contraseña es correcta entonces se imprime ""Password correcta")
        delay(5000);

      } else {

        Serial.println(" Password incorrecta"); // se imprime que que la Password es incorrecta
        tone(buzzer, 523.25, 500);   //do 5   // Lanza señal a 523.25Hz por el pin 3 durante 500ms.
        delay(550);
        tone(buzzer, 523.25, 500);   //do 5  // Lanza señal a 523.25Hz por el pin 3 durante 500ms.
        delay(550);
      }
      cont = 0; //resetear a 0 la variable cont
    }
  }
  if (valor == HIGH) {
    digitalWrite(ledverde, LOW);
    digitalWrite(ledrojo, HIGH);
    digitalWrite(buzzer, HIGH);
    tone(3, 698.46, 600);  // fa 5 Lanza señal a 698.46Hz por el pin 3 durante 600ms.
    digitalWrite(ledrojo, LOW);
    delay(550);
    tone(3, 932.33, 500);  //  la# 5 Lanza señal a 932.33Hz por el pin 3 durante 600ms.
    digitalWrite(ledrojo, HIGH);
    delay(550);
  }

}


