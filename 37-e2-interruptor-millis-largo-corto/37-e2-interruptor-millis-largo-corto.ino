/**
   @file     37-e2-interruptor-millis-largo-corto.ino
   @author   luistaal, 2021/07
   @brief    Detección durante la pulsación (corta/larga) usando millis()

   @attention
   Distribuida bajo licencia GNU General Public License V3
*/

const uint8_t pinLed = 13;            // declare pin 13 for led
const uint8_t pinButton = 12;         // declare pin 12 for button
const uint16_t onDuraction = 100;     // duraction time activated of led
const uint16_t offDuraction = 500;    // duraction time desactivated of led
const uint16_t longPressTime = 2000;  // long press time of button

unsigned long initialTime = 0;        // control initial time of push button
unsigned long rememberTime = 0;       // remember time for duration led blink
uint8_t ledState = 1;                 // led status for high or low
uint8_t blinkSwitch = 0;              // switch for activated/desactivated led blink

void setup() {
  Serial.begin(9600);          // define serial port 9600
  pinMode(pinLed, OUTPUT);     // define pinLED as output
  pinMode(pinButton, INPUT);   // define pinButton as input
}

void loop() {
  uint8_t buttonState = digitalRead(pinButton); // read button state

  // detected in state button on actived
  if (buttonState == 0) {
		if (initialTime == 0) initialTime = millis();
		
		if ((millis() - initialTime) > longPressTime) {
			Serial.println("2 seconds have passed.");
			initialTime = millis();
			Serial.println(initialTime);
			blinkSwitch = !blinkSwitch;
		}
  }

	// detected in state button on desactivated
	if (buttonState == 1) {
		initialTime = 0;
	}

  // activated the flashing of the led
  if (blinkSwitch == 1) {
    if (ledState == 1) {
      if ((millis() - rememberTime) >= onDuraction) {
        ledState = 0;
        rememberTime = millis();
      }
    } else if (millis() - rememberTime >= offDuraction) {
      ledState = 1;
      rememberTime = millis();
    }

    digitalWrite(pinLed, ledState);
  } else {
    digitalWrite(pinLed, 0);
  }
}