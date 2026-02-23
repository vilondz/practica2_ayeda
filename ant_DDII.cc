#include "ant_DDII.h"


void ant_DDII::movimiento(int color){
  if (color == 0 || color == 1){
    girar_derecha();
  }
  else if (color == 2 || color == 3){
    girar_izquierda();
  }
}
