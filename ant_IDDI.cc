#include "ant_IDDI.h"


void ant_IDDI::movimiento(int color){
  if (color == 1 || color == 2)
    girar_derecha();
  else if (color == 0 || color == 3)
    girar_izquierda();
}