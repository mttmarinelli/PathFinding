//
// Created by matteo on 17/08/21.
//

#include "Logger.h"
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

void Logger::init()
{
  instance().worker = std::make_unique<std::jthread>(&Logger::process);
}

Logger::~Logger()
{
  auto &log = instance();

  log.stop = true;

  if (log.worker)
  {
    log.worker->join();
  }
}

void Logger::push(Logger::LogType type, const std::string &msg)
{
  auto &log = instance();
  
  if (!log.worker)
    log.init();

  std::scoped_lock lck(log.mtx);

  log.data.emplace_back(type, msg);
  log.cond.notify_one();
}

void Logger::process()
{
  auto &log = instance();
  
  while (!log.stop)
  {
    std::unique_lock lck(log.mtx);
    if (!log.cond.wait_for(lck, std::chrono::seconds(2), [&log]() {
          return !log.data.empty();
        }))
      continue;

    auto [type, str] = log.data.front();
    log.data.pop_front();
    lck.unlock();

    const auto clr = type == LogType::Info ?    fmt::color::white :
                     type == LogType::Warning ? fmt::color::yellow :
                                                fmt::color::red;

    std::time_t t = std::time(nullptr);
    fmt::print(fmt::fg(clr), "[{:%Y-%m-%d}, {:%H:%M:%S}]: {}\n", fmt::localtime(t), fmt::gmtime(t), str);
  }
}

Logger &Logger::instance()
{
  static Logger log;
  return log;
}
