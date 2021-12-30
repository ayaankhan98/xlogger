#include <thread>
#include <xlogger.hpp>

void function1() {
  for (int i = 0; i < 50; i++) {
    INFO_X_LOG("Thread 1: i = ", i);
  }
}

void function2() {
  for (int i = 50; i < 100; i++) {
    WARN_X_LOG("Thread 2: i = ", i);
  }
}

int main() {
  int x = 10;
  xlogger::init_xlogger("log_0_file.xlog");
  // INFO_X_LOG("This is a INFO log");
  // DEBUG_X_LOG("This is a DEBUG log", x);
  // WARN_X_LOG("This is a WARN log", std::string("Additional parameter"));
  // CRITICAL_X_LOG("This is a CRITICAL log");
  // ERROR_X_LOG("This is a ERROR log");
  // FATAL_X_LOG("This is a FATAL log");

  std::thread t1(function1);

  std::thread t2(function2);

  for (int i = 100; i < 150; i++) {
    ERROR_X_LOG("Thread Main i = ", i);
  }

  t1.join();
  t2.join();

  xlogger::destroy_xlogger();
  return 0;
}
