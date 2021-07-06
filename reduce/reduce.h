#pragma once

#include <cstddef>
#include <thread>
#include <vector>

template <typename RandomAccessIterator, class T, class Func>
T parallel_reduce(RandomAccessIterator begin, RandomAccessIterator end,
                  const T& initial_value, Func func, size_t n_threads) {
  size_t range_size = end - begin;
  size_t sub_range_size = range_size / n_threads;

  // If we have too many threads, we can't use all of them anyway.
  // How to optimise "parallel-reduce" in this case is a "highly debatable issue",
  // so if my solution is not satisfying, please let me know how to do the realisation properly.
  // Sincerely, 0masiza0
  if (sub_range_size == 0) {
      ++sub_range_size;
      n_threads = range_size;
  }
  T result = initial_value;

  std::vector<std::thread> threads;
  std::vector<T> cur_results(n_threads);
  for (size_t i = 0; i < n_threads; ++i) {
      auto cur_end = i + 1 == n_threads ? end : std::next(begin, sub_range_size);
      threads.emplace_back([&, i](auto begin, auto end) {
          T cur_result = *begin++;
          while (begin != end) {
              cur_result = func(cur_result, *begin++);
          }
          cur_results[i] = cur_result;
      }, begin, cur_end);
      std::advance(begin, sub_range_size);
  }
  for (size_t i = 0; i < n_threads; ++i) {
      threads[i].join();
      result = func(result, cur_results[i]);
  }
  return result;
}

