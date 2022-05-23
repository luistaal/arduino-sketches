/**
   @brief Control de un pulsador utilizando la función 'botonPresionado' y la función 'esBotonPresionado' con millis()
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
void esBotonPresionado(void);

void setup() {
  Serial.begin(9600);
  expansor.begin();
  expansor.pinMode(P0, INPUT);
  expansor.pinMode(P1, INPUT);
}

void loop() {
  esBotonPresionado();
  
  if (botonPresionado(P0)) {
    Serial.println("Botón arriba");
  }

  if (botonPresionado(P1)) {
    Serial.println("Botón abajo");
  }
}

bool botonPresionado (int pBoton) {
  bool bp = expansor.digitalRead(pBoton) == HIGH;

  if (bp && !botonEsPresionado) {
    ultimoTiempoRebote = millis();
    botonEsPresionado = true;
    return true;
  }

  return false;
}

void esBotonPresionado() {
  if (botonEsPresionado == true) {
    if ((millis() - ultimoTiempoRebote) > tiempoRebote) {
      botonEsPresionado = false;
    }
  }
}
