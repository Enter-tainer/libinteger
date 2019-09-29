#include <iostream>
#include "i.h"
#include "u.h"

using namespace std;
using i32 = mgt::i<32>;

int main() {
  i32 a, b;
  cin >> a >> b;
  cout << a + b << endl;

  return 0;
}