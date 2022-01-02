/**
 * @brief Utilizar un botón como toogle switch
 * @file 49-e2-utilizar-un-boton-como-toogle-switch.ino
 * @author luistaal - https://github.com/luistaal
 * @date 2022-01
 * @version 0.1
 * @attention Distribuida bajo licencia GNU General Public License V3
 */

const uint8_t buttonPin = 22; // declare pin 22 for button
const uint8_t ledPin = 23;    // declare pin 23 for led

uint8_t ledState = 1;         // the current state of the output pin
uint8_t buttonState;          // the current reading from the input pin
uint8_t lastButtonState = 0;  // last button state for push control   

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  uint8_t reading = digitalRead(buttonPin); // read button state

  // if the switch changed, due to noise or pressing
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the led if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState); // define ledPin with variable "ledState" value
  lastButtonState = reading;
}
