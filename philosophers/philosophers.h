#pragma once

#include <mutex>


class Fork {
 public:
  Fork(size_t id) : id_(id) {
  }

  size_t Id() const {
    return id_;
  }

  void Get() {
    mutex_.lock();
  }

  bool TryGet() {
    return mutex_.try_lock();
  }

  void Put() {
    mutex_.unlock();
  }

 private:
  size_t id_;
  std::mutex mutex_;
};

class Philosopher {
 public:
  Philosopher(size_t id, Fork* left_fork, Fork* right_fork)
    : id_(id)
    , min_id_fork_(left_fork)
    , max_id_fork_(right_fork)
    {
      if (min_id_fork_->Id() > max_id_fork_->Id()) {
          std::swap(min_id_fork_, max_id_fork_);
      }
    }

  size_t Id() const {
    return id_;
  }

  void Eat() {
    min_id_fork_->Get();
    max_id_fork_->Get();
  }

  void Think() {
    max_id_fork_->Put();
    min_id_fork_->Put();
  }

 private:
  const size_t id_;
  Fork* min_id_fork_;
  Fork* max_id_fork_;
};

