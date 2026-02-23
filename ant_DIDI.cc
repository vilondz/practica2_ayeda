#include "ant_DIDI.h"

void ant_DIDI::movimiento(int color){
  if (color == 0 || color == 2)
    girar_derecha();
  else if (color == 1 || color == 3)
    girar_izquierda();
}