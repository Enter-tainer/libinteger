#include "i.h"
#include "u.h"
#include <iostream>

using namespace std;
using i32 = mgt::i<32>;
using u32 = mgt::u<32>;

int main() {
  i32 a, b;
  bool flag = true;
  for (int i = -1000; i <= 1e3; ++i) {
    for (int j = i; j <= 1e3; ++j) {
      a = i, b = j;
      if (a * b != i32(i * j)) {
        cout << "Error when i = " << i << ", j = " << j << ", expected " << i32(i * j) << ", got " << a * b << ". "
             << endl;
        flag = false;
      }
    }
  }
  if (flag)
    cout << "All tests passed, no error found" << endl;

  return 0;
}
