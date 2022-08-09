// include the library code:
#include <LiquidCrystal.h>
#include <math.h>
#include <DHT.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const int Trigger = 6;
const int Echo = 5;   //Pin digital 2 para el Echo del sensor

int PinRoj = 2;
int PinAzu = 3;
int PinVer = 4;
// Pin analogico de entrada para el LDR
int pinTMP = 0;
 
// Variable donde se almacena el valor del LDR
int valorTMP = 0;  


//TEMPERATURA
const int DHTPin = 13; 
DHT dht(DHTPin, DHTTYPE);
  
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  // Configuramos como salidas los pines donde se conectan los led
  pinMode(PinRoj, OUTPUT);
  pinMode(PinAzu, OUTPUT);
  pinMode(PinVer, OUTPUT);
  
    
  //  Configurar el puerto serial
  Serial.begin(9600);
    
  digitalWrite(PinRoj, HIGH);
  digitalWrite(PinAzu, LOW);
  digitalWrite(PinVer, LOW);

  //TEMPERATURA
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {
  //TEMPERATURA
   delay(2000);
   float h = dht.readHumidity();
   float t = dht.readTemperature();
 
   if (isnan(h) || isnan(t)) {
   Serial.println("Error en medición del  sensor!");
   return;
   } 
   Serial.print("Humedad: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.print(" *C ");
  //ULTRASONICO Y PANTALLA LCD
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    // Print a message to the LCD.
  lcd.print("Porcentaje agua:");
  lcd.setCursor(12, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);                                                       // Tiempo
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  float div; //para sacar el %
  long p; // porcentaje de liquido
  long aux; // variable axiliar para limpiar la pantalla, funciona como variable temporal del valor p
  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  
  delay(100);          //Hacemos una pausa de 100ms 
  div = d;// variable para poder dividir entre float y long numbers
  aux = p;
  p = roundf((((29-div)/26)*100));// conversion de cm a % de agua en el termo
  Serial.print(p);
  Serial.print("% ");
  lcd.setCursor(0,1); // mover el cursor

  if (p > 99){
    p = 100;
  }
  if (p < 1){
    p = 0;
  }
  lcd.print(p); // imprimir el porcentaje de liquido
  lcd.print("%");
  delay(1000);
  lcd.clear();

   valorTMP= analogRead(pinTMP);
  
  Serial.print("Valor TMP := ");
  Serial.println(valorTMP);

  /*
  lcd.setCursor(1,10);
  lcd.print(valorTMP);
  lcd.setCursor(0,0);
  */
}
 
