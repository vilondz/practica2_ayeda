#include "simulator.h"
#include <assert.h>
#include <cstdlib>
#include <stdlib.h>
#include "ant_DDII.h"
#include "ant_DIDI.h"
#include "ant_IDDI.h"
#include "ant_IDID.h"
Simulator::Simulator(){
 menu();
}

void Simulator::Simulacion_por_fichero(std::vector<std::unique_ptr<Ant>>& hormigas, Tape& cinta){
  //std::cout << "dimensiones de la cinta" << std::endl;
  //std::cout << cinta_x << " " << cinta_y << std::endl;
  //std::cout << "posicion de la hormiga" << std::endl;
  //std::cout << hormiga_x << " " << hormiga_y << " " << orientacion_num << std::endl;
  //std::cout << "casillas negras " << std::endl;
  //for(auto aux : casillas_negras){
  //  std::cout << aux.first << " " << aux.second << std::endl;
  //}

  std::cout << "Indique el número de pasos: ";
    int pasos_a_dar, pasos_dados = 0;
    std::cin >> pasos_a_dar;

    while (pasos_a_dar > 0) {
        // Chequeamos si alguna hormiga salió de la cinta
        if (check_out(cinta, hormigas)) {
            std::cout << "Al menos una hormiga salió de la cinta. Terminando simulación." << std::endl;
            break;
        }

        // Visualización
        if (cada_x_pasos_) {
            if (pasos_dados % x_pasos == 0) {
                std::cout << "\033[3J\033[2J\033[H" << std::flush;
                visualizar(cinta, hormigas);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        } else {
            std::cout << "\033[3J\033[2J\033[H" << std::flush;
            visualizar(cinta, hormigas);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        // Cada hormiga se mueve según la celda donde está
        for (auto& h : hormigas) {
            auto [x, y] = h->get_pos();
            int color_actual = cinta.get_color(x, y);

            // Cambiamos el color de la celda de manera cíclica
            cinta.change_color(x, y);

            // Llamamos al método virtual que aplica el movimiento de la hormiga
            h->movimiento(color_actual);
        }

        // Chequeamos que no haya hormigas en la misma celda
        //check_hormigas_no_superpuestas(hormigas);

        pasos_a_dar--;
        pasos_dados++;

        // Modo paso a paso
        if (paso_a_paso_ && pasos_dados % x_pasos == 0) {
            std::string seguir;
            std::cout << "Presiona 'a' para continuar, cualquier otra tecla para salir: ";
            std::cin >> seguir;
            if (seguir != "a") break;
        }
    }

    // Visualización final
    visualizar(cinta, hormigas);
    std::cout << "Pasos dados: " << pasos_dados << std::endl;

    // Guardado de todas las hormigas
    Guardar_fichero(cinta, hormigas);
}

    
void Simulator::Guardar_fichero(Tape & cinta, const std::vector<std::unique_ptr<Ant>>& hormigas){
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
      crear_archivo_guardado(fichero_guardado, cinta, hormigas);
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

    std::cout << "Introduzca un fichero .langdon" << std::endl;
    std::cin >> fichero;

    do {
        opcion = 0;
        std::cout << "Como quiere imprimir la hormiga de langdon\n"
                  << " 1. Cada x pasos\n"
                  << " 2. Paso a Paso\n"
                  << " 3. Ambas\n";
        std::cin >> opcion;
    } while (opcion != 1 && opcion != 2 && opcion != 3);

    switch (opcion) {
        case 1:
            cada_x_pasos_ = true;
            std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
            std::cin >> x_pasos;
            assert(x_pasos != 0);
            check_fichero(fichero);
            break;

        case 2:
            paso_a_paso_ = true;
            x_pasos = 1;
            check_fichero(fichero);
            break;

        case 3:
            cada_x_pasos_ = true;
            paso_a_paso_ = true;
            std::cout << "Cada cuantos pasos quiere imprimir la hormiga" << std::endl;
            std::cin >> x_pasos;
            assert(x_pasos != 0);
            check_fichero(fichero);
            break;

        default:
            std::cout << "opcion invalida cerrando programa..." << std::endl;
            std::exit(1);
    }
}

//void Simulator::visualizar(Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas){
//  for(int i = 0; i < cinta.get_dimensions().first; i++){
//    for(int j = 0; j < cinta.get_dimensions().second; j++){
//      if(hormiga.get_pos().first == i && hormiga.get_pos().second == j){
//        if(cinta.get_color(hormiga.get_pos().first, hormiga.get_pos().second)){
//          std::cout << RED << BG_BLACK << hormiga << RESET;
//        }
//        else{
//          std::cout << RED << BG_WHITE << hormiga << RESET;
//        }
//          
//
//      }
//      else{
//        if(cinta.get_color(i, j)){
//          std::cout <<BLACK << BG_BLACK << "X" << RESET;
//        }
//        else{
//          std::cout <<WHITE << BG_WHITE << "x" << RESET;
//        }
//      }
//    }
//    std::cout << std::endl;
//  }
//  std::cout << std::endl;
//}
void Simulator::visualizar(Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas){
  for(int i = 0; i < cinta.get_dimensions().first; i++){
    for(int j = 0; j < cinta.get_dimensions().second; j++){
      bool dibujado = false;
      for(const auto& h : hormigas){
        auto [hx, hy] = h->get_pos();
        if(hx == i && hy == j){
          dibujado = true;
          // Flecha de la hormiga con su color, fondo según celda
            std::cout << h->get_color() <<  cinta.get_color_draw(cinta.get_color(i, j)) << *h << RESET;
          break;
        }
      }
      if(!dibujado)
          std::cout << "x" << cinta.get_color_draw(cinta.get_color(i,j)) << RESET;
   }
   std::cout << std::endl;
  }
}

bool Simulator::check_out(Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas) {
    for (const auto& hormiga : hormigas) {
        auto [x, y] = hormiga->get_pos();
        if (x < 0 || x >= cinta.get_dimensions().first ||
            y < 0 || y >= cinta.get_dimensions().second) {
            return true;  // Al menos una hormiga salió de la cinta
        }
    }
    return false;  // Todas dentro de la cinta
}

void Simulator::crear_archivo_guardado(std::string fichero_guardado, Tape& cinta, const std::vector<std::unique_ptr<Ant>>& hormigas){
  std::ofstream output_file(fichero_guardado);
    if (!output_file.is_open()) {
        std::cerr << "Error al abrir el archivo de guardado cerrando programa ..." << std::endl;
        std::exit(1);
    }
    // Guardamos las dimensiones de la cinta
    output_file << cinta.get_dimensions().first << " " << cinta.get_dimensions().second << std::endl;

    // Guardamos cada hormiga: posición y orientación
    for (const auto& hormiga : hormigas) {
        output_file << hormiga->get_pos().first << " "
                    << hormiga->get_pos().second << " "
                    << hormiga->get_orientacion_char() << std::endl;
    }
    // Guardamos todas las celdas con color distinto de 0
    for (int i = 0; i < cinta.get_dimensions().first; i++) {
        for (int j = 0; j < cinta.get_dimensions().second; j++) {
            if (cinta.get_color(i, j) != 0) { // cualquier color distinto de 0
                output_file << i << " " << j << " " << cinta.get_color(i, j) << std::endl;
            }
        }
    }
}
void Simulator::check_fichero(std::string fichero){
  std::vector<std::unique_ptr<Ant>> hormigas;
    std::ifstream input_file(fichero);
    if (!input_file.is_open()) {
        std::cerr << "Error al abrir el fichero terminando programa ..." << std::endl;
        std::exit(1);
    }

    // --- Leemos dimensiones de la cinta y número de colores ---
    int cinta_x, cinta_y, n_colores;
    input_file >> cinta_x >> cinta_y >> n_colores;

    // Inicializamos la cinta vacía
    
    Tape cinta(cinta_x, cinta_y);

    // --- Leemos las hormigas ---
    std::string tipo_hormiga;
    int hormiga_x, hormiga_y;
    char orient_char;
    while (input_file >> tipo_hormiga >> hormiga_x >> hormiga_y >> orient_char) {
        orientacion dir;
        switch (orient_char) {
            case '^': dir = orientacion::N; break;
            case 'v': dir = orientacion::S; break;
            case '>': dir = orientacion::E; break;
            case '<': dir = orientacion::O; break;
            default:
                std::cerr << "Orientacion invalida en el fichero: " << orient_char << std::endl;
                continue;
        }

        // Creamos la hormiga según el tipo
        if (tipo_hormiga == "DDII") {
            hormigas.push_back(std::make_unique<ant_DDII>(hormiga_x, hormiga_y, dir));
        } else if (tipo_hormiga == "DIDI") {
            hormigas.push_back(std::make_unique<ant_DIDI>(hormiga_x, hormiga_y, dir));
        } else if (tipo_hormiga == "IDDI") {
            hormigas.push_back(std::make_unique<ant_IDDI>(hormiga_x, hormiga_y, dir));
        } else if (tipo_hormiga == "IDID") {
            hormigas.push_back(std::make_unique<ant_IDID>(hormiga_x, hormiga_y, dir));
        } else {
            std::cerr << "Tipo de hormiga desconocido: " << tipo_hormiga << std::endl;
        }
    }

    // --- Leemos las celdas con color inicial distinto de 0 ---
    int celda_x, celda_y, color;
    while (input_file >> celda_x >> celda_y >> color) {
        cinta.set_color(celda_x, celda_y, color);
    }

    input_file.close();

    Simulacion_por_fichero(hormigas,cinta);
}