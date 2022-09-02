/***************************************************************************//**
  @file     +MagtekWrapper.c+
  @brief    +Mangetic stripe wrapper for 8 digit Id+
  @author   +Group 5+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "MagtekWrapper.h"
#include <string.h>
#include <stdlib.h>
#include "Magtek.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

# define ID_SIZE 8

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void new_callback (bool state, const data* data);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static WrapperCardCb newMainCb;
static char newId[ID_SIZE+1];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
bool Card2Init(WrapperCardCb funCb){
	if (funCb==NULL)
		return false;
	CardInit(new_callback);
	newMainCb=funCb;
	return true;
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void new_callback (bool state, const data* data){
	if (state==true){
		if (strlen(data->id)>ID_SIZE){
			memcpy(newId, data->id+(strlen(data->id)-ID_SIZE)*sizeof(char),ID_SIZE);		//If ID > N characters, save the last N ones
		}
		else{
			memcpy(newId, data->id,ID_SIZE);
		}
		newId[ID_SIZE]='\0';
		if(strlen(newId)!=ID_SIZE){										//if ID < N characters, complete with '0'
			for (int i = strlen(newId); i < ID_SIZE; i++) {								
				newId[i]='0';
			}
		}
		newMainCb(state, newId);
	}
	else
		newMainCb(state, NULL);
}
