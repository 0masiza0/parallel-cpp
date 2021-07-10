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
    cv_.notify_all();
  }

  T Pop() {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [&]() {return !queue_.empty();});
    auto value = queue_.front();
    queue_.pop();
    return value;
  }

  std::optional<T> TryPop() {
    std::unique_lock lock(mutex_);
    if (queue_.empty()) {
        return std::optional<T>();
    }
    auto value = queue_.front();
    queue_.pop();
    return value;
  }


 private:
  std::mutex mutex_;
  std::condition_variable cv_;
  std::queue<T> queue_;
};

