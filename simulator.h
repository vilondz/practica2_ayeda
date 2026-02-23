#include <fstream>
#include "ant.h"
#include "tape.h"
#include "colours.h"
#include <thread>
#include <chrono>

class Simulator{
  private:
    bool paso_a_paso_ = false;
    bool cada_x_pasos_ = false;
    int x_pasos = 0;
  public:
    Simulator();
    void Simulacion_por_fichero(std::vector<std::unique_ptr<Ant>>& hormigas, Tape& cinta);
    void Guardar_fichero(Tape&, const std::vector<std::unique_ptr<Ant>>& hormigas);
    void visualizar(Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas);
    bool check_out(Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas);
    void menu();
    void check_fichero(std::string fichero);
    void crear_archivo_guardado(std::string fichero_guardado, Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas);
};