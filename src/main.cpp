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

  if (Serial.available())
  {

    event = Serial.read();

    event_t e;
    e.state = (char)event;

    handle_machine_state(&mensaje_prueba, &e);
    e.state = 0;
  }
}

void handle_machine_state(obj_msg_t *obj, event_t *e)
{
  event_status status;
  hierarchical_t statusSon;
  estados_names_t source, target;
  estados_son_names_t source_son, target_son;
  event_t ee;

  source = obj->activate_state;
  source_son = obj->activate_state_son;
  status = State_machine(obj, e);
  statusSon = obj->level;

  switch (status)
  {
  case transicion_evento:
    target = obj->activate_state;
    

    ee.state = EXIT;
    obj->activate_state = source;
    State_machine(obj, &ee);

    if (statusSon == SON_EXIT)
    {
      ee.state = EXIT;
      obj->activate_state = source;
      State_machine(obj, &ee);
    }

    ee.state = ENTRY;
    obj->activate_state = target;
    State_machine(obj, &ee);
    break;

  case transicion_evento_hijo:
    target = obj->activate_state;
    target_son = obj->activate_state_son;

    ee.state = EXIT;
    obj->activate_state = source;
    obj->activate_state_son = source_son;
    State_machine(obj, &ee);

    ee.state = ENTRY;
    obj->activate_state = target;
    obj->activate_state_son = target_son;
    State_machine(obj, &ee);

    break;
  }
}