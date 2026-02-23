#include "ant.h"
#include "colours.h"
class ant_IDID : public Ant
{
  private:
  public:
    ant_IDID(int x = 0, int y = 0, orientacion posicion = orientacion::N) : Ant(x, y, posicion){};
    void movimiento(int color) override;
    std::string get_color(){return GREEN;}
};