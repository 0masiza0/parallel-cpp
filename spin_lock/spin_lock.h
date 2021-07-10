#pragma once

#include <atomic>
#include <thread>

class SpinLock {
 public:
  SpinLock() {
  }

  void Lock() {
      for (;;) {
          if (!locked_.exchange(true)) {
              return;
          }
          while (locked_.load()) {
              std::this_thread::yield();
          }
      }
  }

  void Unlock() {
    locked_.store(false);
  }

 private:
  std::atomic<bool> locked_ = false;
};

