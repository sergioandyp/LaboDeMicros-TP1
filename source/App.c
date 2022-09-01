/***************************************************************************//**
  @file     App.c
  @brief    TP!: Access Control
  @author   Sergio Peralta
 ******************************************************************************/

/*
	1- Habria que checkear que haya lugares libres antes de cargar el id para
	agregar el usuario
	2- Agregar admins?
	3- Mostrar ID cuando se agregan usuarios con la tarjeta
	4- Penalizaciones por mal ingreso de passwords
*/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "const.h"
#include "FSM_table.h"
#include "FSM_routines.h"
#include "userDatabase.h"
#include "event_queue/event_queue.h"
#include "display/dispArr.h"
#include "magtek/MagtekWrapper.h"
#include "encoder_hal.h"
#include "LEDMux/LEDMux.h"
#include "timer/timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        	GLOBAL VARIABLES
 *******************************************************************************
 ******************************************************************************/
static STATE* p_tabla_estado_actual;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	timerInit();
	Card2Init(IDcardCb);
	encoderInit(encoderCallback);
	LEDMuxInit();
	dispArrInit();
	init_Database();

	p_tabla_estado_actual = ID_state;
	id_init();
	setUpIDTimer();
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	event_t evento = get_next_event();  // Tomo un nuevo evento de la cola de eventos.
	p_tabla_estado_actual = fsm_interprete(p_tabla_estado_actual, evento);  // Actualizo el estado
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

STATE *fsm_interprete(STATE * p_tabla_estado_actual, event_t evento_actual)
{
    while ((p_tabla_estado_actual -> evento) != evento_actual && (p_tabla_estado_actual -> evento) !=NULL_EVENT){
        ++p_tabla_estado_actual;
    } 

    (p_tabla_estado_actual -> p_rut_accion) (); // Ejecuta Rutina de accion correspondiente
    p_tabla_estado_actual = (p_tabla_estado_actual -> proximo_estado); // Encuentro próximo estado
    return (p_tabla_estado_actual);    
}

/*******************************************************************************
 ******************************************************************************/
