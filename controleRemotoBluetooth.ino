/*
  Author: Vinícius Silva Madureira Pereira.
  Date: April, 26th, 2019.
*/

#include <IRremote.h>

byte infravermelho = 12, led = 13, 
	reles[] = {2, 3, 4, 5};
bool estados[] = {HIGH, HIGH, HIGH, HIGH};
IRrecv receptor(infravermelho);
//IRrecv *receptor = new IRrecv(infravermelho);
decode_results resultados;
unsigned long teclas[] = {
  0xFF9867, 0xFFA25D, 0xFF629D, 0xFFE21D,
  0xFF22D, 0xFF02FD, 0xFFC23D, 0xFFE01F,
  0xFFA857, 0xFF906F
};

void setup() {
  receptor.enableIRIn();
  receptor.blink13(true);
  Serial.begin(9600);
  for (byte indice = 0; indice < 4; indice++) {
  	pinMode(reles[indice], OUTPUT);
        digitalWrite(reles[indice], estados[indice]);
  }
}

void loop() {  
  // Controle Remoto
  if (receptor.decode(&resultados)) {
    Serial.println(resultados.value, HEX);
    //Serial.println(keys[0], HEX);    
    for (byte indice = 0; indice < 4; indice++) {
      if (resultados.value == teclas[indice]) {
      	estados[indice] = estados[indice] == HIGH ? LOW : HIGH;
      	digitalWrite(reles[indice], estados[indice]);      
      }
    }
  	receptor.resume();
  }
  // Bluetooth
  if (Serial.available()) {
     byte indice = Serial.readString().toInt();       
     estados[indice] = estados[indice] == HIGH ? LOW : HIGH;
     digitalWrite(reles[indice], estados[indice]);      
  }
}
