#include <iostream>
#include "basic_uint.h"

using namespace std;

int main() {
  mgt::basic_uint<4> s(3), g(3);
  cout << (s < g) << endl;
  return 0;
}