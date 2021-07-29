/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/07
 *===========================================================================*/

#include "sapi.h"
#include "teclas.h"

/*=============================================================================
* Funcion: leerTecla -> Utilizada para leer teclas en la placa EDU CIAA.
* Parametros de Entrada: gpioMap_t tecla tipo de datos de sapi.h
* Valor de retorno:	ret_val -> 1 si la función se ejecutó correctamente * 0 si
* no fue pulsada una tecla permitida.	 	*
*=============================================================================*/

bool_t leerTecla (gpioMap_t tecla)
{
	bool_t ret_val;

   // Validacion de teclas presentes en la placa EDU CIAA.
   if ((tecla == TEC1) || (tecla == TEC2) || (tecla == TEC3) || (tecla == TEC4)) {
	   ret_val = gpioRead( tecla );
   }
   else {
   // No se puede leer ninguna tecla.
   ret_val     = 1;
   printf("\n Error: Se intentó presionar una tecla no permitida");
   }

	return ret_val;
}
