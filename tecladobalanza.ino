#include <Keypad.h>
#include "HX711.h"

char contrasena[]="11"; //carne
int cont=0; //incrementa por tecla


char codigo[2]; 
const int DOUT=A1; //balanza 
const int CLK=A0; //balanza
const byte ROWS=4; //filas de teclado
const byte COLS =4; //columnas del teclado 

char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
byte rowPins[ROWS] = {9, 8, 7, 6}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {5, 4, 3, 2}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

HX711 balanza;

 void setup()
 {
  pinMode(13, OUTPUT); // led guía
  Serial.begin(9600);
  balanza.begin(DOUT, CLK);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(439430.25); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar...");    
 }

void loop()
{
  //setup para teclado
    char customKey = customKeypad.getKey(); //se guarda en la variable customKey el caracter de la tecla presionada
  if (customKey != NO_KEY)         //se evalúa si se presionó una tecla
  {
    codigo[cont]=customKey;          //se guarda caracter por caracter en el arreglo codigo[]
    Serial.println(codigo[cont]);    //se imprime en el puerto serie la tecla presionada
    cont=cont+1;              //incrementamos la variable cont
    if(cont==2)          //si ya fueron presionadas 4 teclas se evalúa si la contraseña es correcta
    {
      if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1])
      {
        Serial.print("Peso de Carne: ");
        Serial.print(balanza.get_units(20),3);
        Serial.println(" kg");
      }

      else
      {
        Serial.print("Peso de Vegetales: ");
        Serial.print(balanza.get_units(20),3);
        Serial.println(" kg");
      }

      cont=0;  //resetear a 0 la variable cont
    }
  }
}
