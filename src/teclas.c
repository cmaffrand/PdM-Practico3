/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/07
 *===========================================================================*/

#include "sapi.h"
#include "teclas.h"

/*=====[Definitions of public global variables]==============================*/

/*=============================================================================
* Funcion: leerTecla -> Utilizada para leer teclas en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t tecla tipo de datos de sapi.h
* Valor de retorno:	ret_val -> 1 si la función se ejecutó correctamente * 0 si
* no fue pulsada una tecla permitida.	 	*
*=============================================================================*/

bool_t leerTecla (dbn_t * ptecla)
{
	bool_t ret_val;
	static bool_t MEF_Init = TRUE;

	if(MEF_Init){
		inicializarMEF(ptecla);
		MEF_Init = FALSE;
	}

   // Validacion de teclas presentes en la placa EDU CIAA.
   if ((ptecla->tecla == TEC1) || (ptecla->tecla == TEC2) || (ptecla->tecla == TEC3) || (ptecla->tecla == TEC4)) {
	   ret_val = actualizarMEF( ptecla );
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

void inicializarMEF (dbn_t * ptecla)
{
	ptecla->estado = UP_STATE;
	delayInit( &(ptecla->delay), DEBOUNCE_TIME);
}

/*=============================================================================
* Funcion: actualizarMEF -> .
* Parametros de Entrada: 
* Valor de retorno:	
*=============================================================================*/

bool_t actualizarMEF( dbn_t * ptecla )
{	
	bool_t ret_val = 1;
	bool_t instant_read;

	if (delayRead(&(ptecla->delay)) == TRUE) {
		delayInit( &(ptecla->delay), DEBOUNCE_TIME);
		instant_read = gpioRead( ptecla->tecla );
		switch (ptecla->estado)
		{
		case UP_STATE:
			if (instant_read == 0){
				ptecla->estado = FALLING_STATE;
			}
			break;
		case FALLING_STATE:
			if (instant_read == 0){
				ptecla->estado = DOWN_STATE;
				buttonPressed(ptecla->tecla);
				ret_val = 0;
			}
			else ptecla->estado = UP_STATE;
			break;
		case DOWN_STATE:
			if (instant_read == 1){
				ptecla->estado = RISING_STATE;
			}
			break;
		case RISING_STATE:
			if (instant_read == 1){
				ptecla->estado = UP_STATE;
				buttonReleased(ptecla->tecla);
			}
			else ptecla->estado = DOWN_STATE;
			break;
		
		default:
			ptecla->estado = UP_STATE;
			break;
		}
	}

	return ret_val;
}

void buttonPressed (gpioMap_t tecla){
	printf("Tecla presionada TEC%d \n", tecla-35);
}

void buttonReleased (gpioMap_t tecla){
	printf("Tecla soltada TEC%d \n", tecla-35);
}
