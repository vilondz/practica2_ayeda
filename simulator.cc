#include "simulator.h"
#include <assert.h>
Simulator::Simulator(){
 menu();
}

void Simulator::Simulacion_por_fichero(std::string fichero){
  std::ifstream input_file(fichero);
  if(!input_file.is_open()){
    std::cerr << "Error al abrir el fichero terminando programa ..." << std::endl;
    std::exit(1);
  }
    //fichero         0 ,1, 2, 3
  //enum orientacion {N, S, E, O};
  int cinta_x, cinta_y;
  input_file >> cinta_x >> cinta_y;
  int hormiga_x, hormiga_y, orientacion_num;
  input_file >> hormiga_x >> hormiga_y >> orientacion_num;
  orientacion orientacion_sign;
  switch (orientacion_num)
  {
  case 0:
    orientacion_sign = orientacion::N;
    break;
  case 1:
    orientacion_sign = orientacion::S;
    break;
  case 2:
    orientacion_sign = orientacion::E;
    break;
  case 3:
    orientacion_sign = orientacion::O;
    break;
  default:
    std::cerr << "orientacion de la hormiga invalida, terminando programa ..." << std::endl;
    break;
  }
  std::vector<std::pair<int, int>> casillas_negras;
  int casilla_negra_x, casilla_negra_y;
  while(input_file >> casilla_negra_x >> casilla_negra_y){
    casillas_negras.push_back(std::pair<int, int>(casilla_negra_x, casilla_negra_y));
  }
  //std::cout << "dimensiones de la cinta" << std::endl;
  //std::cout << cinta_x << " " << cinta_y << std::endl;
  //std::cout << "posicion de la hormiga" << std::endl;
  //std::cout << hormiga_x << " " << hormiga_y << " " << orientacion_num << std::endl;
  //std::cout << "casillas negras " << std::endl;
  //for(auto aux : casillas_negras){
  //  std::cout << aux.first << " " << aux.second << std::endl;
  //}
  Tape cinta(cinta_x, cinta_y, casillas_negras);
  Ant hormiga(hormiga_x, hormiga_y, orientacion_sign);
  std::cout << "indique el numero de pasos: ";
  int pasos_a_dar, pasos_dados = 0;
  std::cin >> pasos_a_dar;
  while(true){
    //chequeamos si esta fuera del tablero
    if(check_out(cinta, hormiga)){
      //si esta fuera se acabo el bucle
      std::cout << "la hormiga salio de la cinta" << std::endl;
      break;
    }
    if(cada_x_pasos_){
      if(pasos_dados % x_pasos == 0)visualizar(cinta, hormiga);
    }
    else visualizar(cinta, hormiga);
    //si ya los hizo todos se acaba el bucle
    if(cinta.get_color(hormiga.get_pos().first, hormiga.get_pos().second)){  //vemos el color de donde esta la hormiga
      cinta.change_color(hormiga.get_pos().first, hormiga.get_pos().second);
      hormiga.sobre_negro();   //y la hormiga hace el movimiento que tiene que hacer para las casillas negras
    }
    else{
      //lo mismo para el negro
      cinta.change_color(hormiga.get_pos().first, hormiga.get_pos().second);
      hormiga.sobre_blanco();
    }
    //restamos un paso de los que nos pidio el usuario 
    pasos_a_dar--;
    pasos_dados++;
    if(pasos_a_dar == 0){
      break;
    }
    if(paso_a_paso_ && pasos_a_dar % x_pasos == 0){
      std::string seguir;
      std::cout << "Presiona a para continuar\nPresiona cualquier otra cosa para salir" << std::endl;

      std::cin >> seguir;
      if(seguir == "a"){
        continue;
      }
      else break;
    }
      
  }
  visualizar(cinta, hormiga);
  std::cout << "pasos dados : " << pasos_dados << std::endl;
  Guardar_fichero(cinta, hormiga);
}

void Simulator::Simulacion_por_defecto(){
  Tape cinta(150,150);
  Ant hormiga(150/2-1,150/2-1);
  std::cout << "indique el numero de pasos: ";
  int pasos_a_dar, pasos_dados = 0;
  std::cin >> pasos_a_dar;
  while(true){
    //chequeamos si esta fuera del tablero
    if(check_out(cinta, hormiga)){
      //si esta fuera se acabo el bucle
      std::cout << "la hormiga salio de la cinta" << std::endl;
      break;
    }
    if(cada_x_pasos_){
      if(pasos_dados % x_pasos == 0)visualizar(cinta, hormiga);
    }
    else visualizar(cinta, hormiga);
    //si ya los hizo todos se acaba el bucle
    
    if(cinta.get_color(hormiga.get_pos().first, hormiga.get_pos().second)){  //vemos el color de donde esta la hormiga
      cinta.change_color(hormiga.get_pos().first, hormiga.get_pos().second);
      hormiga.sobre_negro();   //y la hormiga hace el movimiento que tiene que hacer para las casillas negras
    }
    else{
      //lo mismo para el blanco
      cinta.change_color(hormiga.get_pos().first, hormiga.get_pos().second);
      hormiga.sobre_blanco();
    }
    //restamos un paso de los que nos pidio el usuario 
    pasos_a_dar--;
    pasos_dados++;
    if(pasos_a_dar == 0){
      break;
    }
    if(paso_a_paso_ && pasos_a_dar % x_pasos == 0){
      std::string seguir;
      std::cout << "presiona a para continuar" << std::endl;
      std::cin >> seguir;
      if(seguir == "a"){
        continue;
      }
    }
      
  }
  visualizar(cinta, hormiga);
  std::cout << "pasos dados : " << pasos_dados << std::endl;

  Guardar_fichero(cinta, hormiga);
 
}
    
void Simulator::Guardar_fichero(Tape & cinta, Ant& hormiga){
  char opcion;
  std::string fichero_guardado = "guardado.langdon";
  do
  {
    std::cout << "Desea guardar el estado final (y/n)" << std::endl;
    std::cin >> opcion;
  } while (opcion != 'y' && opcion != 'n');
  switch(opcion){
    case 'y':
      std::cout << "Elija un nombre para el fichero de guardado" << std::endl;
      std::cin >> fichero_guardado;
      fichero_guardado += ".langdon";
      crear_archivo_guardado(fichero_guardado, cinta, hormiga);
      break;
    case 'n':
      std::cout << "no se ha guardado el estado final cerrando programa ..." << std::endl;
      std::exit(0);
      break;
    default:
    break;
  }

}

void Simulator::menu(){
  std::cout << "Configuracion del simulador " << std::endl;
  int opcion = 0;
  std::string fichero;
  do
  {
    std::cout << "Como desea utilizar el simulador\n 1.Por defecto\n 2.Con un fichero.langdon" << std::endl;
    std::cin >> opcion;
  } while (opcion != 1 && opcion != 2);  
  switch (opcion)
  {
  case 1:
    do
    {
        opcion = 0;
        std::cout << "Como quiere imprimir la hormiga de langdon\n 1.Cada x pasos\n 2.Paso a Paso\n 3.Ambas" << std::endl;
        std::cin >> opcion;
    } while (opcion != 1 && opcion != 2 && opcion != 3);
    switch (opcion)
    {
      case 1:
        cada_x_pasos_ = true;
        std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
        std::cin >> x_pasos;
        Simulacion_por_defecto();
        break;
      case 2:
        paso_a_paso_ = true;
        x_pasos = 1;
        Simulacion_por_defecto();
        break;
      case 3:
        cada_x_pasos_ = true;
        paso_a_paso_ = true;
        std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
        std::cin >> x_pasos;
        assert(x_pasos != 0);
        Simulacion_por_defecto();
        break;
      default:
        std::cout << "opcion invalida cerrando programa..." << std::endl;
        std::exit(1);
      break;
    }
    break;
  case 2:
    std::cout << "Introduzca un fichero .langdon" << std::endl;
    std::cin >> fichero;
    do
    {
      opcion = 0;
      std::cout << "Como quiere imprimir la hormiga de langdon\n 1.Cada x pasos\n 2.Paso a Paso\n 3.Ambas" << std::endl;
      std::cin >> opcion;
    } while (opcion != 1 && opcion != 2 && opcion != 3);
    switch (opcion)
    {
    case 1:
      cada_x_pasos_ = true;
      std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
      std::cin >> x_pasos;
      assert(x_pasos != 0);
      Simulacion_por_fichero(fichero);
      break;
    case 2:
      paso_a_paso_ = true;
      x_pasos = 1;
      Simulacion_por_fichero(fichero);
      break;
    case 3:
      cada_x_pasos_ = true;
      paso_a_paso_ = true;
      std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
      std::cin >> x_pasos;
      Simulacion_por_fichero(fichero);
      break;
    default:
      std::cout << "opcion invalida cerrando programa..." << std::endl;
      std::exit(1);
    }
  
  default:
    break;
  }
  
}

void Simulator::visualizar(Tape& cinta, Ant& hormiga){
  for(int i = 0; i < cinta.get_dimensions().first; i++){
    for(int j = 0; j < cinta.get_dimensions().second; j++){
      if(hormiga.get_pos().first == i && hormiga.get_pos().second == j){
        if(cinta.get_color(hormiga.get_pos().first, hormiga.get_pos().second)){
          std::cout << RED << BG_BLACK << hormiga << RESET;
        }
        else{
          std::cout << RED << BG_WHITE << hormiga << RESET;
        }
          

      }
      else{
        if(cinta.get_color(i, j)){
          std::cout <<BLACK << BG_BLACK << "X" << RESET;
        }
        else{
          std::cout <<WHITE << BG_WHITE << "x" << RESET;
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool Simulator::check_out(Tape& cinta, Ant& hormiga){
      //hormiga x >= size_x de cinta
  if(hormiga.get_pos().first >= cinta.get_dimensions().first || 
     hormiga.get_pos().first < 0 || 
     hormiga.get_pos().second >= cinta.get_dimensions().second || 
     hormiga.get_pos().second < 0){
    return true;
  }
  return false;
}

void Simulator::crear_archivo_guardado(std::string fichero_guardado, Tape& cinta, Ant& hormiga){
  std::ofstream output_file(fichero_guardado);
  if(!output_file.is_open()){
    std::cerr << "Error al abrir el archivo de guardado cerrando programa ..." << std::endl;
    std::exit(1);
  }
  output_file << cinta.get_dimensions().first << " " << cinta.get_dimensions().second << std::endl;
  output_file << hormiga.get_pos().first << " " << hormiga.get_pos().second << " " << hormiga.get_orientacion() << std::endl;
  for(int i = 0; i < cinta.get_dimensions().first; i++){
    for(int j = 0; j < cinta.get_dimensions().second; j++){
      if(cinta.get_color(i, j)){
        output_file << i << " " << j << std::endl;
      }
    }
  }
}