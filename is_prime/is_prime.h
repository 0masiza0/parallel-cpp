#pragma once

#include <cstdint>

inline bool IsPrime(uint64_t x) {
    if (x <= 3) {
        return x > 1;
    }
    if (x % 2 == 0) {
        return false;
    }
    for (uint64_t divisor = 3; divisor * divisor <= x; divisor += 2) {
          if (x % divisor == 0) {
              return false;
          }
      }
    return true;
}

