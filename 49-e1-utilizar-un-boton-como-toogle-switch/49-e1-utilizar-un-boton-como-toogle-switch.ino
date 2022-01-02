/**
 * @brief Utilizar un botón como toogle switch
 * @file 49-e1-utilizar-un-boton-como-toogle-switch.ino
 * @author luistaal - https://github.com/luistaal
 * @date 2021-12
 * @version 0.1
 * @attention Distribuida bajo licencia GNU General Public License V3
 */

const uint8_t buttonPin = 22; // declare pin 22 for button
const uint8_t ledPin = 23;    // declare pin 23 for led

uint8_t buttonState;          // read button state
uint8_t lastButtonState = 1;  // last button state for push control
uint8_t ledState = 0;         // led status on or off
uint8_t pauseTime = 100;      // pause time for the button

void setup() {
  pinMode(buttonPin, INPUT);  // define buttonPin as input
  pinMode(ledPin, OUTPUT);    // define ledPin as output

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  buttonState = digitalRead(buttonPin); // read button state

  if (buttonState == 0 && lastButtonState == 1) {
    if (ledState == 0) {
      digitalWrite(ledPin, HIGH); // define LedPin with high value
      ledState = 1;
    } else {
      digitalWrite(ledPin, LOW); // define LedPin with low value
      ledState = 0;
    }
  }

  lastButtonState = buttonState; // save the last state of the button
  delay(pauseTime); // delay with pause time
}
