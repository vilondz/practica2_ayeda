#include <string>
#include <vector>
typedef int celda;
typedef std::vector<celda> fila_de_celdas ;
typedef std::vector<fila_de_celdas> Cinta;
typedef std::pair<int, int> celda_par;
typedef std::pair<celda_par,int> celda_con_color;
class Tape {
  private:
    int size_x_;
    int size_y_;
    Cinta cinta_;
    int n_colores_;
  public:
    Tape(int = 10, int = 10);
    Tape(int , int , int);
    std::pair<int, int> get_dimensions();
    int get_color(int x, int y);
    int get_n_colores(void){return n_colores_;}
    void change_color(int x, int y);
    void set_color(int x, int y, int color);
    std::string get_color_draw(int color);
    std::string get_color_draw_bg(int color);
    std::ostream& draw_tape(std::ostream& out);
};