/**
   @brief Temporalizador que pausa y reanuda el tiempo usando pulsadores y millis
   @file 65-pausar-reanudar-temporalizador-con-millis.ino
   @author luistaal - https://github.com/luistaal
   @date 2022-06
   @version 0.1
   @attention Distribuida bajo licencia GNU General Public License V3
*/

enum
{
  STATE_INIT,
  STATE_WAIT_FOR_START,
  STATE_RUNNING,
  STATE_PAUSED,
  STATE_STOPPED,
} state; // conjunto definido de estados

const uint8_t botonIniciar = 2; // pin para el botón iniciar
const uint8_t botonParar = 3; // pin para el botón parar
const uint8_t botonPausar = 4; // pin para el botón pausar

uint8_t ultimoEstadoIniciar = LOW; // último estado booleano para iniciar
uint8_t ultimoEstadoParar = LOW; // último estado booleano para parar
uint8_t ultimoEstadoPausar = LOW; // último estado booleano para pausar

unsigned long iniciarMillis; // momento del inicio
unsigned long pararMillis; // momento de la parada
unsigned long pausarMillis; // momento del inicio de la pausa
unsigned long pausaTotalMillis; // tiempo total del la pausa combinada

unsigned long actualizacionAnteriorMillis; // para actualizar el tiempo de ejecución
const unsigned long intervaloActualizacion = 200;  // actualiza cada 200ms

void setup()
{
	Serial.begin(9600); // inicializar la comunicación serial
	
	pinMode(botonIniciar, INPUT); // pin botonIniciar en modo de entrada
	pinMode(botonParar, INPUT); // pin botonParar en modo de entrada
	pinMode(botonPausar, INPUT); // pin botonPausar en modo de entrada
	
	state = STATE_INIT; // inicializar la variable con STATE_INIT
}

void loop() {
	unsigned long actualMillis = millis(); // estado actual de millis()

	bool start = false; // inicializar variable start en false
	bool stop = false; // inicializar variable stop en false
	bool pause = false; // inicializar variable pause en false
	
	// ---------------------------------------------------
  	// Reúne toda la información de los botones y sensores
  	// ---------------------------------------------------
	uint8_t iniciarEstado = digitalRead(botonIniciar);
	uint8_t PararEstado = digitalRead(botonParar);
	uint8_t PausarEstado = digitalRead(botonPausar);
	
	// -----------------------------
  	// Detección de cambio de estado
  	// -----------------------------
	if (iniciarEstado != ultimoEstadoIniciar) {
		if (iniciarEstado == HIGH) {
			start = true;
		}
		
		ultimoEstadoIniciar = iniciarEstado;
	}
	
	if (PararEstado != ultimoEstadoParar) {
		if (PararEstado == HIGH) {
			stop = true;
		}
		
		ultimoEstadoParar = PararEstado;
	}
	
	if (PausarEstado != ultimoEstadoPausar) {
		if (PausarEstado == HIGH) {
			pause = true;
		}
		
		ultimoEstadoPausar = PausarEstado;
	}
	
	// --------------------------
  	// Máquina de estados finitos
  	// --------------------------
	switch(state) {
		case STATE_INIT:
			pausaTotalMillis = 0;
			Serial.println("Listo");
			state = STATE_WAIT_FOR_START;
			break;
		case STATE_WAIT_FOR_START:
			if (start) {
				iniciarMillis = actualMillis;
				Serial.println("Inicializado");
        	state = STATE_RUNNING;
			}
			break;
		case STATE_RUNNING:
			if (stop) {
				pararMillis = actualMillis;
				state = STATE_STOPPED;
			} else if (pause) {
				pausarMillis = actualMillis;
				Serial.println("Pausado");
				state = STATE_PAUSED;
			}
			break;
		case STATE_PAUSED:
			if (stop) {
				pararMillis = actualMillis;
				unsigned long tiempoTranscurridoPausa = actualMillis - pausarMillis;
        	pausaTotalMillis += tiempoTranscurridoPausa;
        	state = STATE_STOPPED;
			} else if (start || pause) {
				unsigned long tiempoTranscurridoPausa = actualMillis - pausarMillis;
        	pausaTotalMillis += tiempoTranscurridoPausa;
	        Serial.println("Continuar");
	        state = STATE_RUNNING;
			}
			break;
		case STATE_STOPPED:
     		unsigned long tiempoTranscurrido = pararMillis - iniciarMillis - pausaTotalMillis;
			Serial.println("Detenido.");
			Serial.print("Tiempo del cronometro: ");
			Serial.println(tiempoTranscurrido);
			Serial.print("(En pausa: ");
			Serial.print(pausaTotalMillis);
	
			unsigned long total = pararMillis - iniciarMillis;
			Serial.print(", Total: ");
			Serial.print(total);
			Serial.print(")");
			Serial.println();
	
			state = STATE_INIT;
			break;
	}
	
	// -------------------------------------------
  	// Muestra en el Serial el tiempo en ejecución
  	// -------------------------------------------
	if (state == STATE_RUNNING || state == STATE_PAUSED) {
		if ( actualMillis - actualizacionAnteriorMillis >= intervaloActualizacion)
    	{
	      actualizacionAnteriorMillis = actualMillis;
	
	      unsigned long tiempoTranscurridoHastaAhora;
	
	      if (state == STATE_PAUSED) {
	        tiempoTranscurridoHastaAhora = pausarMillis - iniciarMillis - pausaTotalMillis;
	      } else {
	        tiempoTranscurridoHastaAhora = actualMillis - iniciarMillis - pausaTotalMillis;
	      }
	
	      Serial.println(tiempoTranscurridoHastaAhora);
	    }
	}
}