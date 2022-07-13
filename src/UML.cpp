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
    case C:
        Serial.println("Evento realizaso en START C");
        return event_realizado;
    case EXIT:
        Serial.printf("Adios %s\n\n", obj->msg);
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
    case C:
        Serial.println("Evento realizaso en DOS por C");
        return event_realizado;
    case EXIT:
        Serial.printf("Adios %s\n\n", obj->msg);
        obj->activate_state_son = TRES_UNO;
        obj->level = PARENT;
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
        if (obj->level == PARENT)
        {
            obj->msg = "TRES PADRE";
            Serial.printf("Hola %s\n", obj->msg);
            obj->level = SON;
        }

        break;

    case C:
        obj->activate_state = START;
        obj->level = SON_EXIT;
        return transicion_evento;
        break;

    case EXIT:
        if (obj->level == PARENT)
        {
            obj->msg = "TRES PADRE";
            Serial.printf("Adios %s\n\n", obj->msg);
            return event_realizado;
            break;
        }
    }


    if (obj->level == SON || obj->level == SON_EXIT)
    {
        switch (obj->activate_state_son)
        {
        case TRES_UNO:
            return handle_state_tres_uno(obj, ee);
            break;

        case TRES_DOS:
            return handle_state_tres_dos(obj, ee);
            break;
        }
    }

 

    return evento_ignorad;
}

event_status handle_state_tres_uno(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "TRES UNO";
        Serial.printf("Hola desde tres uno %s\n", obj->msg);
        return event_realizado;
        break;
    case A:
        obj->activate_state = TRES;
        obj->activate_state_son = TRES_DOS;
        return transicion_evento_hijo;
        break;
    case B:
        Serial.println("Evento en tres UNO B");
        event_realizado;
        break;
    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = TRES;
            obj->level = PARENT;
        }
        Serial.printf("adios este es el tres uno %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}

event_status handle_state_tres_dos(obj_msg_t *obj, event_t *ee)
{
    switch (ee->state)
    {
    case ENTRY:
        obj->msg = "TRES DOS";
        Serial.printf("Hola este hola es de tres dos %s\n", obj->msg);
        return event_realizado;
        break;
    case A:
        Serial.println("Evento en tres DOS A");
        event_realizado;
        break;
    case B:
        obj->activate_state = TRES;
        obj->activate_state_son = TRES_UNO;
        return transicion_evento_hijo;
        break;
    case EXIT:
        if (obj->level == SON_EXIT)
        {
            obj->activate_state = TRES;
            obj->level = PARENT;
        }
        Serial.printf("adios Este es el adios de tres dos %s\n\n", obj->msg);
        return event_realizado;
        break;
    }
    return evento_ignorad;
}
