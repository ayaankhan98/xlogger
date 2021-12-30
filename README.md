# xlogger


![xlogger](assets/xlogger_1_.svg?raw=true "xlogger")

xlogger is a simple header only logging provider for C++ applications. Using
xlogger no need to worry about anything just copy the header file in your
project `include` directory and start using it. xlogger provides facility for
logging variables as well as l-values.

### Requirement
- C++17 or above

### Features
- [x] console based logging support with different log levels and colors
- [x] single file based logging support
- [x] thread safe logging
- [ ] multi file based logging

### Usage
- copy `xlogger.hpp` file and paste it into your project `include` directory.

- #### Available Logging Macros
  - `INFO_X_LOG()`
  - `DEBUG_X_LOG()`
  - `WARN_X_LOG()`
  - `CRITICAL_X_LOG()`
  - `ERROR_X_LOG()`
  - `FATAL_X_LOG()`


- #### Logging in Console
  Console logger is enabled by default. Need not to do anything just initiate
  the xlogger context and start using it. And at the end don't forget to
  destroy xlogger context.

  Code example:
  ```C++
    #include <string>
    #include <unordered_map>
    #include <xlogger.hpp>

    std::unordered_map<std::string, std::string> fetch_from_server() {
      std::unordered_map<std::string, std::string> response;
      response["username"] = "foo bar";
      response["email"] = "foo@example.com";
      response["dob"] = "10-10-1999";
      return response;
    }

    int main() {
      /// Initiate a xlogger context
      xlogger::init_xlogger();

      INFO_X_LOG("Welcome to xlogger");

      const double PI = 3.145;
      INFO_X_LOG("Value of PI = ", PI);

      auto response = fetch_from_server();
      DEBUG_X_LOG("Response from server: [username: ", response["username"],
                 ", email: ", response["email"], ", dob", response["dob"], "]");

      /// Destroy the xlogger context before you exit
      xlogger::destroy_xlogger();
      return 0;
    }
  ```

- #### Using a File logger
  File logger can be used to preserve the logs on local disk.

  code example:

  ```C++
  #include <xlogger.hpp>

  int main() {
    /// pass the filepath of file in which you wish to preserve the logs.
    xlogger::init_xlogger("log_0_file.xlog");

    /// Log some stuff as usuall
    INFO_X_LOG("Loggin information");

    /// Destroy xlogger context
    xlogger::destroy_xlogger();
  }
  ```

  if you wish to just use xlogger as file logger, you can disable console based
  logging

  ```C++
  xlogger::init_xlogger("log_0_file.xlog")->set_type_console(false);
  ```

- #### Using `xlogger` in Multithreading environment
  xlogger provide thread safe logging. File logs and console logs are in sync.

  code example:

  ```C++
  #include <xlogger.hpp>
  #include <thread>

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

    for(int i = 100; i < 150; i++) {
      ERROR_X_LOG("Thread Main: i = ", i);
    }

    t1.join();
    t2.join();

    xlogger::destroy_xlogger();
    return 0;
  }
  ```
