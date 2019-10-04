# libinteger

## Usage

``` cpp
#include <iostream>
#include "i.h"
#include "u.h"

using namespace std;
using i1024 = mgt::i<1024>;
using u1024 = mgt::u<1024>;
int main() {
  i1024 a, b;
  cin >> a >> b;
  cout << a + b << endl;

  return 0;
}
```

## Performance(With -O2)

```
ms / op: test on i1024
plus:0.003
minus:0.005
multiply:0.16
division:0
to_string:2.01

====================================================

ms / op: test on u1024
plus:0.002
minus:0.004
multiply:0.18
division:0
to_string:2.02
```

See bench.cpp for details
