#include <chrono>

#include "source_func_for_main.hpp"

// cmake ..
//  cmake .. -D visual
// 
//  AIAS_s.exe autogen_version
//  AIAS_s.exe autogen_version k_varies
//  AIAS_s.exe autogen_version length_test
//  AIAS_s.exe autogen_version length_varies

//  AIAS_s.exe sample.txt
//  AIAS_s.exe sample2.txt

int main(char argc, char** argv) {
  try {
    if (argc != 1) {
      std::string t(argv[1]);
      if (t == "autogen_version") {
         func_for_main::calculate_type_autogen_1(argc,argv);

      }

      if (t == "sample.txt" || t == "sample2.txt") {
        func_for_main::file_read(t);
      }
    }

  } catch (std::invalid_argument& r) {
    std::cerr << r.what();
  } catch (std::exception& r) {
    std::cerr << r.what();
  }
}