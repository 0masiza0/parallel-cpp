#pragma once

#include <atomic>
#include <vector>
#include <shared_mutex>

template <typename T>
class ThreadSafeVector {
 public:
  ThreadSafeVector() {
  }

  T operator[](size_t index) const {
    std::shared_lock sh_data(sh_data_);
    return vector_[index];
  }

  size_t Size() const {
    std::shared_lock sh_sz(sh_sz_);
    return vector_.size();
  }

  void PushBack(const T& value) {
    sh_sz_.lock();
    sh_cap_.lock();

    if (vector_.size() == vector_.capacity()) {
        sh_data_.lock();
        vector_.push_back(value);
        sh_data_.unlock();
    } else {
        vector_.push_back(value);
    }

    sh_cap_.unlock();
    sh_sz_.unlock();
  }

 private:
  mutable std::shared_mutex sh_data_, sh_sz_, sh_cap_;
  std::vector<T> vector_;
};

