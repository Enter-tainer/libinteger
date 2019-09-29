//
// Created by mgt on 9/28/19.
//

#ifndef INTEGER_U_H
#define INTEGER_U_H

#include "basic_uint.h"

namespace mgt {
template <size_t l = 1024> class u : public basic_uint<l> {
public:
  u() { this->data = 0; }

  u(const u<l> &s) { this->data = s.data; }

  explicit u(unsigned long long s) { this->data = std::bitset<l>(s); }

  explicit u(std::bitset<l> s) { this->data = s; }

  explicit u(std::string str) { this->from_string(str); }

  u<l> &operator=(const unsigned long long s) {
    *this = u<l>(s);
    return *this;
  }

  u<l> &operator=(const std::string str) {
    if (str[0] == '-') {
      abort();
    }
    *this = u<l>(str);
    return *this;
  }
};

} // namespace mgt

#endif // INTEGER_U_H
