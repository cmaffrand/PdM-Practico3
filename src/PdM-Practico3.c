/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/07
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "PdM-Practico3.h"
#include "sapi.h"
#include "teclas.h"
#include "led.h"
#include "secuencia.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

uint8_t ultimoLed;
delay_t NonBlockingDelay;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
	 // Inicializar y configurar la plataforma
	   boardConfig();

	   //Secuencias
	   gpioMap_t semaforo_normal[] 			= {LED1, LED2, LED1, LED3};
	   gpioMap_t semaforo_desconectado[] 	= {LED_OFF, LED1};
	   gpioMap_t semaforo_alarma[] 			= {LED_OFF, LED2};
	   tick_t tiempos_normal[]				= {500, 3000, 500, 1000};
	   tick_t tiempos_desconectado[]		= {500, 500};
	   tick_t tiempos_alarma[]				= {1000, 1000};

	   // Inicializar las variables y estructuras del retardo no bloqueante.
	   delayInit( &NonBlockingDelay, tiempos_normal[0]);

	   // Crear varias variables
	   gpioMap_t * psecuencia 	= semaforo_normal;
	   bool_t camSecFlag    	= FALSE; // bandera "debounce"
	   tick_t * ptiempos 		= tiempos_normal;
	   uint8_t selecSecuencia 	= 0;



   // Mensaje de inició del programa
   printf("Secuencia Comenzada\n");
   printf("Secuencia Normal\n");
   ultimoLed = sizeof(semaforo_normal)/sizeof(gpioMap_t);
   // ----- Repeat for ever -------------------------
   while( true ) {

	   // Chequeo del delay no bloquenate.
	   if (delayRead(&NonBlockingDelay) == TRUE) {
		   // Selección de la secuencia
		   if (selecSecuencia == 0) {
			   psecuencia 	= semaforo_normal;
			   ptiempos 	= tiempos_normal;
			   ultimoLed 	= sizeof(semaforo_normal)/sizeof(gpioMap_t);			   
		   }
		   else if (selecSecuencia == 1) {
			   psecuencia 	= semaforo_desconectado;
			   ptiempos 	= tiempos_desconectado;
			   ultimoLed 	= sizeof(semaforo_desconectado)/sizeof(gpioMap_t);
		   }
		   else {
			   psecuencia 	= semaforo_alarma;
			   ptiempos 	= tiempos_alarma;
			   ultimoLed 	= sizeof(semaforo_alarma)/sizeof(gpioMap_t);
		   }
		   // Ejecución de la secuencia.
		   activarSecuencia(psecuencia, TRUE, ptiempos);
		}
	   // Si no se cumple el delay pooling de botones.
		 else {
			if (leerTecla( TEC2 ) == OFF) {
				selecSecuencia++;
				if (selecSecuencia >= 3) selecSecuencia = 0;
				switch (selecSecuencia)
				{
				case 0:
					printf("Secuencia Normal\n");
					break;
				case 1:
					printf("Secuencia Desconectado\n");
					break;
				case 2:
			    	printf("Secuencia Alarma\n");
					break;
				default:
					break;
				}
			}
		 }
   }
   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
