#include "ant.h"
Ant::Ant(int pos_x, int pos_y, orientacion direccion)
{
  pos_x_ = pos_x;
  pos_y_ = pos_y;
  orientacion_ = direccion;
}

std::pair<int, int> Ant::get_pos(void) const
{
  return std::pair<int, int>(this->pos_x_, this->pos_y_);
}

// Si está sobre una celda blanca, cambia el color a negra, gira noventa grados a la izquierda
// y avanza una celda.

// ● Si está sobre una celda negra, cambia el color a blanca, gira noventa grados a la derecha
// y avanza una celda.

std::ostream &operator<<(std::ostream &out, const Ant &hormiga)
{

  // out << hormiga.get_pos().first << hormiga.get_pos().second << std::endl;
  switch (hormiga.orientacion_)
  {
  case orientacion::N:
    out << "^";
    break;
  case orientacion::O:
    out << "<";
    break;
  case orientacion::S:
    out << "v";
    break;
  case orientacion::E:
    out << ">";
    break;
  }
  return out;
}

// fichero         0 ,1, 2, 3
// enum orientacion {N, S, E, O};
orientacion Ant::get_orientacion(void)
{
  return orientacion_;
}

void Ant::move()
{
  switch (this->orientacion_)
  {
  case orientacion::N:
    this->pos_x_--;
    break;
  case orientacion::E:
    this->pos_y_++;
    break;
  case orientacion::S:
    this->pos_x_++;
    break;
  case orientacion::O:
    this->pos_y_--;
  }
}
void Ant::set_orientacion(orientacion ori)
{
  orientacion_ = ori;
}

void Ant::girar_derecha(){
  switch (orientacion_){
  case orientacion::N:
    orientacion_ = orientacion::E;
    break;
  case orientacion::E:
    orientacion_ = orientacion::S;
    break;
  case orientacion::S:
    orientacion_ = orientacion::O;
    break;
  case orientacion::O:
    orientacion_ = orientacion::N;
    break;
  }
}
void Ant::girar_izquierda(){
  switch (orientacion_){
  case orientacion::N:
    orientacion_ = orientacion::O;
    break;
  case orientacion::O:
    orientacion_ = orientacion::S;
    break;
  case orientacion::S:
    orientacion_ = orientacion::E;
    break;
  case orientacion::E:
    orientacion_ = orientacion::N;
    break;
  }
}

char Ant::get_orientacion_char(){
  switch (orientacion_)
  {
  case orientacion::N:
    return '^' ;
    break;
  case orientacion::S:
    return 'v' ;
    break;
  case orientacion::O:
    return '<' ;
    break;
  case orientacion::E:
    return '>' ;
    break;
  }
}