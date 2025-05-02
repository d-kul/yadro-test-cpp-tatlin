#include <iostream>

#include "FileTape.h"

using namespace std;

int main(int argc, char** argv) {
  FileTape tape("test.txt");
  cout << "SIZE: " << tape.getSize() << '\n';
  for (size_t i = 0; i < tape.getSize(); i++) {
    cout << tape.read() << ", ";
    tape.shift();
  }
  cout << '\n';
  tape.rewind();
  for (size_t i = 0; i < tape.getSize(); i++) {
    cout << tape.read() << ", ";
    tape.shift();
  }
  cout << '\n';
  for (size_t i = 0; i < tape.getSize(); i++) {
    tape.shift(-1);
    cout << tape.read() << ", ";
  }
  cout << '\n';
  for (size_t i = 0; i < tape.getSize(); i++) {
    tape.write(tape.getSize() - 1 - i);
    tape.shift();
  }
  cout << '\n';
}
