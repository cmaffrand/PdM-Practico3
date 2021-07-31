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
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef enum{
	    RED_STATE,
	    REDYELLOW_STATE,
	    GREEN_STATE,
	    YELLOW_STATE,
	    OFF_STATE
	} estadoSem_t;

typedef enum{
	    NORMAL_MODE,
	    DISCONNECTED_MODE,
	    ALARM_MODE
	} modoSem_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void initSemaforoModeMEF (void);
void semaforoModeMEF (uint8_t updown);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SEMAFORO_H__ */
