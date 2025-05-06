#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <numeric>
#include <random>

#include "FileTape.h"
#include "Solution.h"

namespace fs = std::filesystem;
using namespace std::literals;

TEST(SolutionTest, TestData) {
  fs::path dir_path = __FILE__;
  dir_path = dir_path.parent_path() / "data";
  FileTape<std::uint32_t> in(dir_path / "in.tape"),
      out("test_out.tape", in.getSize());
  Solution::sort(in, out);
  out.rewind();
  FileTape<std::uint32_t> expected(dir_path / "out.tape");
  ASSERT_EQ(expected.getSize(), out.getSize());
  for (std::size_t i = 0; i < in.getSize(); i++) {
    ASSERT_EQ(expected.read(), out.read());
    expected.shift();
    out.shift();
  }
}

TEST(SolutionTest, RandomShuffle) {
  constexpr int length = 1 << 16, tests = 5;
  std::mt19937 rng(0xDEADBEEF);
  {
    FileTape<std::uint32_t> in("test_in.tape", length),
        out("test_out.tape", length);
    for (int t = 0; t < tests; t++) {
      std::vector<std::uint32_t> range(length);
      std::iota(range.begin(), range.end(), 0);
      std::shuffle(range.begin(), range.end(), rng);
      for (auto e : range) {
        in.write(e);
        in.shift();
      }
      in.rewind();
      Solution::sort(in, out);
      in.rewind();
      out.rewind();
      for (std::uint32_t i = 0; i < length; i++) {
        ASSERT_EQ(i, out.read()) << "failed at test " << t;
        out.shift();
      }
      out.rewind();
    }
  }
  fs::remove("test_in.tape");
  fs::remove("test_out.tape");
}
