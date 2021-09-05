/**
 * @brief Multitarea con 3 procesos: un reloj, un interruptor de led y una alarma
 * @file 36-e1-multitarea-millis-nano.ino
 * @author luistaal - https://github.com/luistaal
 * @date 2021-05
 * @version 0.1
 * @attention Distribuida bajo licencia GNU General Public License V3
 */

unsigned long currentTimeA = 0;
unsigned long currentTimeB = 0;
long begin, final, timeNow;
byte buttonReading_old = 1;

byte hour = 9;
byte minute = 59;
byte second = 55;
String showHour;
String showMinute;
String showSecond;

const byte pinLed = A5;
const byte pinLedNano = 13;
const byte pinButton = 6;

uint8_t alarmOn[] = {10, 00, 00};
uint8_t alarmOff[] = {10, 00, 10};

void setup()
{
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinLedNano, OUTPUT);
  pinMode(pinButton, INPUT);

  begin = alarmOn[0] * 100000 + alarmOn[1] * 1000 + alarmOn[2] * 100;
  final = alarmOff[0] * 100000 + alarmOff[1] * 1000 + alarmOff[2] * 100;
}

void loop()
{
  byte buttonReading = digitalRead(pinButton);

  if (buttonReading != buttonReading_old) {
    if (buttonReading == 0) {
      blink13();
    }
  }

  buttonReading_old = buttonReading;

  if (millis() >= currentTimeA + 1000) {
    currentTimeA = millis();
    time();
  }

  timeNow = hour * 100000 + minute * 1000 + second * 100;

  bool minimum = timeNow >= begin;
  bool maximum = timeNow <= final;

  if ( minimum && maximum ) {
    if (millis() >= currentTimeB + 100) {
      currentTimeB = millis();
      blink();
    }
  } else {
    digitalWrite(pinLed, 0);
  }
}

void blink()
{
  byte ledReading = digitalRead(pinLed);
  digitalWrite(pinLed, !ledReading);
}

void blink13()
{
  byte ledNanoReading = digitalRead(pinLedNano);
  digitalWrite(pinLedNano, !ledNanoReading);
}

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
  
  String showHour = String(hour);
  String showMinute = String(minute);
  String showSecond = String(second);
  
  if (hour < 10) showHour = "0" + String(hour);
  if (minute < 10) showMinute = "0" + String(minute);
  if (second < 10) showSecond = "0" + String(second);
  
  Serial.println(showHour + ":" + showMinute + ":" + showSecond);
}