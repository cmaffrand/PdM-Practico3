/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/07
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "PdM-Practico3.h"
#include "sapi.h"
#include "teclas.h"
#include "semaforo.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void)
{
	// Inicializar y configurar la plataforma
	boardConfig();

	//teclas
	dbn_t tecla1;
	tecla1.tecla = TEC1;
	dbn_t tecla2;
	tecla2.tecla = TEC2;
	dbn_t tecla3;
	tecla3.tecla = TEC3;
	dbn_t tecla4;
	tecla4.tecla = TEC4;

	// Punteros de teclas
	dbn_t *ptecla1 = &tecla1;
	dbn_t *ptecla2 = &tecla2;
	dbn_t *ptecla3 = &tecla3;
	dbn_t *ptecla4 = &tecla4;

	initSemaforoModeMEF();

	// ----- Repeat for ever -------------------------
	while (true)
	{
		// Pooling de botones.
		if (leerTecla(ptecla1) == OFF)
		{
			// Poner funcionalidad de tecla 1.
		}
		if (leerTecla(ptecla2) == OFF)
		{
			semaforoModeMEF(MODE_UP);
		}
		if (leerTecla(ptecla3) == OFF)
		{
			semaforoModeMEF(MODE_DOWN);
		}
		if (leerTecla(ptecla4) == OFF)
		{
			// Poner funcionalidad de tecla 4.
		}
		// Lammado a la MEF de manejo de estados del semaforo
		semaforoStateMEF();
	}
	// YOU NEVER REACH HERE, because this program runs directly or on a
	// microcontroller and is not called by any Operating System, as in the
	// case of a PC program.
	return 0;
}
