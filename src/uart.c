/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/31
 *===========================================================================*/

#include "sapi.h"
#include "teclas.h"
#include "semaforo.h"
#include <string.h>

/*=====[Definitions of public global variables]==============================*/

/*=============================================================================
* Funcion: displaySemaforo -> Muestra por consola los estados y modos del
* semaforo y las teclas.
*=============================================================================*/

void displaySemaforo(void)
{
	char mensajeModo[20];
	char mensajeEstado[20];
	char mensajeEstadoTecla1[20];
	char mensajeEstadoTecla2[20];
	char mensajeEstadoTecla3[20];
	char mensajeEstadoTecla4[20];

	//se genera el mensaje de modo del semaforo
	switch (semaforoMode){
	case NORMAL_MODE:
		strcpy(mensajeModo,"NORMAL_MODE");
		break;
	case DISCONNECTED_MODE:
		strcpy(mensajeModo,"DISCONNECTED_MODE");
		break;
	case ALARM_MODE:
		strcpy(mensajeModo,"ALARM_MODE");
		break;
	default:
		break;
	}

	//se genera el mensaje de estado del semaforo
	switch (semaforoState){
		case RED_STATE:
			strcpy(mensajeEstado,"RED_STATE");
			break;
		case REDYELLOW_STATE:
			strcpy(mensajeEstado,"REDYELLOW_STATE");
			break;
		case GREEN_STATE:
			strcpy(mensajeEstado,"GREEN_STATE");
			break;
		case YELLOW_STATE:
			strcpy(mensajeEstado,"YELLOW_STATE");
			break;
		case OFF_STATE:
			strcpy(mensajeEstado,"OFF_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 1
	switch (tecla1.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla1,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla1,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla1,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla1,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 2
	switch (tecla2.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla2,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla2,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla2,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla2,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 3
	switch (tecla3.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla3,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla3,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla3,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla3,"RISING_STATE");
			break;
		default:
			break;
		}

	//se genera el mensaje de estado de la tecla 4
	switch (tecla4.estado){
		case UP_STATE:
			strcpy(mensajeEstadoTecla4,"UP_STATE");
			break;
		case DOWN_STATE:
			strcpy(mensajeEstadoTecla4,"DOWN_STATE");
			break;
		case FALLING_STATE:
			strcpy(mensajeEstadoTecla4,"FALLING_STATE");
			break;
		case RISING_STATE:
			strcpy(mensajeEstadoTecla4,"RISING_STATE");
			break;
		default:
			break;
		}

	//se borra pantalla
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[2J" );   // Clear screen command
	uartWriteByte(   UART_USB, 27    );   // ESC command
	uartWriteString( UART_USB, "[H"  );   // Cursor to home command

	//se imprime el mensaje
	printf("Modo actual: %s\r\n",mensajeModo);
	printf("Estado actual: %s\r\n",mensajeEstado);
	printf("Tecla %d: %s\r\n",tecla1.tecla - 35,mensajeEstadoTecla1);
	printf("Tecla %d: %s\r\n",tecla2.tecla - 35,mensajeEstadoTecla2);
	printf("Tecla %d: %s\r\n",tecla3.tecla - 35,mensajeEstadoTecla3);
	printf("Tecla %d: %s\r\n",tecla4.tecla - 35,mensajeEstadoTecla4);

}
