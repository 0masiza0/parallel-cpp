#pragma once

#include <atomic>
#include <thread>

class MCSLock {
 public:
  MCSLock() {
  }

  void Lock() {
    Node* prior_node = tail_.exchange(&local_node_);

    if (prior_node != nullptr) {
        local_node_.acquired_.store(true);

        prior_node->next_ = &local_node_;

        while (local_node_.acquired_) {
            std::this_thread::yield();
        }
    }
  }

  void Unlock() {
    if (local_node_.next_ == nullptr) {
        Node* tmp = &local_node_;
        if (tail_.compare_exchange_weak(tmp, nullptr)) {
            return;
        }
        while (local_node_.next_ == nullptr) {}
    }
    local_node_.next_.load()->acquired_.store(false);
    local_node_.next_ = nullptr;
  }

 private:
  struct Node {
      std::atomic<bool> acquired_;
      std::atomic<Node*> next_;
  };
  thread_local static inline Node local_node_;
  std::atomic<Node*> tail_ = nullptr;
};
