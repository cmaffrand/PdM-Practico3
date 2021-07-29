/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/09
 *===========================================================================*/

#include "sapi.h"
#include "led.h"
#include "secuencia.h"

/*=============================================================================
* Funcion: activarSecuencia -> Utilizada para generar el cambio de estado en los
* leds en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t* secuencia, puntero a tipo de datos de sapi.h
* y bool_t dirValue, define el sentido de cambio de estados.
* Valor de retorno:	void
*=============================================================================*/

void activarSecuencia(gpioMap_t * psecuencia, bool_t dirValue, tick_t * ptiempos) {

	static uint8_t estado = 0;

	// Evaluación del estado de la secuencia, observando la dirección.
	if (dirValue == FALSE) {
		// Rotacion a la derecha
		estado++;
		if (estado > ultimoLed-1)  estado = 0;
   }
   else {
	   // Rotacion a la izquierda
	   estado--;
	   if (estado > ultimoLed-1) estado = ultimoLed-1;
   }

	// Se reinicia el retardo no bloqueante con el tiempo asignado al led correspondiente
	delayInit( &NonBlockingDelay, ptiempos[estado] );

   //  Chequeo y llamado de funciones sobre leds
   if (!(apagarLeds())) {
	   printf("\n Error: Secuencia Detenida");
	   while(true){}
   }
   if (!(encenderLed(psecuencia[estado]))) {
	   printf("\n Error:Secuencia Detenida");
	   while(true){}
   }
}
