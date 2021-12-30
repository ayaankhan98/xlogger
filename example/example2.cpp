#include <xlogger.hpp>

int main() {
  /// pass the filepath of file in which you wish to preserve the logs.
  xlogger::init_xlogger("log_0_file.xlog");

  /// Log some stuff as usuall
  INFO_X_LOG("Loggin information");

  /// Destroy xlogger context
  xlogger::destroy_xlogger();
}
