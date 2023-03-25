/***

# Otto_simplificado
Primeiros pasos para o control de OTTO

***/


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
código que chamdas a función externas.

Autor: Víctor M. Álvarez
Data: Marzo de 2023
*/

//#include <NewPing.h>  //Pódese empregar opcionalmente, non en TinkerCad 
#include <Servo.h>

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
#define LR       3  // Perna dereita (Right Leg)
#define FL       4  // Pé esquerdo (Left Foot)
#define LL       2  // Perna esquerda (Left Leg)

Servo peDer, pernaDer, peEsq, pernaEsp;  

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  peDer.attach(FR); 
  pernaDer.attach(LR);
  peEsq.attach(FL);
  pernaEsp.attach(LL);
}

void loop() {
  demasiadoProximo();
}

// Funcións externas

// Función que indica se o obxecto supera o 
// umbral (true) ou non (false
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
  
}

// Función que apaga o zumbador durante 200 ms
void nonZumbar() {
  
}
