/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/30
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __TECLAS_H__
#define __TECLAS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

	/*=====[Definition macros of public constants]===============================*/

#define DEBOUNCE_TIME 20

	/*=====[Public function-like macros]=========================================*/

	/*=====[Definitions of public data types]====================================*/

	typedef enum
	{
		UP_STATE,
		DOWN_STATE,
		FALLING_STATE,
		RISING_STATE
	} estadoMEF_t;

	typedef struct
	{ // estructura para controlar el antirrebote de un tecla
		gpioMap_t tecla;
		delay_t delay;
		estadoMEF_t estado;
	} dbn_t;

	dbn_t tecla1;
	dbn_t tecla2;
	dbn_t tecla3;
	dbn_t tecla4;

	/*=====[Prototypes (declarations) of public functions]=======================*/

	bool_t leerTecla(dbn_t *ptecla);
	void inicializarMEF(dbn_t *ptecla);
	bool_t actualizarMEF(dbn_t *ptecla);
	void buttonPressed(gpioMap_t tecla);
	void buttonReleased(gpioMap_t tecla);

	/*=====[Prototypes (declarations) of public interrupt functions]=============*/

	/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __TECLAS_H__ */
