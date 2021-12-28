#pragma once

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <iostream>
#include <unordered_map>

namespace xlogger {
enum xlogger_color {
  RESET,
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  BOLD_BLACK,
  BOLD_RED,
  BOLD_GREEN,
  BOLD_YELLOW,
  BOLD_BLUE,
  BOLD_MAGENTA,
  BOLD_CYAN,
  BOLD_WHITE
};

enum xlogger_log_level { INFO, DEBUG, WARN, CRITICAL, ERROR, FATAL };

class xlogger {
private:
  xlogger_log_level log_level;
  std::unordered_map<xlogger_color, std::string> xlogger_color_map;
  xlogger_color loglevel;
  template <typename Args> void log_single(Args &&arg) {
    std::cout << " " << std::forward<decltype(arg)>(arg);
  }

  std::string get_timestamp() {
    auto instant =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const char *x = std::ctime(&instant);
    std::string timestamp;
    for (int i = 0; x[i] != '\n'; i++)
      timestamp.push_back(x[i]);
    return timestamp;
  }

public:
  xlogger() {
    xlogger_color_map[RESET] = "\033[0m";
    xlogger_color_map[BLACK] = "\033[30m";
    xlogger_color_map[RED] = "\033[31m";
    xlogger_color_map[GREEN] = "\033[32m";
    xlogger_color_map[YELLOW] = "\033[33m";
    xlogger_color_map[BLUE] = "\033[34m";
    xlogger_color_map[MAGENTA] = "\033[35m";
    xlogger_color_map[CYAN] = "\033[36m";
    xlogger_color_map[WHITE] = "\033[37m";
    xlogger_color_map[BOLD_BLACK] = "\033[1m\033[30m";
    xlogger_color_map[BOLD_RED] = "\033[1m\033[31m";
    xlogger_color_map[BOLD_GREEN] = "\033[1m\033[32m";
    xlogger_color_map[BOLD_YELLOW] = "\033[1m\033[33m";
    xlogger_color_map[BOLD_BLUE] = "\033[1m\033[34m";
    xlogger_color_map[BOLD_MAGENTA] = "\033[1m\033[35m";
    xlogger_color_map[BOLD_CYAN] = "\033[1m\033[36m";
    xlogger_color_map[BOLD_WHITE] = "\033[1m\033[37m";
  }
  ~xlogger() {}

  void set_log_level(xlogger_log_level log_level) {
    this->log_level = log_level;
  }

  xlogger_log_level get_log_level() { return this->log_level; }

  template <typename... Args> void log_multi(Args &&...args) {
    switch (log_level) {
    case INFO:
      std::cout << xlogger_color_map[GREEN] << "[INFO";
      break;
    case DEBUG:
      std::cout << xlogger_color_map[CYAN] << "[DEBUG";
      break;
    case WARN:
      std::cout << xlogger_color_map[YELLOW] << "[WARN";
      break;
    case CRITICAL:
      std::cout << xlogger_color_map[MAGENTA] << "[CRITICAL";
      break;
    case ERROR:
      std::cout << xlogger_color_map[RED] << "[ERROR";
      break;
    case FATAL:
      std::cout << xlogger_color_map[BOLD_RED] << "[FATAL";
      break;
    default:
      std::cout << xlogger_color_map[GREEN] << "[INFO";
    }
    std::cout << ": " << get_timestamp() << "] " << xlogger_color_map[RESET];
    (log_single(std::forward<Args>(args)), ...);
    std::cout << "\n";
  }
};
static xlogger *logger = new xlogger();
} // namespace xlogger

#define INFO_X_LOG(...)                                                        \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::INFO);            \
  xlogger::logger->log_multi(__VA_ARGS__)

#define DEBUG_X_LOG(...)                                                       \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::DEBUG);           \
  xlogger::logger->log_multi(__VA_ARGS__)

#define WARN_X_LOG(...)                                                        \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::WARN);            \
  xlogger::logger->log_multi(__VA_ARGS__)

#define CRITICAL_X_LOG(...)                                                    \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::CRITICAL);        \
  xlogger::logger->log_multi(__VA_ARGS__)

#define ERROR_X_LOG(...)                                                       \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::ERROR);           \
  xlogger::logger->log_multi(__VA_ARGS__)

#define FATAL_X_LOG(...)                                                       \
  xlogger::logger->set_log_level(xlogger::xlogger_log_level::FATAL);           \
  xlogger::logger->log_multi(__VA_ARGS__)
