#include <cstddef>

template <typename T>
class Tape {
 public:
  // Returns the sizeof the tape
  virtual std::size_t getSize() = 0;

  // Rewinds the tape back to the beginning
  virtual void rewind() = 0;

  // Moves the tape forward by offset (or backward if offset is negative)
  virtual void shift(int offset = 1) = 0;

  // Reads the cell under the head
  virtual T read() = 0;

  // Writes to the cell under the head
  virtual void write(T value) = 0;
};
