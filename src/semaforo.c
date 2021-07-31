/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/30
 *===========================================================================*/

#include "sapi.h"
#include "led.h"
#include "semaforo.h"
#include "uart.h"

/*=====[Definitions of public global variables]==============================*/

static delay_t SemaforoNBD;

/*=====[Definitions of functions]==============================*/

/*=============================================================================
* Funcion: semaforoModeMEF -> Maquina de estado finito que maneja los modos del
* semaforo.
* Parametros de Entrada: bool_t updown -> cambio a siguiente o anterior.
*=============================================================================*/

void semaforoModeMEF(bool_t updown)
{
    switch (semaforoMode)
    {
    case NORMAL_MODE:
        if (updown == MODE_UP)
        {
            semaforoMode = DISCONNECTED_MODE;
            semaforoState = OFF_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Desconectado\n");
        }
        else if (updown == MODE_DOWN)
        {
            semaforoMode = ALARM_MODE;
            semaforoState = OFF_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Alarma\n");
        }
        break;
    case DISCONNECTED_MODE:
        if (updown == MODE_UP)
        {
            semaforoMode = ALARM_MODE;
            semaforoState = OFF_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Alarma\n");
        }
        else if (updown == MODE_DOWN)
        {
            semaforoMode = NORMAL_MODE;
            semaforoState = YELLOW_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Normal\n");
        }
        break;
    case ALARM_MODE:
        if (updown == MODE_UP)
        {
            semaforoMode = NORMAL_MODE;
            semaforoState = YELLOW_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Normal\n");
        }
        else if (updown == MODE_DOWN)
        {
            semaforoMode = DISCONNECTED_MODE;
            semaforoState = OFF_STATE;
            delayInit(&SemaforoNBD, 0);
            printf("Secuencia Desconectado\n");
        }
        break;
    default:
        semaforoMode = NORMAL_MODE;
        semaforoState = YELLOW_STATE;
        delayInit(&SemaforoNBD, 0);
        printf("Error de Secuencia\n");
        break;
    }
}

/*=============================================================================
* Funcion: initSemaforoModeMEF -> Inicializa el semaforo en modo normal
*=============================================================================*/

void initSemaforoModeMEF(void)
{
    semaforoMode = NORMAL_MODE;
    displaySemaforo();
    initSemaforoStateMEF();
}

/*=============================================================================
* Funcion: initSemaforoState MEF -> Se inicializa en el ultimo estado de modo
* normal, para que dispare un cambio y arranque en el primer estado (RED_STATE).
*=============================================================================*/

void initSemaforoStateMEF(void)
{
    semaforoState = YELLOW_STATE;
    //printf("Semaforo Rojo\n");
    // Inicializar retardo no bloqueante.
    delayInit(&SemaforoNBD, 0);
}

/*=============================================================================
* Funcion: semaforoStateMEF -> Maquina de estado finito que maneja los estados
* del semaforo. Los cambios de estado dependen del temporizado.
*=============================================================================*/

void semaforoStateMEF(void)
{
    // Chequeo del delay no bloquenate.
    if (delayRead(&SemaforoNBD) == TRUE)
    {
        // Selección del estado
        if (semaforoMode == NORMAL_MODE)
        {
            switch (semaforoState)
            {
            case RED_STATE:
                semaforoState = REDYELLOW_STATE;
                apagarLeds();
                encenderLed(LED1);
                encenderLed(LED2);
                delayInit(&SemaforoNBD, DELAY_ROJOAMA_NORMAL);
                break;
            case REDYELLOW_STATE:
                semaforoState = GREEN_STATE;
                apagarLeds();
                encenderLed(LED3);
                delayInit(&SemaforoNBD, DELAY_VERDE_NORMAL);
                break;
            case GREEN_STATE:
                semaforoState = YELLOW_STATE;
                apagarLeds();
                encenderLed(LED1);
                delayInit(&SemaforoNBD, DELAY_AMARILLO_NORMAL);
                break;
            case YELLOW_STATE:
                semaforoState = RED_STATE;
                apagarLeds();
                encenderLed(LED2);
                delayInit(&SemaforoNBD, DELAY_ROJO_NORMAL);
                break;
            default:
                semaforoState = RED_STATE;
                apagarLeds();
                encenderLed(LED2);
                delayInit(&SemaforoNBD, DELAY_ROJO_NORMAL);
                break;
            }
        }
        else if (semaforoMode == DISCONNECTED_MODE)
        {
            switch (semaforoState)
            {
            case OFF_STATE:
                semaforoState = YELLOW_STATE;
                apagarLeds();
                encenderLed(LED1);
                delayInit(&SemaforoNBD, DELAY_AMARILLO_DESC);
                break;
            case YELLOW_STATE:
                semaforoState = OFF_STATE;
                apagarLeds();
                delayInit(&SemaforoNBD, DELAY_OFF_DESC);
                break;
            default:
                semaforoState = OFF_STATE;
                apagarLeds();
                delayInit(&SemaforoNBD, DELAY_OFF_DESC);
                break;
            }
        }
        else if (semaforoMode == ALARM_MODE)
        {
            switch (semaforoState)
            {
            case OFF_STATE:
                semaforoState = RED_STATE;
                apagarLeds();
                encenderLed(LED2);
                delayInit(&SemaforoNBD, DELAY_ROJO_ALARMA);
                break;
            case RED_STATE:
                semaforoState = OFF_STATE;
                apagarLeds();
                delayInit(&SemaforoNBD, DELAY_OFF_ALARMA);
                break;
            default:
                semaforoState = OFF_STATE;
                apagarLeds();
                delayInit(&SemaforoNBD, DELAY_OFF_ALARMA);
                break;
            }
        }
        displaySemaforo();
    }
}
