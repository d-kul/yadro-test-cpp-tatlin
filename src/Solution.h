#pragma once

#include <cstdint>
#include <filesystem>

#include "Tape.h"

class Solution {
 private:
  static inline std::size_t M = 1 << 10;
  static inline const auto temp_dir = std::filesystem::path("tmp");
  static inline const auto temp_path = temp_dir / "tape";

  static void sortImpl(Tape<std::uint32_t>& in, Tape<std::uint32_t>& out,
                std::size_t l, std::size_t r);

 public:
  static void sort(Tape<std::uint32_t>& in, Tape<std::uint32_t>& out);

  static void read_config(std::filesystem::path filePath);
};
