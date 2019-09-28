#include <iostream>
#include "basic_uint.h"

using namespace std;
using u200 = mgt::basic_uint<200>;
int main() {
  u200 a, b;
  cin >> a >> b;
  cout << a * b << endl;
  return 0;
}