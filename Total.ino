/*
  Capitulo 5 de Arduino desde cero en Español
  Segundo programa que envía mediante el Monitor Serial el valor de distancia
  leído por el sensor ultrasónico HC-SR04 y enciende y apaga LED dentro del
  rango de 0 a 20 cms.

  Autor: bitwiseAr  

*/
//variables ultrasonico
int TRIG = 10;      // trigger en pin 10
int ECO = 9;      // echo en pin 9
int LEDV = 11;      // LED en pin 3
int LEDR = 3;
int LEDA = 12;
int DURACION;
int DISTANCIA;

//variables sensor-color
#define S0 4    // S0 a pin 4
#define S1 5    // S1 a pin 5
#define S2 6    // S2 a pin 6
#define S3 7    // S3 a pin 7
#define salidaTCS 8 // salidaTCS a pin 8

void setup()
{
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(LEDV, OUTPUT);   // LED verde como salida
  pinMode(LEDR, OUTPUT);   // LED rojo como salida
  pinMode(LEDA, OUTPUT);   // LED azul como salida    

  pinMode(S0, OUTPUT);    // pin 4 como salida
  pinMode(S1, OUTPUT);    // pin 5 como salida
  pinMode(S2, OUTPUT);    // pin 6 como salida
  pinMode(S3, OUTPUT);    // pin 7 como salida
  pinMode(salidaTCS, INPUT);  // pin 8 como salida
  
  digitalWrite(S0,HIGH);  // establece frecuencia de salida
  digitalWrite(S1,LOW);   // del modulo al 20 por ciento
  Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps

}

void loop()
{
  digitalWrite(S2,LOW);     // establece fotodiodos
  digitalWrite(S3,LOW);     // con filtro rojo
  int rojo = pulseIn(salidaTCS, LOW); // obtiene duracion de pulso de salida del sensor
  delay(200);       // demora de 200 mseg
  
  digitalWrite(S2,HIGH);    // establece fotodiodos
  digitalWrite(S3,HIGH);    // con filtro verde
  int verde = pulseIn(salidaTCS, LOW);  // obtiene duracion de pulso de salida del sensor
  delay(200);       // demora de 200 mseg
  
  digitalWrite(S2,LOW);     // establece fotodiodos
  digitalWrite(S3,HIGH);    // con filtro azul
  int azul = pulseIn(salidaTCS, LOW); // obtiene duracion de pulso de salida del sensor
  delay(200);       // demora de 200 mseg

  
  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial
  delay(200);       // demora entre datos


  if (DISTANCIA <= 10 && DISTANCIA >= 0){ // si distancia entre 0 y 20 cms.
     if ( rojo < 250 && verde > 300 && azul > 60){   // si valores dentro del rango
        digitalWrite(LEDR, HIGH);      // enciende LED
        delay(5000);      // demora proporcional a la distancia
        digitalWrite(LEDR, LOW);     // apaga LED // muestra texto
     } 
    else if ( verde < 250 && rojo > 150 && azul > 80){  // si valores dentro del rango
        digitalWrite(LEDV, HIGH);      // enciende LED
        delay(5000);      // demora proporcional a la distancia
        digitalWrite(LEDV, LOW);     // apaga LED // muestra texto
     }
    else if ( azul < 200 && rojo > 200 && verde > 100){  // si valores dentrol del rango
         digitalWrite(LEDA, HIGH);      // enciende LED
         delay(5000);      // demora proporcional a la distancia
         digitalWrite(LEDA, LOW);     // apaga LED       // muestra texto
     }
    }
   
}
