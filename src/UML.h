#ifndef UML_H
#define UML_H

// Definir los estados
typedef enum
{
    START,
    DOS,
    TRES
} estados_names_t;

typedef enum {
    TRES_UNO,
    TRES_DOS
} estados_son_names_t;

//******* Agreados ******
typedef enum{
    PARENT,
    SON,
    SON_EXIT,
} hierarchical_t; 


// Definir las señales principales
typedef enum
{
    A = 97,
    B,
    C,
    ENTRY,
    EXIT
} signal_t;

// Definir las variables a trabajar
typedef struct
{
    String msg;
    estados_son_names_t activate_state_son;
    hierarchical_t level;
    estados_names_t activate_state;
} obj_msg_t;

typedef enum
{
    event_realizado,
    evento_ignorad,
    transicion_evento,
    transicion_evento_hijo
} event_status;

// Definir el evento
typedef struct
{
    uint8_t state; // Aca se almacena el valor de las señales
} event_t;

void init_state(obj_msg_t *);
event_status State_machine(obj_msg_t *obj, event_t *ee);
event_status handle_state_start(obj_msg_t *obj, event_t *ee);
event_status handle_state_dos(obj_msg_t *obj, event_t *ee);
event_status handle_state_tres(obj_msg_t *obj, event_t *ee);
event_status handle_state_tres_uno(obj_msg_t *obj, event_t *ee);
event_status handle_state_tres_dos(obj_msg_t *obj, event_t *ee);


#endif