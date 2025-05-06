#include <iostream>
#include <stdexcept>

#include "FileTape.h"
#include "Solution.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "usage: " << argv[0]
              << " <config_file> <input_file> <output_file>\n";
    return EXIT_FAILURE;
  }
  try {
    Solution::read_config(argv[1]);
  } catch (std::runtime_error e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  FileTape<uint32_t> in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "couldn't open input file\n";
    return EXIT_FAILURE;
  }
  FileTape<uint32_t> out(argv[3], in.getSize());
  if (!out.is_open()) {
    std::cerr << "couldn't open output file\n";
    return EXIT_FAILURE;
  }
  Solution::sort(in, out);
}
