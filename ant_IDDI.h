#include "ant.h"
#include "colours.h"
class ant_IDDI : public Ant
{
  private:
  public:
    ant_IDDI(int x = 0, int y = 0, orientacion posicion = orientacion::N) : Ant(x, y, posicion){};
    void movimiento(int color) override;
    std::string get_color(){return RED;}
};