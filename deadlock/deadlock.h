#pragma once

#include <chrono>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

class Deadlock {
 public:
  Deadlock() {
  }

  void ThreadOne() {
      mutex1.lock();
      mutex2.lock();
      std::thread thr([](){std::this_thread::sleep_for(100ms);});

      mutex1.unlock();
      mutex2.unlock();
//    if (!busy) {
//        busy = true;
//        std::thread thread1([&]() { ThreadTwo(); });
//
//    } else
//        std::this_thread::sleep_for(10ms);
  }

  void ThreadTwo() {
      mutex2.lock();
      mutex1.lock();
      std::thread thr([](){std::this_thread::sleep_for(100ms);});

      mutex2.unlock();
      mutex1.unlock();
//      if (!busy) {
//          busy = true;
//          std::thread thread1([&]() { ThreadOne(); });
//
//      } else
//          std::this_thread::sleep_for(10ms);
  }

 private:
  std::mutex mutex1;
  std::mutex mutex2;
//  std::thread thread1;
//  std::thread thread2;
//  bool busy = false;
};

