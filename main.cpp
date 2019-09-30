#include "i.h"
#include "u.h"
#include <iostream>

using namespace std;
using i32 = mgt::i<32>;
using u32 = mgt::u<32>;

int main() {
  u32 a, b;
  a = 1;
  b = 1;
  u32 c;
  c = a + b;
  cout << c << endl;
  return 0;
}
