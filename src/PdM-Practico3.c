/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/30
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

	//Inicializacion de estructuras de teclas
	tecla1.tecla = TEC1;
	tecla2.tecla = TEC2;
	tecla3.tecla = TEC3;
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
		// Polling de botones.
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

	return 0;
}
