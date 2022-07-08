#include <Arduino.h>
#include "UML.h"

static obj_msg_t mensaje_prueba;
void handle_machine_state(obj_msg_t *obj, event_t *e);

void setup()
{
  Serial.begin(115200);

  Serial.println("==========================");
  Serial.println("Empezando maquina de estos");
  Serial.println("==========================\n");

  init_state(&mensaje_prueba);
}

void loop()
{
  uint8_t event;
  
  if (Serial.available() )
  {
  
    event = Serial.parseInt();

    event_t e;
    e.state = (char)event;

   handle_machine_state(&mensaje_prueba, &e);
   e.state = 0;
  }
}

void handle_machine_state(obj_msg_t *obj, event_t *e)
{
  event_status status;
  estados_t source, target;
   

  source = obj->activate_state;
  status = State_machine(obj, e);


  if (status == transicion_evento)
  {
    target = obj->activate_state;
    event_t ee;

    ee.state = EXIT;
    obj->activate_state = source;
    State_machine(obj, &ee);

    ee.state = ENTRY;
    obj->activate_state = target;
    State_machine(obj, &ee);
  }
}