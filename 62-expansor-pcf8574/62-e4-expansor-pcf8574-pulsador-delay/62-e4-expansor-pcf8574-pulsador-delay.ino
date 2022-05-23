/**
   @brief Control de un pulsador utilizando la función 'botonPresionado' con millis()
   @file 62-e4-expansor-pcf8574-pulsador-delay.ino
   @author luistaal - https://github.com/luistaal
   @date 2022-05
   @version 0.1
   @link https://github.com/xreef/PCF8574_library
   @attention Distribuida bajo licencia GNU General Public License V3
*/

#include "PCF8574.h"

PCF8574 expansor(0x20);

bool botonEsPresionado = false;
unsigned long ultimoTiempoRebote = 0;
unsigned long tiempoRebote = 250;

bool botonPresionado(int pBoton);

void setup() {
  Serial.begin(9600);
  expansor.begin();
  expansor.pinMode(P0, INPUT);
}

void loop() {
  if (botonPresionado(P0) && botonEsPresionado == false) {
    Serial.println("Botón pulsado");
    ultimoTiempoRebote = millis();
    botonEsPresionado = true;
  }

  if ((millis() - ultimoTiempoRebote) > tiempoRebote) {
    botonEsPresionado = false;
  }
}

bool botonPresionado (int pBoton) {
  bool bp = expansor.digitalRead(pBoton) == HIGH;
  
  return bp;
}
