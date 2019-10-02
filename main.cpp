//
// Created by Margatroid on 2019/10/2.
//

#include "i.h"
#include "u.h"
#include <iostream>

using namespace std;
using i32 = mgt::i<32>;
using u32 = mgt::u<32>;

int main() {
  i32 a, b;
  cin >> a >> b;
  cout << a + b << endl;
  return 0;
}
