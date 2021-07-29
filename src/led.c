/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/09
 *===========================================================================*/

#include "sapi.h"
#include "led.h"

/*=============================================================================
* Funcion: encenderLed -> Utilizada para encender leds en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t led, tipo de datos de sapi.h
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente.
* 							-> FALSE si no se pudo encender el led.
*=============================================================================*/

bool_t encenderLed( gpioMap_t led )
{
   bool_t ret_val     = 1;

   // Chequeo de los valores de LEDs presentes en la EDU CIAA.
   if ((led == LEDR) || (led == LEDG) || (led == LEDB) || (led == LED1) || (led == LED2) || (led == LED3)) {
	   gpioWrite( led, 1 );
   }
   // Este es un led inexistente en la placa, para generar un estado donde
   // todos los leds están apagados.
   else if (led == LED_OFF) ret_val     = 1;
   else {
	   // No se puede encender ningun led.
	   ret_val     = 0;
	   printf("\n Error: Se intentó encender un led no permitido");
	   }

   return ret_val;
}

/*=============================================================================
* Funcion: apagarLeds -> Utilizada para apagar todos los leds de la placa EDU CIAA.
* Parametros de Entrada:  void
* Valor de retorno:	ret_val -> TRUE si la función se ejecutó correctamente
*=============================================================================*/

bool_t apagarLeds(void)
{
   bool_t ret_val     = 1;

	gpioWrite( LEDB, 0 );
	gpioWrite( LED1, 0 );
	gpioWrite( LED2, 0 );
	gpioWrite( LED3, 0 );

   return ret_val;
}

