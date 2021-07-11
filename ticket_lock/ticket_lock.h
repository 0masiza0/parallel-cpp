#pragma once

#include <atomic>
#include <thread>

class TicketLock {
 public:
  TicketLock() {
  }

  void Lock() {
      auto my_ticket = next_ticket_.fetch_add(1);
      while (my_ticket != now_serving_.load()) {
          std::this_thread::yield();
      }
  }

  void Unlock() {
      now_serving_.fetch_add(1);
  }

 private:
    std::atomic<uint64_t> now_serving_ = 0;
    std::atomic<uint64_t> next_ticket_ = 0;
};

