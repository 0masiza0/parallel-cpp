#pragma once

#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

class Deadlock {
 public:
  Deadlock() {
  }

  void ThreadOne() {
      mutex1_.lock();
      std::this_thread::sleep_for(10ms);
      mutex2_.lock();
      mutex1_.unlock();
      mutex2_.unlock();
  }

  void ThreadTwo() {
      mutex2_.lock();
      std::this_thread::sleep_for(10ms);
      mutex1_.lock();
      mutex2_.unlock();
      mutex1_.unlock();
  }

 private:
    std::mutex mutex1_;
    std::mutex mutex2_;
};

