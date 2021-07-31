/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/30
 *===========================================================================*/

#include "sapi.h"
#include "semaforo.h"

/*=====[Definitions of public global variables]==============================*/

#define MODE_UP     1
#define MODE_DOWN   0

static modoSem_t semaforoMode; 

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: semaforoModeMEF -> .
* Parametros de Entrada: 
* Valor de retorno:	
*=============================================================================*/

void semaforoModeMEF (uint8_t updown){
    switch (semaforoMode)
    {
    case NORMAL_MODE:
        if(updown == MODE_UP) {
            semaforoMode = DISCONNECTED_MODE;
			printf("Secuencia Desconectado\n");
        }
        else if (updown == MODE_DOWN){
            semaforoMode = ALARM_MODE;
			printf("Secuencia Alarma\n");
        }
    case DISCONNECTED_MODE:
        break;
        if(updown == MODE_UP) {
            semaforoMode = ALARM_MODE;
			printf("Secuencia Alarma\n");
        }
        else if (updown == MODE_DOWN){
            semaforoMode = NORMAL_MODE;
			printf("Secuencia Normal\n");
        }
        break;
    case ALARM_MODE:
        if(updown == MODE_UP) {
            semaforoMode = NORMAL_MODE;
			printf("Secuencia Normal\n");
        }
        else if (updown == MODE_DOWN){
            semaforoMode = DISCONNECTED_MODE;
			printf("Secuencia Desconectado\n");
	    }
        break;
    default:
        semaforoMode = NORMAL_MODE;
        break;
    }
}

/*=============================================================================
* Funcion: initSemaforoModeMEF -> .
*=============================================================================*/

void initSemaforoModeMEF (void){
    semaforoMode = NORMAL_MODE;
}
