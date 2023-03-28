/* O monitor serie non me da a mesma distancia que marca o sensor ultrasonico no simulador, comprovar se iso 
   e o correcto
  
Programa que imita o comportamento dun robot Otto simplificado.

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

Autor: Juan Carlos Maneiro Moreira
Data: Marzo de 2023
*/

//#include <NewPing.h>  //Pódese empregar opcionalmente, non en TinkerCad 
#include <Servo.h>

//Pin de control do servo Para provar con potenciometro
//#define CTRL 3 // Definimos o control para a Saida 3 do Arduino // esta usado FR PARA A PERNA DEREITA, tamen activa o resto de servos

//Pin de lectura do potenciometro
#define POT A5 // Definimos o potenciometro en entrada Analoxica A5 //Para provar con potenciometro

// Definicións do sensor HC-SR04
#define ECHO           9
#define TRIGGER        8

#define calcDist(t) t*0.034 // definimos calcDist como o resultado dado polo tempo que tarda o son entre o 
                            // trigger e o echo no esta correcto o 100% con 0.017 dame cerca da metade asi
                            //que usei 0.034 pero tampouco e 100x100 exato ten demasiado erro...INVESTIGAR 

#define DIST_MAX       200
#define UMBRAL_DIST    50 //Cambiado umbral xa que algo teño mal no codigo e no lee ben a distancia, ou eso parece
                          // a 50cm e mais cerca zumba, se me alexo deixa de zumbar SEGUE SENDO PRECISO CO 0.034

// funcions definidas que poderemos usar en calquera momento

float tempo, distancia; //funcions flotantes para medir tempo e distancia
float tInicial, tFinal; //funcions flotantes para medir os tempos de ida e volta do sensor coas cales calculara adistancia por medio da funcion t definida mais adiante
int echo;
String mensaxe = "";    //usamolo para poder comunicarnos coa placa a traves do serial (monitor serie)
int espera = 200;       // outro tempo para usar no delay
//int grados = º; // non me deixa usar º pensa que e "\" revisar mais adiante

//NewPing sonar(TRIGGER, ECHO, DIST_MAX); //Obxecto sensor de distancia para <NewPing.h>


// Buzzer
#define BUZZER   13

// Definicións dos servos
#define FR       5  // Pé dereito (Right Foot)
#define FL       4  // Pé esquerdo (Left Foot)
#define LR       3  // Perna dereita (Right Leg)
#define LL       2  // Perna esquerda (Left Leg)

Servo peDer, pernaDer, peEsq, pernaEsq; //Definimos os servomotores, E vez de chamarlle motor agora chamamoslle perna... e decir "servo peDer" 

int angulo = 10; //Por que empezamos en 10? //Para provar con potenciometro
int veloc = 2000; //Tempo que tarda en recorrer o codigo e enviar a orde de movemento //Para provar con potenciometro

void setup() { //donde se encontra toda a configuracion do codigo
  Serial.begin(9600);      // poñemolo sempre para poder utilizar o monitor serie, necesario tanto para recibir como para enviar 
  pinMode(TRIGGER, OUTPUT);// pin trigger do sr04 SAIDA
  pinMode(ECHO, INPUT);    // pin echo do sensor
  
  pinMode(BUZZER, OUTPUT); // pin que da señal o buzzer (zumbador)
                 
  peDer.attach(FR);        // usarei perna dereita para as primeiras provas
  pernaDer.attach(LR);     // mais adiante useinas todas, e decir cun servo manexo todos o servos ao mesmo tempo
  peEsq.attach(FL);        // decimos que cada pe-perna se ten que activar coma un motor
  pernaEsq.attach(LL);     // attach e unha variable do id de arduino "atach", que se usa para definir aos motores
}

void loop() { //donde se encontra a parte do programa que se vai repetir ciclicamente (bucle)
  demasiadoProximo();
  
  //Lectura do potenciometro//Para provar con potenciometro, o pe dereito reacciona o potenciometro
  angulo = analogRead(POT);              // decimos que ángulo é a lectura do potenciómetro             
  angulo = map(angulo, 0, 1023, 0, 180); // mapeamos o valor do angulo xa que o servo esta entre 0 e 180 e a placa arduino
                                         // danos valores entre 0 e 1023
  
  //Actualiza servo
  
                              //Todos os servos reaccionan co potenciometro o mesmo tempo
    peDer.write(angulo);      //posicionamos os servos no valor do angulo dado polo potenciometro
    pernaDer.write(angulo);
    peEsq.write(angulo);
    pernaEsq.write(angulo);
  delay(veloc); // usamos sempre variables definidas anteriormente asi en caso de modificacion non temos que vir o loop
  Serial.print(angulo); // imprime o valor do angulo no monitor serie // ATA AQUI Para probar con potenciometro
  Serial.println(" grados"); //recordatorio "" di o que hai dentro, sen comillas refirese a unha funcion definida

}

// Funcións externas

// Función que indica se o obxecto supera o 
// umbral (true) ou non (false
bool demasiadoProximo() { //variables buleanas, as variables deste tipo poden ter dous valores, true (verdadeiro) ou false (falso)
  // creo que poderiamos conseguir que o zumbador soase ou non xa dende aqui ainda que o fixen coa funcion float 
  if(distanciaObxecto() < UMBRAL_DIST) zumbar(); //vale, si que o necesito, esta funcion forma parte das definicions do float e tamen precisas
  else nonZumbar();    //para saber cando o zumbador debe estar activo ou non, si distancia <UMBRAL_DIST(neste caso 50) deber zumbar
  delay(50);           // en caso contrario (else) non zumbara
}

// Función que calcula a distancia ao obxecto en cm
// Incúe unha espera de 50 ms

float distanciaObxecto() {
  
    //Enviamos un pulso co HC-SR04
  digitalWrite(TRIGGER, LOW);   //primeiro aseguramos que o trigger este en baixo para poder emitir un ultrason
  delayMicroseconds(5);         //5 micro sec
  digitalWrite(TRIGGER, HIGH);  // enviamos un primero pulso de 10 sg
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);   // volvemos a desactivar o trigger e agardamos o eco do son
  echo = digitalRead(ECHO);     // recibimos o son
  tInicial = micros();          //calculamos o tempo en micro sec
  while(echo == LOW) {
    echo = digitalRead(ECHO);
  }
  while(echo == HIGH) {
    echo = digitalRead(ECHO);
    tFinal = micros();
  }
  //A resta dos dous tempos danos a duración do pulso desde que se empeza a enviar até que se deixa de recibir
  tempo = tFinal - tInicial;
  tempo /= 2; 
  
  //Calculamos a distancia en cm
  //distancia = calcDist(tempo);

  //Escribimos no porto serie os resultados
  mensaxe = "Distancia: " + String(distancia) + " cm";
  Serial.println(mensaxe);
  delay(espera);
  
  return distancia; // moi necesario o retorno da distancia
  
}


float calcularDistancia(float t) { //Aqui metemos a funcion zumba non zumba si se cumple o umbral dado
  
  if (distancia < UMBRAL_DIST) //se a distancia e < UMBRAL_DIST
  {
    
  }
    
}

// Función que fai zumbar o zumbador durante 20 ms
void zumbar() {
  
  // Lanzamos alertas
    digitalWrite(BUZZER, HIGH); //fai soar o zumbador durante 20 ms
    delay(20);
  
}

// Función que apaga o zumbador durante 20 ms
void nonZumbar() {
  
  digitalWrite(BUZZER, LOW); // apaga o buzzer, creo que finxen un lio o buzzer estame dando a distancia
    delay(20);
  
}

/**  datos esliminados para posterior analise

 // v = 2*dist / tempo ==> dist = tempo*v/2 
  // dist = tempo*0.034/2 = tempo*0.017 [cm]
  // return t*0.017;
  
  **/
/*
 * Función para calcular a distancia en cm.
 * A distancia medida é o doble da obtida
 * polo sensor (ida e volta).
 * As unidades serán en cm/us, a velocidade
 * do son é 340 m/s = 
 * = 340 m/s * (1 s)/(1000000 us) * (100 cm)/(1 m) =
 * = 340 / 10000 cm/us = 0.034 cm/us
 */
