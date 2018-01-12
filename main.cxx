#include <iostream>
#include <sstream>

#include "reversi.h"
#include "search.h"

int main() {

  Position pos;
    
  std::cout << pos << std::endl;

#if 0
  id_loop(pos);
#else
  perfect_search(pos);
#endif 
  exit(1);
}