#pragma once

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace xlogger {
enum xlogger_color {
  _RESET,
  _BLACK,
  _RED,
  _GREEN,
  _YELLOW,
  _BLUE,
  _MAGENTA,
  _CYAN,
  _WHITE,
  _BOLD_BLACK,
  _BOLD_RED,
  _BOLD_GREEN,
  _BOLD_YELLOW,
  _BOLD_BLUE,
  _BOLD_MAGENTA,
  _BOLD_CYAN,
  _BOLD_WHITE
};

enum xlogger_log_level { _INFO, _DEBUG, _WARN, _CRITICAL, _ERROR, _FATAL };

class xlogger {
private:
  static xlogger *_logger;
  xlogger_log_level _log_level;
  bool _enable_file_log;
  std::ofstream *_file_handler;
  std::string _filepath;
  std::unordered_map<xlogger_color, std::string> _xlogger_color_map;

  template <typename Args> void log_single(Args &&arg) {
    std::cout << " " << std::forward<decltype(arg)>(arg);
    if (_enable_file_log)
      *_file_handler << " " << std::forward<decltype(arg)>(arg);
  }

  std::string get_timestamp() {
    auto current_instant = std::chrono::system_clock::now();
    auto current_instant_time_t =
        std::chrono::system_clock::to_time_t(current_instant);
    const char *x = std::ctime(&current_instant_time_t);
    std::string timestamp;
    for (int i = 0; x[i] != '\n'; i++)
      timestamp.push_back(x[i]);
    return timestamp;
  }

public:
  xlogger() : _enable_file_log(false), _filepath("log_0.xlog") {
    _xlogger_color_map[_RESET] = "\033[0m";
    _xlogger_color_map[_BLACK] = "\033[30m";
    _xlogger_color_map[_RED] = "\033[31m";
    _xlogger_color_map[_GREEN] = "\033[32m";
    _xlogger_color_map[_YELLOW] = "\033[33m";
    _xlogger_color_map[_BLUE] = "\033[34m";
    _xlogger_color_map[_MAGENTA] = "\033[35m";
    _xlogger_color_map[_CYAN] = "\033[36m";
    _xlogger_color_map[_WHITE] = "\033[37m";
    _xlogger_color_map[_BOLD_BLACK] = "\033[1m\033[30m";
    _xlogger_color_map[_BOLD_RED] = "\033[1m\033[31m";
    _xlogger_color_map[_BOLD_GREEN] = "\033[1m\033[32m";
    _xlogger_color_map[_BOLD_YELLOW] = "\033[1m\033[33m";
    _xlogger_color_map[_BOLD_BLUE] = "\033[1m\033[34m";
    _xlogger_color_map[_BOLD_MAGENTA] = "\033[1m\033[35m";
    _xlogger_color_map[_BOLD_CYAN] = "\033[1m\033[36m";
    _xlogger_color_map[_BOLD_WHITE] = "\033[1m\033[37m";
  }

  virtual ~xlogger() {}

  inline xlogger_log_level get_log_level() const { return this->_log_level; }

  inline void set_log_level(xlogger_log_level log_level) {
    this->_log_level = log_level;
  }

  inline const std::string &get_filepath() const { return this->_filepath; }

  inline void set_filepath(const std::string &filepath) {
    this->_filepath = filepath;
  }

  inline void set_enable_file_log(bool enable_file_log) {
    this->_enable_file_log = enable_file_log;
    _file_handler = new std::ofstream(this->_filepath, std::ios::out);
  }

  static xlogger *get_logger() {
    if (!_logger)
      _logger = new xlogger;
    return _logger;
  }

  inline std::ofstream *get_file_handler() const { return this->_file_handler; }

  template <typename... Args> void log_multi(Args &&...args) {
    switch (_log_level) {
    case _INFO:
      std::cout << _xlogger_color_map[_GREEN] << "[INFO";
      if (_enable_file_log)
        *_file_handler << "[INFO";
      break;
    case _DEBUG:
      std::cout << _xlogger_color_map[_CYAN] << "[DEBUG";
      if (_enable_file_log)
        *_file_handler << "[DEBUG";
      break;
    case _WARN:
      std::cout << _xlogger_color_map[_YELLOW] << "[WARN";
      if (_enable_file_log)
        *_file_handler << "[WARN";
      break;
    case _CRITICAL:
      std::cout << _xlogger_color_map[_MAGENTA] << "[CRITICAL";
      if (_enable_file_log)
        *_file_handler << "[CRITICAL";
      break;
    case _ERROR:
      std::cout << _xlogger_color_map[_RED] << "[ERROR";
      if (_enable_file_log)
        *_file_handler << "[ERROR";
      break;
    case _FATAL:
      std::cout << _xlogger_color_map[_BOLD_RED] << "[FATAL";
      if (_enable_file_log)
        *_file_handler << "[FATAL";
      break;
    default:
      std::cout << _xlogger_color_map[_GREEN] << "[INFO";
      if (_enable_file_log)
        *_file_handler << "[INFO";
    }
    std::cout << ": " << get_timestamp() << "] " << _xlogger_color_map[_RESET];
    if (_enable_file_log)
      *_file_handler << ": " << get_timestamp() << "] ";
    (log_single(std::forward<Args>(args)), ...);
    std::cout << "\n";
    if (_enable_file_log)
      *_file_handler << "\n";
  }
};

xlogger *init_xlogger() {
  xlogger *logger = logger->get_logger();
  return logger;
}

void destroy_xlogger() {
  if (xlogger::get_logger()->get_file_handler() &&
      xlogger::get_logger()->get_file_handler()->is_open())
    xlogger::get_logger()->get_file_handler()->close();

  delete xlogger::get_logger();
}

} // namespace xlogger

xlogger::xlogger *xlogger::xlogger::_logger = nullptr;

#define INFO_X_LOG(...)                                                        \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_INFO);                                      \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)

#define DEBUG_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_DEBUG);                                     \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)

#define WARN_X_LOG(...)                                                        \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_WARN);                                      \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)

#define CRITICAL_X_LOG(...)                                                    \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_CRITICAL);                                  \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)

#define ERROR_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_ERROR);                                     \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)

#define FATAL_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->set_log_level(                               \
      xlogger::xlogger_log_level::_FATAL);                                     \
  xlogger::xlogger::get_logger()->log_multi(__VA_ARGS__)
