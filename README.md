# xlogger


![xlogger](assets/xlogger.png?raw=true "xlogger")

xlogger is a simple header only logging provider for C++ applications. Using
xlogger no need to worry about anything just copy the header file in your
project `include` directory and start using it. xlogger provides facility for
logging variables as well as l-values.

### Requirement
- C++17 or above

### Features
- [x] console based logging support with different log levels and colors
- [x] single file based logging support
- [] multi file based logging
- [] thread safe logging

### Usage
- copy `xlogger.hpp` file and paste it into your project `include` directory.

```C++
#include "xlogger.hpp"
#include <string>

int main() {
  int x = 12;

  /// first initiate the xlogger
  xlogger::init_xlogger();

  /// alternatively if you wish to store logs on local disk xlogger provides
  /// file based loggin also, just to enable file based loggin you need to
  /// call set_enable_file_log() method while initiating xlogger
  /// eg:
  ///    xlogger::init_xlogger()->set_enable_file_log(true);
  ///

  INFO_X_LOG("some information...");              /// uses log level INFO
  ++x;
  DEBUG_X_LOG("value of x is: ", x);              /// uses log level DEBUG

  std::string test_val = "Test string";
  WARN_X_LOG("spawing extra instance", test_val); /// uses log level WARN
  CRITICAL_X_LOG("executing critial operation");  /// uses log level CRITICAL
  ERROR_X_LOG("Segmentation fault");              /// uses log level ERROR
  FATAL_X_LOG("Fatal error encountered");         /// uses log level FATAL

  const double PI = 3.1458;
  INFO_X_LOG("PI = ", PI, "and x = ", x, "with test_val = ", test_val);

  INFO_X_LOG(12, 24, 36, PI, test_val, "Hello world");

  /// Destroy the xlogger context before you exit
  xlogger::destroy_xlogger();
}
```
