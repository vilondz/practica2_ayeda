#include <fstream>
#include "ant.h"
#include "tape.h"
#include "colours.h"

class Simulator{
  bool paso_a_paso_ = false;
  bool cada_x_pasos_ = false;
  int x_pasos = 0;
  public:
    Simulator();
    void Simulacion_por_defecto();
    void Simulacion_por_fichero(std::string fichero);
    void Guardar_fichero(Tape&, Ant&);
    void visualizar(Tape& cinta, Ant& hormiga);
    bool check_out(Tape& cinta, Ant& hormiga);
    void menu();
    void crear_archivo_guardado(std::string fichero_guardado, Tape& cinta, Ant& horminga);
};