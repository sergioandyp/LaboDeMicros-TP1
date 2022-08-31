/***************************************************************************//**
  @file		dispTest.c
  @brieef	Testbench para las funciones de dispArr
  @author	Sergio Peralta
  @date		30 ago. 2022
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "dispArr.h"
#include "board.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void nextMode();

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	dispArrInit();
	gpioMode(PIN_SW3, SW3_INPUT_TYPE);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{

	if (gpioRead(PIN_SW3) == SW_ACTIVE) {
		while(gpioRead(PIN_SW3) == SW_ACTIVE);
		nextMode();
	}

}

void nextMode() {

	static uint8_t mode = 0;

	switch (mode) {

	case 0:
		dispArrShow("Hola");
		break;

	case 1:
		dispArrShow("Mensaje largo");
		break;

	case 2:
		dispArrShowForTime("Hola", 5000);
		break;

	case 3:
		dispArrShowForTime("Mensaje largo", 3500);
		break;

	case 4:
		dispArrShowNum(12);
		break;

	case 5:
		dispArrShowNum(1234);
		break;

	case 6:
		dispArrShowNum(12345678);
		break;

	case 7:
		dispArrSlideOnce("Un texto bastante largo");		// no paso
		break;

	case 8:
		dispArrSlideOnce("Hola");				// no paso
		break;

	case 9:
		dispArrSlideLoop("Un texto bastante largo");	// no paso
		break;

	case 10:
		dispArrSlideLoop("Hola");		// no paso
		break;

	case 11:
	case 12:
	case 13:
	case 14:
		dispArrShowSelect("Hola", mode-11);
		break;

	case 15:
		dispArrShowSelect("Hola", 4);		// no paso
		break;

	case 16:
	case 17:
	case 18:
	case 19:
		dispArrShowSelect("Mensaje largo", mode-16);
		break;

	case 20:
		dispArrShowSelect("Mensaje largo", 5);		// no paso
		break;

	case 21:
	case 22:
	case 23:
	case 24:
		dispArrBlink("Hola", mode-21);
		break;

	case 25:
		dispArrBlink("Hola", 4);			// no pasa
		break;

	case 26:
	case 27:
	case 28:
	case 29:
		dispArrBlink("Mensaje largo", mode-26);
		break;

	case 30:
		dispArrBlink("Mensaje largo", 10);		// no paso
		break;

	case 31:
		dispArrClear();
		break;

	}

	if (mode > 31) {
		dispArrSetBright(mode-35);
		dispArrShowNum(dispArrGetBright());
	}

	mode++;

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



 