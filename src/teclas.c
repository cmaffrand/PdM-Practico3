/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/07
 *===========================================================================*/

#include "sapi.h"
#include "teclas.h"

/*=====[Definitions of public global variables]==============================*/

static estadoMEF_t estadoActual;
static delay_t DebounceNBD;

/*=============================================================================
* Funcion: leerTecla -> Utilizada para leer teclas en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t tecla tipo de datos de sapi.h
* Valor de retorno:	ret_val -> 1 si la función se ejecutó correctamente * 0 si
* no fue pulsada una tecla permitida.	 	*
*=============================================================================*/

bool_t leerTecla (gpioMap_t tecla)
{
	bool_t ret_val;
	static bool_t MEF_Init = TRUE;

	if(MEF_Init){
		inicializarMEF();
		MEF_Init = FALSE;
	}

   // Validacion de teclas presentes en la placa EDU CIAA.
   if ((tecla == TEC1) || (tecla == TEC2) || (tecla == TEC3) || (tecla == TEC4)) {
	   ret_val = actualizarMEF( tecla );
   }
   else {
   // No se puede leer ninguna tecla.
   ret_val     = 1;
   printf("\n Error: Se intentó presionar una tecla no permitida");
   }

	return ret_val;
}

/*=============================================================================
* Funcion: inicializarMEF -> .
*=============================================================================*/

void inicializarMEF (void)
{
	estadoActual = UP_STATE;
	delayInit( &DebounceNBD, DEBOUNCE_TIME);
}

/*=============================================================================
* Funcion: actualizarMEF -> .
* Parametros de Entrada: 
* Valor de retorno:	
*=============================================================================*/

bool_t actualizarMEF( gpioMap_t tecla )
{	
	bool_t ret_val = 1;
	bool_t instant_read;

	if (delayRead(&DebounceNBD) == TRUE) {
		delayInit( &DebounceNBD, DEBOUNCE_TIME);
		instant_read = gpioRead( tecla );
		switch (estadoActual)
		{
		case UP_STATE:
			if (instant_read == 0){
				estadoActual = FALLING_STATE;
			}
			break;
		case FALLING_STATE:
			if (instant_read == 0){
				estadoActual = DOWN_STATE;
				buttonPressed(tecla);
				ret_val = 0;
			}
			else estadoActual = UP_STATE;
			break;
		case DOWN_STATE:
			if (instant_read == 1){
				estadoActual = RISING_STATE;
			}
			break;
		case RISING_STATE:
			if (instant_read == 1){
				estadoActual = UP_STATE;
				buttonReleased(tecla);
			}
			else estadoActual = DOWN_STATE;
			break;
		
		default:
			estadoActual = UP_STATE;
			break;
		}
	}

	return ret_val;
}

void buttonPressed (gpioMap_t tecla){
	printf("Tecla presionada %s\n", tecla);
}

void buttonReleased (gpioMap_t tecla){
	printf("Tecla soltada %s\n", tecla);
}






