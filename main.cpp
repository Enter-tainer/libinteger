#include <iostream>
#include "uinteger.h"

using namespace std;

int main() {
  mgt::u<4> s(3), g(3);
  cout << (s < g) << endl;
  return 0;
}