#include "i.h"
#include "u.h"
#include <iostream>

using namespace std;
using i64 = mgt::i<64>;
using u32 = mgt::u<32>;

int main() {
  i64 a, b;
  bool success = true;
  for (long long int i = -1e4; i <= -1e4+1000; ++i) {
    for (long long int j = i; j <= -1e4+1000; ++j) {
      a = i, b = j;
      if (a * b != i64(i * j)) {
        cout << "Error when i = " << i << ", j = " << j << ", expected " << i64(i * j) << ", got " << a * b << ". "
             << endl;
        success = false;
      }
    }
  }
  if (success)
    cout << "All tests passed, no error found" << endl;
  return 0;
}
