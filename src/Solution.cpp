#include "Solution.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "FileTape.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
using namespace std::literals;

void Solution::sortImpl(Tape<std::uint32_t>& in, Tape<std::uint32_t>& out,
                        std::size_t l, std::size_t r) {
  if (r - l <= M / sizeof(std::uint32_t)) {
    std::vector<std::uint32_t> buffer;
    buffer.reserve(r - l);
    for (; l < r; l++) {
      buffer.push_back(in.read());
      in.shift();
    }
    std::sort(buffer.begin(), buffer.end());
    for (std::uint32_t e : buffer) {
      out.write(e);
      out.shift();
    }
    return;
  }

  std::size_t m = (l + r) / 2;
  std::filesystem::path temp_left_path = temp_path;
  temp_left_path += std::to_string(l) + "_" + std::to_string(m);
  std::filesystem::path temp_right_path = temp_path;
  temp_right_path += std::to_string(m) + "_" + std::to_string(r);
  {
    FileTape<std::uint32_t> temp_left(temp_left_path, m - l);
    sortImpl(in, temp_left, l, m);
    temp_left.rewind();

    FileTape<std::uint32_t> temp_right(temp_right_path, r - m);
    sortImpl(in, temp_right, m, r);
    temp_right.rewind();

    std::uint32_t a = temp_left.read(), b = temp_right.read();
    for (std::size_t i = l; i < r; i++) {
      if (temp_left.getOffset() != temp_left.getSize() && a < b ||
          temp_right.getOffset() == temp_right.getSize() && !(a < b)) {
        out.write(a);
        temp_left.shift();
        if (temp_left.getOffset() < temp_left.getSize()) {
          a = temp_left.read();
        }
      } else {
        out.write(b);
        temp_right.shift();
        if (temp_right.getOffset() < temp_right.getSize()) {
          b = temp_right.read();
        }
      }
      out.shift();
    }
  }
  std::filesystem::remove(temp_left_path);
  std::filesystem::remove(temp_right_path);
}

void Solution::sort(Tape<std::uint32_t>& in, Tape<std::uint32_t>& out) {
  if (!std::filesystem::exists(temp_dir))
    std::filesystem::create_directory(temp_dir);
  sortImpl(in, out, 0, in.getSize());
  std::filesystem::remove(temp_dir);
}

void Solution::read_config(std::filesystem::path filePath) {
  std::ifstream f(filePath);
  if (!f.is_open()) {
    throw std::runtime_error{"couldn't open config file"};
  }
  json data = json::parse(f);
  
  try {
    FileTape<std::uint32_t>::readWriteDelay =
          std::chrono::milliseconds{data.value("read_write_delay", 0)};
  } catch (json::exception e) {
    throw std::runtime_error{"couldn't read read_write_delay: "s + e.what()};
  }
  try {
    FileTape<std::uint32_t>::singleShiftDelay =
        std::chrono::milliseconds{data.value("single_shift_delay", 0)};
  } catch (json::exception e) {
    throw std::runtime_error{"couldn't read single_shift_delay: "s + e.what()};
  }
  try {
    FileTape<std::uint32_t>::rewindDelay =
        std::chrono::milliseconds{data.value("rewind_delay", 0)};
  } catch (json::exception e) {
    throw std::runtime_error{"couldn't read rewind_delay: "s + e.what()};
  } 
}
