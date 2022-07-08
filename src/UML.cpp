#include <Arduino.h>
#include "UML.h"

void init_state(obj_msg_t *obj)
{
    event_t ee;
    ee.state = ENTRY;
    obj->activate_state = START;
    State_machine(obj, &ee);
}

event_status State_machine(obj_msg_t *obj, event_t *ee)
{
    switch (obj->activate_state)
    {
    case START:
        return handle_state_start(obj, ee);
        break;
    case DOS:
        return handle_state_dos(obj, ee);
        break;
    case TRES:
        return handle_state_tres(obj, ee);
        break;

    default:
        Serial.printf("No esta contemplado, Reiniciando\n");
        init_state(obj);
        return evento_ignorad;
    }
    return evento_ignorad;
}

event_status handle_state_start(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "START";
        Serial.printf("Hola %s\n", obj->msg);
        return event_realizado;
        break;
    case A:
        obj->activate_state = DOS;
        return transicion_evento;
    case EXIT:
        Serial.printf("Adios %s\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_dos(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "DOS";
        Serial.printf("Hola %s\n", obj->msg);
        return event_realizado;
        break;
    case A:
        obj->activate_state = TRES;
        return transicion_evento;
    case B:
        obj->activate_state = START;
        return transicion_evento;
    case EXIT:
        Serial.printf("Adios %s\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_tres(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "TRES";
        ee->state = TRES_UNO;
        Serial.printf("Hola %s\n ", obj->msg);
        return event_realizado;
        break;

        // switch (ee->state)
        // {
        // case TRES_UNO:

        //     obj->msg = "TRES_UNO";

        //     switch (ee->state)
        //     {
        //     case ENTRY:
        //         Serial.printf("Hola %s\n", obj->msg);
        //         break;

        //     case A:
        //         Serial.printf("Hola Caso A %s\n", obj->msg);
        //         break;

        //     case EXIT:
        //         Serial.printf("Adios %s\n", obj->msg);
        //         break;
        //     }
        //     break;

        // case TRES_DOS:
        //     obj->msg = "TRES_DOS";
        //     switch (ee->state)
        //     {
        //     case ENTRY:
        //         Serial.printf("Hola %s\n", obj->msg);
        //         break;

        //     case A:
        //         Serial.printf("Hola Caso A %s\n", obj->msg);
        //         break;

        //     case EXIT:
        //         Serial.printf("Adios %s\n", obj->msg);
        //         break;
        //     }
        // }

        // break;

    case EXIT:
        Serial.printf("Adios %s\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}