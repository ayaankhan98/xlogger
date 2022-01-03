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

  const double PI = 3.145;
  INFO_X_LOG("Value of PI = ", PI);

  auto response = fetch_from_server();
  DEBUG_X_LOG("Response from server: ", response);

  /// Destroy the xlogger context before you exit
  xlogger::destroy_xlogger();
  return 0;
}
