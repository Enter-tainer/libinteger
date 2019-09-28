#include <iostream>
#include "basic_uint.h"

using namespace std;
using u512 = mgt::basic_uint<1024>;
int main() {
  u512 a(1), b(2);
  cout << a + b << endl;
  return 0;
}