#include <string>
#include <vector>
typedef char celda;
typedef std::vector<celda> fila_de_celdas ;
typedef std::vector<fila_de_celdas> Cinta;
class Tape {
  private:
    int size_x_;
    int size_y_;
    Cinta cinta_;
  public:
    Tape(int = 10, int = 10);
    Tape(int , int , std::vector<std::pair<int, int>> casillas_negras);
    std::pair<int, int> get_dimensions();
    bool get_color(int x, int y);

    void change_color(int x, int y);

    std::ostream& draw_tape(std::ostream& out);
};