/**
   @brief Control de un pulsador con delay utilizando el PCF8574
   @file 62-e1-expansor-pcf8574-pulsador-delay.ino
   @author luistaal - https://github.com/luistaal
   @date 2022-05
   @version 0.1
   @link https://github.com/xreef/PCF8574_library
   @attention Distribuida bajo licencia GNU General Public License V3
*/

#include "PCF8574.h"

uint8_t estadoBotonAnterior = 1;

PCF8574 expansor(0x20);

void setup() {
  Serial.begin(9600);
  expansor.begin();
  expansor.pinMode(P0, INPUT);
}

void loop() {
  uint8_t estadoBoton = expansor.digitalRead(P0);

  if (estadoBoton == 0 && estadoBotonAnterior == 1) {
    if (estadoBoton == 0) {
      Serial.println("Botón pulsado");
    }
  }

  estadoBotonAnterior = estadoBoton;
  delay(100);
}
