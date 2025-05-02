#include <cstdint>
#include <filesystem>
#include <fstream>

#include "Tape.h"

// TODO: add delay from config

class FileTape : public Tape<std::uint32_t> {
 public:
  FileTape(std::filesystem::path file)
      : file(file,
             std::ios::binary | std::ios::in | std::ios::out | std::ios::ate),
        size(this->file.tellp() / sizeof(std::uint32_t)) {
    this->file.seekp(0, std::ios_base::beg);
  }

  std::size_t getSize() override { return size; }

  void rewind() override { file.seekp(0); }

  void shift(int offset = 1) override {
    file.seekp(offset * sizeof(std::uint32_t), std::ios_base::cur);
  }

  std::uint32_t read() override { 
    std::uint32_t result;
    file.read(reinterpret_cast<char*>(&result), sizeof(result));
    shift(-1);
    return result;
  }

  void write(std::uint32_t value) override {
    file.write(reinterpret_cast<char*>(&value), sizeof(value));
    shift(-1);
  }

 private:
  std::fstream file;
  std::size_t size;
};
