#include "List.h"

int main() {

  List<int> list = List<int>();
  List<int> other = List<int>();

  for (int i = 1; i <= 9; ++i) {
    list.insertBack(i);
    
  }
  for (int i = 10; i <= 16; i++) {
    other.insertBack(i);
  }

  


  std::cout << list << std::endl;
  std::cout << other << std::endl;

  return 0;
}