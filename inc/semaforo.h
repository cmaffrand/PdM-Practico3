/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/30
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __SEMAFORO_H__
#define __SEMAFORO_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

	/*=====[Definition macros of public constants]===============================*/

#define MODE_UP 1
#define MODE_DOWN 0
#define DELAY_ROJO_NORMAL 3000
#define DELAY_ROJOAMA_NORMAL 500
#define DELAY_VERDE_NORMAL 1000
#define DELAY_AMARILLO_NORMAL 500
#define DELAY_AMARILLO_DESC 500
#define DELAY_OFF_DESC 500
#define DELAY_ROJO_ALARMA 1000
#define DELAY_OFF_ALARMA 1000

	/*=====[Public function-like macros]=========================================*/

	/*=====[Definitions of public data types]====================================*/

	typedef enum
	{
		RED_STATE,
		REDYELLOW_STATE,
		GREEN_STATE,
		YELLOW_STATE,
		OFF_STATE
	} estadoSem_t;

	estadoSem_t semaforoState;

	typedef enum
	{
		NORMAL_MODE,
		DISCONNECTED_MODE,
		ALARM_MODE
	} modoSem_t;

	modoSem_t semaforoMode;

	/*=====[Prototypes (declarations) of public functions]=======================*/

	void initSemaforoModeMEF(void);
	void semaforoModeMEF(bool_t updown);
	void initSemaforoStateMEF(void);
	void semaforoStateMEF(void);

	/*=====[Prototypes (declarations) of public interrupt functions]=============*/

	/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SEMAFORO_H__ */
