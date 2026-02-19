#include "ant.h"
Ant::Ant(int pos_x, int pos_y, orientacion direccion){
  pos_x_ = pos_x;
  pos_y_ = pos_y;
  orientacion_ = direccion;
}
    
std::pair<int,int> Ant::get_pos(void)const {
  return std::pair<int, int>(this->pos_x_, this->pos_y_);
}

//Si está sobre una celda blanca, cambia el color a negra, gira noventa grados a la izquierda
//y avanza una celda.

void Ant::sobre_blanco(){
  switch(this->orientacion_){
    case orientacion::N:
      this->orientacion_ = O;
      this->pos_y_--;
      break;
    case orientacion::E:
      this->orientacion_ = N;
      this->pos_x_--;
      break;
    case orientacion::S:
      this->orientacion_ = E;
      this->pos_y_++;
      break;
    case orientacion::O:
      this->orientacion_ = S;
      this->pos_x_++;
  }
} 
//● Si está sobre una celda negra, cambia el color a blanca, gira noventa grados a la derecha
//y avanza una celda.
void Ant::sobre_negro(){
  switch(this->orientacion_){
    case orientacion::N:
      this->orientacion_ = E;
      this->pos_y_++;
      break;
    case orientacion::E:
      this->orientacion_ = S;
      this->pos_x_++;
      break;
    case orientacion::S:
      this->orientacion_ = O;
      this->pos_y_--;
      break;
    case orientacion::O:
      this->orientacion_ = N;
      this->pos_x_--;
  }
}

std::ostream& operator<<(std::ostream& out, const Ant& hormiga){
  
  //out << hormiga.get_pos().first << hormiga.get_pos().second << std::endl;
  switch(hormiga.orientacion_){
    case orientacion::N :
      out << "^";
      break;
      case orientacion::O :
      out << "<";
      break;
      case orientacion::S :
      out << "v";
      break;
      case orientacion::E :
      out << ">";
      break;
  }
  return out;
}

    //fichero         0 ,1, 2, 3
  //enum orientacion {N, S, E, O};
int Ant::get_orientacion(void){
  switch (orientacion_)
  {
  case orientacion::N:
    return 0;
    break;
  case orientacion::S:
    return 1;
    break;
  case orientacion::E:
    return 2;
    break;
  case orientacion::O:
    return 3;
    break;
  default:
    break;
  }

}