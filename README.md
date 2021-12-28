# xlogger

xlogger is a simple header only logging provider for C++ applications. Using
xlogger no need to worry about anything just copy the header file in your
project `include` directory and start using it. xlogger provides facility for
logging variables as well as l-values.

### Requirement
- C++17 or above

### Usage
```C++
#include "xlogger.hpp"

int main() {
  int x = 12;
  INFO_X_LOG("some information...");              /// uses log level INFO
  ++x;
  DEBUG_X_LOG("value of x is: ", x);              /// uses log level DEBUG
  WARN_X_LOG("spawing extra instance");           /// uses log level WARN
  CRITICAL_X_LOG("executing critial operation");  /// uses log level CRITICAL
  ERROR_X_LOG("Segmentation fault");              /// uses log level ERROR
  FATAL_X_LOG("Fatal error encountered");         /// uses log level FATAL
}
```
