#include "xlogger.hpp"

int main() {
  int x = 10;
  INFO_X_LOG("This is a INFO log");
  DEBUG_X_LOG("This is a DEBUG log", x);
  WARN_X_LOG("This is a WARN log", std::string("Additional parameter"));
  CRITICAL_X_LOG("This is a CRITICAL log");
  ERROR_X_LOG("This is a ERROR log");
  FATAL_X_LOG("This is a FATAL log");
  return 0;
}

