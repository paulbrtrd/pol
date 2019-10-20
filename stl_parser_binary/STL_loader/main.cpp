#include <cassert>
#include <iostream>

#include "parse_stl.h"
#include "tools.h"
#include "opengl_display.h"

int main(int argc, char* argv[]) {
  std::string stl_file_name = "./Box1x1x1.stl";

  // Init openGL
  init_opengl(argc, argv);

  // Si le nom du fichier est donné en argument, on utilise celui donné
  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }

  stl::Stl_data info(stl_file_name);

  std::vector<stl::Triangle> triangles = info.gettriangles();
  std::cout << "STL HEADER = " << info.getname() << std::endl;
  std::cout << "# triangles = " << triangles.size() << std::endl;

  info.create_stl();
/*
  for (auto t : triangles) {
    std::cout << t << std::endl;
  }
*/
  // Display the mesh with openGL
  opengl_display(&info);

}
