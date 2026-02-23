#include "tape.h"
#include <iostream>
#include "colours.h"

Tape::Tape(int size_x, int size_y){
  size_x_ = size_x;
  size_y_ = size_y;
  cinta_.resize(size_x_);
  for(int i = 0; i < size_x_; i++){
    cinta_[i].resize(size_y_);
  }
  for(int i = 0; i < size_x_; i++){
    for(int j = 0; j < size_y_; j++){
     // std::cout << "el bucle funciona" << std::endl;
     // std::cout << i  << " " << j << std::endl;
      cinta_[i][j] = 0;
    } 
  }
}

Tape::Tape(int size_x, int size_y, int n_colores, std::vector<celda_con_color> casillas_de_colores){
  //para el futuro tiene que coger las fichas negras de un fichero y ponerlas en la cinta donde corresponde
  size_x_ = size_x;
  size_y_ = size_y;
  n_colores_ = n_colores;
  cinta_.resize(size_x_);
  for(int i = 0; i < size_x_; i++){
    cinta_[i].resize(size_y_);
  }
  for(int i = 0; i < size_x_; i++){
    for(int j = 0; j < size_y_; j++){
     // std::cout << "el bucle funciona" << std::endl;
     // std::cout << i  << " " << j << std::endl;
      cinta_[i][j] = 0;
    } 
  }
  for(auto aux : casillas_de_colores){
    //         posicion x       posicion y          color
    set_color(aux.first.first, aux.first.second, aux.second);
  }
}
  
int Tape::get_color(int x, int y){
  return cinta_[x][y];
}
  
void Tape::change_color(int x, int y){
  cinta_[x][y] = (cinta_[x][y] + 1) % n_colores_;
}
void Tape::set_color(int x, int y, int color){
  cinta_[x][y] = color;
}
  
std::ostream& Tape::draw_tape(std::ostream& out){
  for(int i = 0; i < size_x_; i++){
    for(int j = 0; j < size_y_; j++){
      out << (cinta_[i][j]);
    }
    out << std::endl;
  }
  return out;
}

std::pair<int, int> Tape::get_dimensions(){
  return std::pair<int, int>(size_x_, size_y_);
}

std::string Tape::get_color_draw(int color){
  switch(color){
    case 0:
      return  BG_BLACK;
      break;
    case 1:
      return BG_WHITE;
      break;
    case 2:
      return BG_ORANGE;
      break;
    case 3:
      return BG_ROSE;
      break;
  }
} 

