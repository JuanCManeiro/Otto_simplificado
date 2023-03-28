/**

É un esquema das conexións internas dun robot Otto, que debe levar: (a) un zumbador (pin 13), (b) catro servos, 
(c) un sensor de distancia HC-SR04 (trigger pin 8, echo pin 9). Os catro servos corresponden con: 
pé dereito (pin 5), pé esquerdo (pin 4), perna dereita (pin 3) e perna esquerda (pin 2).
Por outra parte, a alimentación dos servos ten que ser externa, o buzzer e o sensor de distancia poden ir
conectados á placa Arduíno.

É MOI importante que GND da alimentación externa sexa o mesmo que o do Arduíno.

A primeira tarefa que imos facer é detectar obxectos demasiado próximos. Para iso imos pór 12 cm como umbral 
de detección e o zumbador como aviso de que o obxecto superou o umbral. Como dificultade adicional, 
dentro da función 'loop()' NON pode haber máis código que chamadas a función definidas aparte.

Facilítase no enunciado da práctica un arquivo .ino coa estructura do que se pide. O arquivo é correcto (compila),
pero non realiza ningunha tarefa. Debes completar o código das tres funcións que se indican a seguir do 'loop()'.
  
  **/


/* Programa que imita o comportamento dun robot Otto simplificado.

As conexións aos servos son as que se indican a seguir.
         --------------- 
        |     O   O     |
        |---------------|
LR 3==> |               | <== LL 2
         --------------- 
            ||     ||
            ||     ||
FR 5==>   -----   ------  <== FL 4
         |-----   ------|
         
O zumbador vai conectado no pin 13 e o sensor de distancia HC-SR04 
nos pins 9 (echo) e 8 (trigger).

A función loop() vai facendo chamadas a funcións definidas aparte. NON inclúe máis
código que chamadas a función externas.

Autor: Víctor M. Álvarez eu.....
Data: Marzo de 2023
*/

//#include <NewPing.h>  //Pódese empregar opcionalmente, non en TinkerCad 
#include <Servo.h>

//Pin de control do servo Para provar con potenciometro
//#define CTRL 3 // Definimos o control para a Saida 3 do Arduino // esta usado FR PARA A PERNA DEREITA

//Pin de lectura do potenciometro
#define POT A5 // Definimos o potenciometro en entrada Analoxica A5 //Para provar con potenciometro


// Definicións do sensor HC-SR04
#define ECHO           9
#define TRIGGER        8
#define DIST_MAX       200
#define UMBRAL_DIST    12

//NewPing sonar(TRIGGER, ECHO, DIST_MAX); //Obxecto sensor de distancia para <NewPing.h>


// Buzzer
#define BUZZER   13

// Definicións dos servos
#define FR       5  // Pé dereito (Right Foot)
#define FL       4  // Pé esquerdo (Left Foot)
#define LR       3  // Perna dereita (Right Leg)
#define LL       2  // Perna esquerda (Left Leg)

Servo peDer, pernaDer, peEsq, pernaEsq; // E vez de chamarlle motor agora chamamoslle perna... e decir "servo peDer"

int angulo = 10; //Por que empezamos en 10? //Para provar con potenciometro
int veloc = 3000; //Tempo que tarda en recorrer o codigo e enviar a orde de movemento //Para provar con potenciometro

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGGER, OUTPUT); // pin trigger do sr04 SAIDA
  pinMode(ECHO, INPUT);     // pin echo do sensor
  
  pinMode(BUZZER, OUTPUT);  // pin que da señal o buzzer (zumbador)
  
  peDer.attach(FR);  // usarei perna dereita para as primeiras provas
  pernaDer.attach(LR);
  peEsq.attach(FL);
  pernaEsq.attach(LL);
}

void loop() {
  demasiadoProximo();
  
   //Lectura do potenciometro//Para provar con potenciometro, o pe dereito reacciona o potenciometro
  angulo = analogRead(POT);                  
  angulo = map(angulo, 0, 1023, 0, 180); // mapeamos o valor do angulo xa que o servo esta entre 0 e 180 e a placa arduino
                                         // danos valores entre 0 e 1023
  
  //Actualiza servo
  //Todos os servos reaccionan co potenciometro o mesmo tempo
    peDer.write(angulo);
    pernaDer.write(angulo);
    peEsq.write(angulo);
    pernaEsq.write(angulo);
  delay(veloc); // usamos sempre variables definidas anteriormente asi en caso de modificacion non temos que vir o loop
  Serial.println(angulo); // ATA AQUI Para probar con potenciometro
  
  
}
 
// Funcións externas

// Función que indica se o obxecto supera o 
// umbral (true) ou non (false)
bool demasiadoProximo() {
  if(distanciaObxecto() < UMBRAL_DIST) zumbar(); 
  else nonZumbar(); 
  delay(50);
}

// Función que calcula a distancia ao obxecto en cm
// Incúe unha espera de 50 ms
float distanciaObxecto() {
  
}

// Función que fai zumbar o zumbador durante 200 ms
void zumbar() {
  // if(){
  //}
  //else{
  //}
  
}

// Función que apaga o zumbador durante 200 ms
void nonZumbar() {
  
}

/**

#include <Servo.h>  //incluimos a librerias Servo.h xa incluida no IDE de Arduino

//Pin de control do servo
#define CTRL 3 // Definimos o control para a Saida 3 do Arduino

//Pin de lectura do potenciometro
#define POT A5 // Definimos o potenciometro en entrada Analoxica A5

     //Parece que non da problemas escribir despois da almofada ainda que non cambia de cor

//Declaramos o obxecto motor
//da clase Servo
Servo motor;
int angulo = 10; //Por que empezamos en 10?
int veloc = 500; //Tempo que tarda en recorrer o codigo e enviar a orde de movemento


void setup() {
  motor.attach(CTRL);
  Serial.begin(9600); //Activamos o monitor serie por se necesitamos sacar algunha informacion
  
}


void loop() {
  //Lectura do potenciometro
  angulo = analogRead(POT);
  angulo = map(angulo, 0, 1023, 0, 180); // mapeamos o valor do angulo xa que o servo esta entre 0 e 180 e a placa arduino
                                         // danos valores entre 0 e 1023
  
  //Actualiza servo
  motor.write(angulo);
  delay(veloc); // usamos sempre variables definidas anteriormente asi en caso de modificacion non temos que vir o loop
  Serial.println(angulo);
}

**/


/***

Traido de sensor sr04 

/*
 * Script para medir a distancia
 * a un obxecto, empregando un
 * sensor de ultrasóns HC-SR04
 */

/***

#define TRIGGER 9
#define ECHO 10
//Defimos macro para calcular distancia
#define calcDist(t) t*0.017
#define zum 6

float tempo, distancia;
float tInicial, tFinal;
int echo;
String mensaxe = "";
int espera = 500;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(zum, OUTPUT);
}

void loop() {
   if(distancia > 50){         // Si distancia es >50 cm el zumbador suena
     digitalWrite(zum, HIGH);
     delayMicroseconds(100);
      if(distancia > 50){      // Si distancia es < 50 cm no suena
     digitalWrite(zum, LOW);
        delayMicroseconds(100);
   }
     
   }

  //Enviamos un pulso co HC-SR04
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  echo = digitalRead(ECHO);
  tInicial = micros();
  while(echo == LOW) {
    echo = digitalRead(ECHO);
  }
  while(echo == HIGH) {
    echo = digitalRead(ECHO);
    tFinal = micros();
    
   }
  //A resta dos dous tempos danos
  //a duración do pulso desde que
  //se empeza a enviar até que se
  //deixa de recibir
  tempo = tFinal - tInicial;
  tempo /= 2; 
  
  //Calculamos a distancia en cm
  distancia = calcDist(tempo);

  //Escribimos no porto serie os resultados
  mensaxe = "Distancia: " + String(distancia) + " cm";
  Serial.println(mensaxe);
  delay(espera);
}

***/

/*
 * Función para calcular a distancia en cm.
 * 
 * A distancia medida é o doble da obtida
 * polo sensor (ida e volta).
 * As unidades serán en cm/us, a velocidade
 * do son é 340 m/s = 
 * = 340 m/s * (1 s)/(1000000 us) * (100 cm)/(1 m) =
 * = 340 / 10000 cm/us = 0.034 cm/us
 */
/*****
float calcularDistancia(float t) {
  // v = 2*dist / tempo ==> dist = tempo*v/2
  // dist = tempo*0.034/2 = tempo*0.017 [cm]
  return t*0.017;

} 

*****/

/** Estructura if - else

if(){
     else{
     } 
     }
     
     estructura if
     
     if(dist > 30cm ){
     digitalWrite(zum, high);
     }
**/     
