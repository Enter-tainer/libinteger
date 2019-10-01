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

## Performance

```
ms / op: test on i1024
plus:0.094
minus:0.176
multiply:43.74
division:0.53
to_string:33.35

====================================================

ms / op: test on u1024
plus:0.088
minus:0.176
multiply:43.08
division:0
to_string:33.01
```

See bench.cpp for details
