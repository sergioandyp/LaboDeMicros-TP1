/***************************************************************************//**
  @file     gpio.h
  @brief    Simple GPIO Pin services, similar to Arduino
  @author   Nicolas Magliola
 ******************************************************************************/

#ifndef _DATABASE_H_
#define _DATABASE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <const.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Arranca la lista de usuarios para saber cual borrar
*/
void list_init();

/**
 * @brief subimos en el menú de borrado
*/
void up_menu_del();

/**
 * @brief bajamos en el menú de borrado
*/
void down_menu_del(); 

/**
 * @brief borramos el usuario
*/
void del_user();

/**
 * @brief checkea que el usuario exista en la database
*/
bool internal_check_id(uint8_t * id);

/**
 * @brief checkea que la contraseña corresponda al usuario
*/
bool internal_check_pass(uint8_t * id, uint8_t * password);

/**
 * @brief checkea si el id ya existe
*/
void internal_used_id(uint8_t * id);

/**
 * @brief Guarda la password en la base de datos
*/
bool internal_save_pass(uint8_t * id, uint8_t * password);

/**
 * @brief Carga el usuario en la base de datos
*/
bool internal_add_user(uint8_t * id, uint8_t * pass);
/*******************************************************************************
 ******************************************************************************/

#endif // _DATABASE_H_