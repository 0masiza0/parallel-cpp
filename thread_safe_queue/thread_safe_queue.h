#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>


template <typename T>
class ThreadSafeQueue {
 public:
  ThreadSafeQueue() {
  }

  void Push(const T& value) {
    std::unique_lock lock(mutex_);
    queue_.push(value);
    cv.notify_all();
  }

  T Pop() {
    std::unique_lock lock(mutex_);
    cv.wait(lock, [&]() {return !queue_.empty();});
    auto value = queue_.front();
    queue_.pop();
    return value;
  }

  std::optional<T> TryPop() {
    bool free = mutex_.try_lock();
    if (!free || queue_.empty()) {
      if (free)
          mutex_.unlock();
      return std::nullopt;
    }
    auto value = queue_.front();
    queue_.pop();
    mutex_.unlock();
    return value;
  }


 private:
  std::mutex mutex_;
  std::condition_variable cv;
  std::queue<T> queue_;
};

