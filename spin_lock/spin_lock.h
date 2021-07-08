#pragma once

#include <atomic>

class SpinLock {
 public:
  SpinLock() {
  }

  void Lock() {
    while (flag.test_and_set()) {}
  }

  void Unlock() {
    flag.clear();
  }

 private:
  std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

