#include <iostream>
//fichero         0 ,1, 2, 3
enum orientacion {N, S, E, O};

class Ant{
  private:
    int pos_x_;
    int pos_y_;
    orientacion orientacion_;
  public:
    //Ant();
    Ant(int pos_x = 0, int pos_y = 0, orientacion direccion = orientacion::N);
    std::pair<int, int> get_pos() const;
    void sobre_blanco(); 
    void sobre_negro();
    int get_orientacion(void);
    friend std::ostream& operator<<(std::ostream& out, const Ant& hormiga);
};