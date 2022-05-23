/**
   @brief Control de un pulsador utilizando la función 'botonPresionado'
   @file 62-e3-expansor-pcf8574-pulsador-delay.ino
   @author luistaal - https://github.com/luistaal
   @date 2022-05
   @version 0.1
   @link https://github.com/xreef/PCF8574_library
   @attention Distribuida bajo licencia GNU General Public License V3
*/

#include "PCF8574.h"

PCF8574 expansor(0x20);

bool botonPresionado(int pBoton);

void setup() {
  Serial.begin(9600);
  expansor.begin();
  expansor.pinMode(P0, INPUT);
}

void loop() {
  if (botonPresionado(P0)) {
    Serial.println("Botón pulsado");
  }
}

bool botonPresionado(int pBoton) {
  bool bp = expansor.digitalRead(pBoton) == HIGH;
  if (bp) {
    delay(250);
  }

  return bp;
}
