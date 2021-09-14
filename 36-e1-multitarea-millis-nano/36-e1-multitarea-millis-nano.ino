/**
 * @brief Multitarea con 3 procesos: un reloj, un interruptor de led y una alarma
 * @file 36-e1-multitarea-millis-nano.ino
 * @author luistaal - https://github.com/luistaal
 * @date 2021-05
 * @version 0.1
 * @attention Distribuida bajo licencia GNU General Public License V3
 */

const uint8_t pinLed = A5;        // declare pin A5 for led
const uint8_t pinLedNano = 13;    // declare pin 13 for internal led
const uint8_t pinButton = 6;      // declare pin 6 for button

unsigned long currentTimeA = 0;   // variable for current time A
unsigned long currentTimeB = 0;   // variable for current time B
long begin, end, timeNow;         // variable for the start and end time of the alarm, in addition to the current time
uint8_t buttonOldReading = 1;     // variable for button old reading

uint8_t hour = 9;                   // clock in hours
uint8_t minute = 59;                // clock in minutes
uint8_t second = 55;                // clock in seconds
uint8_t alarmOn[] = {10, 00, 00};   // clock for alarm on
uint8_t alarmOff[] = {10, 00, 10};  // clock for alarm off

void setup()
{
  Serial.begin(9600);           // define serial port 9600
  pinMode(pinLed, OUTPUT);      // define pinLed as output
  pinMode(pinLedNano, OUTPUT);  // define pinLedNano as output
  pinMode(pinButton, INPUT);    // define pinButton as input
  begin = alarmOn[0] * 100000 + alarmOn[1] * 1000 + alarmOn[2] * 100;   // prepare alarm variable on
  end = alarmOff[0] * 100000 + alarmOff[1] * 1000 + alarmOff[2] * 100;  // prepare alarm variable off
}

void loop()
{
  uint8_t buttonReading = digitalRead(pinButton); // read button state

  // detected in state button on actived
  if (buttonReading != buttonOldReading) {
    if (buttonReading == 0) {
      blink13(); // call to the blink13() function
    }
  }

  buttonOldReading = buttonReading;

  // check if a second has passed
  if (millis() - currentTimeA >= 1000) {
    currentTimeA = millis();
    time(); // call to the time() function
  }

  // prepare time variable now
  timeNow = hour * 100000 + minute * 1000 + second * 100;

  bool minimum = timeNow >= begin;  // time now is greater than or equal to start
  bool maximum = timeNow <= end;    // time now is less than or equal to end

  // check if the two variable meet true
  if ( minimum && maximum ) {
    if (millis() - currentTimeB >= 100) {
      currentTimeB = millis();
      blink(); // call to the blink() function
    }
  } else {
    digitalWrite(pinLed, 0);
  }
}

/*!
  @brief   Reading the state of the 'pinLed' led and returns the status as high/low
  @return  Returns the status of the led
*/ 
void blink()
{
  uint8_t ledReading = digitalRead(pinLed);
  digitalWrite(pinLed, !ledReading);
}

/*!
  @brief   Reading the state of the 'pinLedNano' led and returns the status as high/low
  @return  Returns the status of the led
*/ 
void blink13()
{
  uint8_t ledNanoReading = digitalRead(pinLedNano);
  digitalWrite(pinLedNano, !ledNanoReading);
}

/*!
  @brief   Prepare the time and data string to print on the Serial
  @return  Returns the time in the Serial
*/ 
void time()
{
  second++;
  
  if (second == 60) {
    second = 0;
    minute++;
  }
  
  if (minute == 60) {
    minute = 0;
    hour++;
  }
  
  if (hour == 24) {
    hour == 0;
  }

  Serial.print("Clock: ");
  if (hour < 10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if (minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  if (second < 10) Serial.print("0");
  Serial.print(second);
  Serial.print("\n");
}