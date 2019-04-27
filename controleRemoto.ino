/*
  Author: Vinícius Silva Madureira Pereira.
  Date: April, 26th, 2019.
*/

#include <IRremote.h>

byte infravermelho = 12, led = 13, 
	reles[] = {2, 3, 4, 5};
bool estados[] = {false, false, false, false};
IRrecv receptor(infravermelho);
//IRrecv *receptor = new IRrecv(infravermelho);
decode_results resultados;
unsigned long teclas[] = {
  0xFD30CF, 0xFD08F7, 0xFD8877, 0xFD48B7,
  0xFD28D7, 0xFDA857, 0xFD6897, 0xFD18E7,
  0xFD9867, 0xFD58A7
};

void setup() {
  receptor.enableIRIn();
  receptor.blink13(true);
  Serial.begin(9600);
  for (byte indice = 0; indice < 4; indice++) {
  	pinMode(reles[indice], OUTPUT);
  }
}

void loop() {
  if (receptor.decode(&resultados)) {
    //Serial.println(resultados.value, HEX);
    //Serial.println(keys[0], HEX);    
    for (byte indice = 0; indice < 4; indice++) {
      if (resultados.value == teclas[indice]) {
      	estados[indice] = !estados[indice];
      	digitalWrite(reles[indice], estados[indice]);      
      }
    }
  	receptor.resume();
  }  
}

// LED -  2.94V 0.2mA (min 147 Ohms)
/*

0 - FD30CF
1 - FD08F7
2 - FD8877
3 - FD48B7
4 - FD28D7
5 - FDA857
6 - FD6897
7 - FD18E7
8 - FD9867
9 - FD58A7

*/
