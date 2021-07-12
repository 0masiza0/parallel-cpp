#pragma once

#include <atomic>
#include <thread>

class RWSpinLock {
 public:
  RWSpinLock() {
  }

  void LockRead() {
    for (;;) {
        auto cur_val = counter_flag_.load();
        if (cur_val & 1) {
            std::this_thread::yield();
            continue;
        }
        if (counter_flag_.compare_exchange_weak(cur_val, cur_val + 2)) {
            break;
        }
    }
  }

  void UnlockRead() {
    counter_flag_.fetch_sub(2);
  }

  void LockWrite() {
    for (;;) {
        auto cur_val = counter_flag_.load();
        if (cur_val & 1) {
            std::this_thread::yield();
            continue;
        }
        if (counter_flag_.compare_exchange_weak(cur_val, cur_val + 1)) {
            break;
        }
    }
    while (counter_flag_ != 1) {}
  }

  void UnlockWrite() {
    counter_flag_.fetch_sub(1);
  }

 private:
  std::atomic<uint64_t> counter_flag_ = 0;
};

