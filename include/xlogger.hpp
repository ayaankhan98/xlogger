#pragma once

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
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

class xlogger_core {
private:
  xlogger_log_level _log_level;
  std::unordered_map<xlogger_color, std::string> _xlogger_color_map;

public:
  xlogger_core() {
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

  virtual ~xlogger_core() {}

  inline xlogger_log_level get_log_level() const { return this->_log_level; }

  virtual inline void set_log_level(const xlogger_log_level &log_level) {
    this->_log_level = log_level;
  }

  inline std::string get_xlogger_color(const xlogger_color &color) {
    return this->_xlogger_color_map[color];
  }

  const std::string get_timestamp() {
    auto current_instant = std::chrono::system_clock::now();
    auto current_instant_time_t =
        std::chrono::system_clock::to_time_t(current_instant);
    const char *x = std::ctime(&current_instant_time_t);
    std::string timestamp;
    for (int i = 0; x[i] != '\n'; i++)
      timestamp.push_back(x[i]);
    return timestamp;
  }
};

class xfile_logger : public xlogger_core {
private:
  std::ofstream *_file_handler;
  std::string _filepath;

  template <typename Args> void log(Args &&arg) {
    *_file_handler << std::forward<decltype(arg)>(arg);
  }

public:
  xfile_logger() { _file_handler = new std::ofstream(); }

  xfile_logger(const std::string &filepath) : _filepath(filepath) {
    _file_handler = new std::ofstream();
    _file_handler->open(_filepath);
  }

  virtual ~xfile_logger() {
    if (_file_handler->is_open())
      _file_handler->close();
  }

  template <typename... Args> void logger(Args &&...args) {
    switch (get_log_level()) {
    case _INFO:
      log("[INFO");
      break;

    case _DEBUG:
      log("[DEBUG");
      break;

    case _WARN:
      log("[WARN");
      break;

    case _CRITICAL:
      log("[CRITICAL");
      break;

    case _ERROR:
      log("[ERROR");
      break;

    case _FATAL:
      log("[FATAL");
      break;

    default:
      log("[INFO");
      break;
    }
    log(": " + get_timestamp() + "] ");
    (log(std::forward<Args>(args)), ...);
    log("\n");
  }
};

class xconsole_logger : public xlogger_core {
private:
  template <typename Args> void log(Args &&arg) {
    std::cout << std::forward<decltype(arg)>(arg);
  }

public:
  xconsole_logger() {}
  virtual ~xconsole_logger() {}

  template <typename... Args> void logger(Args &&...args) {
    switch (get_log_level()) {
    case _INFO:
      log(get_xlogger_color(_GREEN) + "[INFO");
      break;

    case _DEBUG:
      log(get_xlogger_color(_CYAN) + "[DEBUG");
      break;

    case _WARN:
      log(get_xlogger_color(_YELLOW) + "[WARN");
      break;

    case _CRITICAL:
      log(get_xlogger_color(_MAGENTA) + "[CRITICAL");
      break;

    case _ERROR:
      log(get_xlogger_color(_RED) + "[ERROR");
      break;

    case _FATAL:
      log(get_xlogger_color(_BOLD_RED) + "[FATAL");
      break;

    default:
      log(get_xlogger_color(_GREEN) + "[INFO");
      break;
    }
    log(": " + get_timestamp() + "] ");
    (log(std::forward<Args>(args)), ...);
    log("\n" + get_xlogger_color(_RESET));
  }
};

enum xlogger_type { _FILE, _CONSOLE };

class xlogger : private xfile_logger, private xconsole_logger {
private:
  static xlogger *_logger;
  bool _type_file;
  bool _type_console;
  std::mutex _mtx;

public:
  xlogger() : xfile_logger(), _type_console(true), _type_file(false) {}

  xlogger(const std::string &filepath)
      : xfile_logger(filepath), _type_console(true), _type_file(true) {}

  virtual ~xlogger() {}

  inline bool get_type_file() const { return this->_type_file; }

  inline void set_type_file(bool type_file) { this->_type_file = type_file; }

  inline bool get_type_console() const { return this->_type_console; }

  inline void set_type_console(bool type_console) {
    this->_type_console = type_console;
  }

  static xlogger *get_logger() {
    if (!_logger)
      _logger = new xlogger();
    return _logger;
  }

  static xlogger *get_logger(const std::string &filepath) {
    if (!_logger)
      _logger = new xlogger(filepath);
    return _logger;
  }

  template <typename... Args>
  void logger(const xlogger_log_level &log_level, Args &&...args) {
    std::lock_guard<std::mutex> locker(_mtx);
    if (_type_file) {
      xfile_logger::set_log_level(log_level);
      xfile_logger::logger(args...);
    }
    if (_type_console) {
      xconsole_logger::set_log_level(log_level);
      xconsole_logger::logger(args...);
    }
  }
};

xlogger *init_xlogger() {
  xlogger *logger = logger->get_logger();
  return logger;
}

xlogger *init_xlogger(const std::string &filepath) {
  xlogger *logger = logger->get_logger(filepath);
  return logger;
}

void destroy_xlogger() { delete xlogger::xlogger::get_logger(); }
} // namespace xlogger

xlogger::xlogger *xlogger::xlogger::_logger = nullptr;

#define INFO_X_LOG(...)                                                        \
  xlogger::xlogger::get_logger()->logger(xlogger::xlogger_log_level::_INFO,    \
                                         __VA_ARGS__)

#define DEBUG_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->logger(xlogger::xlogger_log_level::_DEBUG,   \
                                         __VA_ARGS__)

#define WARN_X_LOG(...)                                                        \
  xlogger::xlogger::get_logger()->logger(xlogger::xlogger_log_level::_WARN,    \
                                         __VA_ARGS__)

#define CRITICAL_X_LOG(...)                                                    \
  xlogger::xlogger::get_logger()->logger(                                      \
      xlogger::xlogger_log_level::_CRITICAL, __VA_ARGS__)

#define ERROR_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->logger(xlogger::xlogger_log_level::_ERROR,   \
                                         __VA_ARGS__)

#define FATAL_X_LOG(...)                                                       \
  xlogger::xlogger::get_logger()->logger(xlogger::xlogger_log_level::_FATAL,   \
                                         __VA_ARGS__)
