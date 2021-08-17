//
// Created by matteo on 17/08/21.
//

#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>
#include <string>
#include <thread>

class Logger
{
public:
  enum class LogType {
    Info,
    Warning,
    Error
  };

  using msg_t = std::tuple<LogType, std::string>;
  static void push(LogType type, const std::string &msg);

private:
  Logger() = default;
  ~Logger();

  void init();

  std::atomic_bool stop = false;
  std::mutex mtx;
  std::deque<msg_t> data;
  std::condition_variable cond;
  std::unique_ptr<std::jthread> worker;

  static Logger& instance();
  static void process();
};
