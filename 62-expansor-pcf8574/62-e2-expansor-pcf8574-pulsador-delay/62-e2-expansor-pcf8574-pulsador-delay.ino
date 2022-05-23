/**
   @brief Control de un pulsador con delay utilizando el flag 'botonPresionado'
   @file 62-e2-expansor-pcf8574-pulsador-delay.ino
   @author luistaal - https://github.com/luistaal
   @date 2022-05
   @version 0.1
   @link https://github.com/xreef/PCF8574_library
   @attention Distribuida bajo licencia GNU General Public License V3
*/

#include "PCF8574.h"

bool botonPresionado = false;

PCF8574 expansor(0x20);

void setup() {
  Serial.begin(9600);
  expansor.begin();
  expansor.pinMode(P0, INPUT);
}

void loop() {
  uint8_t estadoBoton = expansor.digitalRead(P0);

  if (estadoBoton == 1 && botonPresionado == false) {
    Serial.println("Botón pulsado");
    botonPresionado = true;
  }

  if (estadoBoton == 0) botonPresionado = false;

  delay(100);
}
