#pragma once

#include <ostream>
#include <string_view>

#include <thread>
#include <mutex>
#include <vector>

class HelloWorld {
 public:
  static constexpr std::string_view kHelloPrefix = "Hello, World! From thread ";

  HelloWorld(size_t n_threads)
  {
    n_threads_ = n_threads;
  }

  void SayHello(std::ostream& os) {
      std::vector<std::thread> threads;

      for (size_t i = 0; i < n_threads_ ; ++i) {
          threads.emplace_back([&]() {
              mutex_.lock();
              os << kHelloPrefix << std::this_thread::get_id() << '\n';
              mutex_.unlock();
          });
      }
      for (auto& thread : threads) {
          thread.join();
      }
  }

 private:
  size_t n_threads_;
  std::mutex mutex_;
};

