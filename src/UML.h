#ifndef UML_H
#define UML_H

// Definir los estados
typedef enum{
    START,
    DOS,
    TRES
} estados_t;

// Definir las señales principales
typedef enum{
    A=1,
    B,
    C,
    TRES_UNO,
    TRES_DOS,
    ENTRY,
    EXIT
} signal_t;

// Definir las variables a trabajar
typedef struct 
{
    String msg;
    estados_t activate_state;
} obj_msg_t;

typedef enum{
    event_realizado,
    evento_ignorad,
    transicion_evento
} event_status;

// Definir el evento
typedef struct 
{
    uint8_t state;  // Aca se almacena el valor de las señales 
} event_t;


void init_state(obj_msg_t *);
event_status State_machine(obj_msg_t *obj, event_t *ee);
event_status handle_state_start(obj_msg_t *obj, event_t *ee);
event_status handle_state_dos(obj_msg_t *obj, event_t *ee);
event_status handle_state_tres(obj_msg_t *obj, event_t *ee);

#endif