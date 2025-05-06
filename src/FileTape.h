#pragma once

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "Tape.h"

template <typename T>
class FileTape : public Tape<T> {
 private:
  static inline std::chrono::milliseconds readWriteDelay;
  static inline std::chrono::milliseconds singleShiftDelay;
  static inline std::chrono::milliseconds rewindDelay;

 public:
  FileTape() {}

  FileTape(std::filesystem::path filePath) { open(filePath); }

  FileTape(std::filesystem::path filePath, std::size_t size) {
    create(filePath, size);
  }

  std::size_t getSize() override { return size; }

  std::size_t getOffset() override { return file.tellp() / sizeof(T); }

  void rewind() override {
    file.seekp(0, std::ios_base::beg);
    std::this_thread::sleep_for(rewindDelay);
  }

  void shift(int offset = 1) override {
    file.seekp(offset * sizeof(T), std::ios_base::cur);
    std::this_thread::sleep_for(singleShiftDelay * std::abs(offset));
  }

  T read() override {
    if (getOffset() >= size) {
      throw std::runtime_error("invalid offset");
    }
    T result;
    file.read(reinterpret_cast<char*>(&result), sizeof(result));
    file.seekp(-sizeof(T), std::ios_base::cur);
    std::this_thread::sleep_for(readWriteDelay);
    return result;
  }

  void write(T value) override {
    if (getOffset() >= size) {
      throw std::runtime_error("invalid offset");
    }
    file.write(reinterpret_cast<char*>(&value), sizeof(value));
    file.seekp(-sizeof(T), std::ios_base::cur);
    std::this_thread::sleep_for(readWriteDelay);
  }

  void open(std::filesystem::path filePath) {
    file.open(filePath, file.binary | file.in | file.out | file.ate);
    size = file.tellp() / sizeof(T);
    rewind();
  }

  void create(std::filesystem::path filePath, std::size_t size) {
    file.open(filePath, file.binary | file.in | file.out | file.trunc);
    std::filesystem::resize_file(filePath, size * sizeof(T));
    this->size = size;
  }

  bool is_open() { return file.is_open(); }

 private:
  std::fstream file;
  std::size_t size;

  friend class Solution;
};
