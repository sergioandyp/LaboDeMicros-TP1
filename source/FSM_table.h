/*******************************************************************************
  @file     +FSM_table.h+
  @brief    +Tabla de estados de la maquina de estados+
  @author   +Grupo 3+
 ******************************************************************************/

#ifndef FSM_TABLE_H
#define FSM_TABLE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "FSM_routines.h"
#include "event_queue/event_queue.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 *******************************************************************************/
typedef struct state_diagram_edge STATE;
struct state_diagram_edge{
    event_t evento;
	//Evento que activa la rutina de acción

    STATE *proximo_estado;
    // Puntero que apunta al estado al que hay que ir en caso
    //que se cumpla el evento correspondiente. 

    void (*p_rut_accion)(void);
    // Función a realizar durante la transición entre un estado y otro.
};

STATE *fsm_interprete(STATE * p_tabla_estado_actual, event_t evento_actual);

extern STATE ID_state[];
STATE ID_show[]; 
extern STATE brillo_state[];
extern STATE IDError_state[];
extern STATE Pass_state[];
extern STATE PassError_state[];
extern STATE changePass_state[];
extern STATE addID_state[];
extern STATE addError_state[];
extern STATE addPass_state[];
extern STATE delUser_state[];
extern STATE AdminMenu_state[];
extern STATE UserMenu_state[];
extern STATE changePassA_state[];

STATE ID_state[] = {
    {ENCODER_LONG, brillo_state, brillo_init},          
    {ENCODER_LEFT, ID_state, previous_id},
    {ENCODER_RIGHT, ID_state, upper_id}, 
    {ENCODER_PRESS, ID_state, next_id}, 
    {ID_READY, ID_show, setIDTimer},
    {TIMEOUT, ID_state, id_init},
    {NULL_EVENT, ID_state, doNothing}
};  

STATE ID_show[] = {
    {TIMEOUT, ID_show, check_id},          
    {WRONG_ID, IDError_state, errorScreen},     
    {ID_OK, Pass_state, pass_init},
    {NULL_EVENT, ID_state, doNothing}
}; 

STATE brillo_state[] = {
    {ENCODER_LEFT, brillo_state, dec_bright},  
    {ENCODER_RIGHT, brillo_state, inc_bright},
    {ENCODER_PRESS, ID_state, id_init}, 
    {NULL_EVENT, brillo_state, doNothing}
};

STATE IDError_state[] = {
    {ENCODER_PRESS, ID_state, id_init},
    {NULL_EVENT, IDError_state, doNothing}
};

STATE Pass_state[] = {
    {ENCODER_LEFT, Pass_state, previous_pass}, 
    {ENCODER_RIGHT, Pass_state, upper_pass}, 
    {ENCODER_PRESS, Pass_state, next_pass}, 
    {ENCODER_LONG, Pass_state, check_pass},
    {WRONG_PASS, PassError_state, errorScreen},
    {ADMIN_USER, AdminMenu_state, init_admin_menu},
    {NORMAL_USER, UserMenu_state, init_menu},
    {BACK, ID_state, id_init}, 
    {TIMEOUT, Pass_state, pass_init},
    {NULL_EVENT, Pass_state, doNothing}
};

STATE PassError_state[] = {
    {ENCODER_PRESS, Pass_state, pass_init},
    {NULL_EVENT, PassError_state, doNothing}
};

STATE AdminMenu_state[] = {
    {ENCODER_LEFT, AdminMenu_state, up_menu_Admin},       
    {ENCODER_RIGHT, AdminMenu_state, down_menu_Admin},    
    {ENCODER_PRESS, AdminMenu_state, click_menu_Admin},      
    {CHNG_PASS, changePass_state, pass_init},
    {ADD_USER, addID_state, id_init},
    {DEL_USER, delUser_state, list_init},
    {BACK, ID_state, id_init},
    {NULL_EVENT, AdminMenu_state, doNothing}
};

STATE changePassA_state[] = {
    {ENCODER_LEFT, changePassA_state, previous_pass}, 
    {ENCODER_RIGHT, changePassA_state, upper_pass},
    {ENCODER_PRESS, changePassA_state, next_pass}, 
    {ENCODER_LONG, AdminMenu_state, init_admin_menu},
    {PASS_READY, AdminMenu_state, save_pass},
    {BACK, AdminMenu_state, init_admin_menu},
    {NULL_EVENT, changePassA_state, doNothing}
};

STATE addID_state[] = {
    {ENCODER_LEFT, addID_state, previous_pass},
    {ENCODER_RIGHT, addID_state, upper_pass}, 
    {ENCODER_PRESS, addID_state, next_pass}, 
    {ENCODER_LONG, AdminMenu_state, init_admin_menu},
    {ID_READY, addID_state, used_id},   
    {WRONG_ID, addError_state, errorScreen},     
    {ID_OK, addPass_state, pass_init},
    {NULL_EVENT, addID_state, doNothing}
};

STATE addError_state[] = {
    {ENCODER_PRESS, addID_state, id_init},
    {NULL_EVENT, addError_state, doNothing}
};

STATE addPass_state[] = {
    {ENCODER_LEFT, addPass_state, previous_pass},  
    {ENCODER_RIGHT, addPass_state, upper_pass}, 
    {ENCODER_PRESS, addPass_state, next_pass}, 
    {ENCODER_LONG, AdminMenu_state, init_admin_menu},
    {PASS_READY, Pass_state, add_user},          
    {BACK, AdminMenu_state, init_admin_menu},
    {NULL_EVENT, addPass_state, doNothing}
};

STATE delUser_state[] = {
    {ENCODER_LEFT, delUser_state, up_menu_del},    
    {ENCODER_RIGHT, delUser_state, down_menu_del}, 
    {ENCODER_PRESS, delUser_state, del_user},        
    {BACK, UserMenu_state, init_menu},
    {NULL_EVENT, delUser_state, doNothing}
};

STATE UserMenu_state[] = {
    {ENCODER_LEFT, UserMenu_state, up_menu},      
    {ENCODER_RIGHT, UserMenu_state, down_menu},   
    {ENCODER_PRESS, UserMenu_state, click_menu},  
    {CHNG_PASS, changePass_state, pass_init},
    {BACK, ID_state, id_init},
    {NULL_EVENT, UserMenu_state, doNothing}
};

STATE changePass_state[] = {
    {ENCODER_LEFT, changePass_state, previous_pass},
    {ENCODER_RIGHT, changePass_state, upper_pass},
    {ENCODER_PRESS, changePass_state, next_pass}, 
    {ENCODER_LONG, UserMenu_state, init_menu},
    {PASS_READY, Pass_state, save_pass},
    {BACK, UserMenu_state, init_menu},
    {NULL_EVENT, changePassA_state, doNothing}
};

/*******************************************************************************
 ******************************************************************************/

#endif // FSM_table_H