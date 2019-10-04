//
// Created by mgt on 9/29/19.
//

#include <chrono>
#include <iostream>
#include "u.h"
#include "i.h"

using namespace std;

using i1024 = mgt::i<1024>;
using u1024 = mgt::u<1024>;

string get_rand_num() {
  string res;
  for (int i = 1; i <= 300; ++i)
    res += '0' + rand() % 10;
  return res;
}

int main() {
  {
    i1024 a(get_rand_num()), b(get_rand_num());
    if (a <= b)
      swap(a, b);
    cout << "ms / op: test on i1024" << endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a + b;
    auto end = std::chrono::high_resolution_clock::now();
    cout << "plus:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a - b;
    end = std::chrono::high_resolution_clock::now();
    cout << "minus:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
      a * b;
    end = std::chrono::high_resolution_clock::now();
    cout << "multiply:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 100.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a / b;
    end = std::chrono::high_resolution_clock::now();
    cout << "division:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
      a.to_string();
    end = std::chrono::high_resolution_clock::now();
    cout << "to_string:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 100.0 << endl;
  }
  cout << "\n====================================================\n\n";
  //=================================================================================================================
  {
    u1024 a(get_rand_num()), b(get_rand_num());
    if (a <= b)
      swap(a, b);
    cout << "ms / op: test on u1024" << endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a + b;
    auto end = std::chrono::high_resolution_clock::now();
    cout << "plus:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a - b;
    end = std::chrono::high_resolution_clock::now();
    cout << "minus:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
      a * b;
    end = std::chrono::high_resolution_clock::now();
    cout << "multiply:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 100.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i)
      a / b;
    end = std::chrono::high_resolution_clock::now();
    cout << "division:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
      a.to_string();
    end = std::chrono::high_resolution_clock::now();
    cout << "to_string:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 100.0 << endl;
  }


}
