#include "ant_IDID.h"


void ant_IDID::movimiento(int color){
  if (color == 1 || color == 3)
    girar_derecha();
  else if (color == 0 || color == 2)
    girar_izquierda();
}