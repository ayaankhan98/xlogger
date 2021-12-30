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
  xlogger::init_xlogger("log_0_file.xlog");

  std::thread t1(function1);
  std::thread t2(function2);

  for (int i = 100; i < 150; i++) {
    ERROR_X_LOG("Thread Main: i = ", i);
  }

  t1.join();
  t2.join();

  xlogger::destroy_xlogger();
  return 0;
}
