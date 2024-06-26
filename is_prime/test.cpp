#include "is_prime.h"

#include "timeout_guard.h"
#include <gtest/gtest.h>

TEST(IsPrime, One) {
  TimeoutGuard guard(10ms);
  ASSERT_FALSE(IsPrime(1));
}

TEST(IsPrime, Two) {
  TimeoutGuard guard(10ms);
  ASSERT_TRUE(IsPrime(2));
}

TEST(IsPrime, Even) {
  TimeoutGuard guard(500ms);
  for (size_t i = 4; i < 10000000; i += 2) {
    EXPECT_FALSE(IsPrime(i));
  }
}

TEST(IsPrime, Border) {
    TimeoutGuard guard(10ms);
    ASSERT_TRUE(!IsPrime(0) && !IsPrime(UINT64_MAX));
}

TEST(IsPrime, PrimaryPowers) {
    TimeoutGuard guard(10ms);
    uint64_t three = 3, five = 5, seven = 7, eleven = 11;
    EXPECT_TRUE(IsPrime(three) && IsPrime(five) && IsPrime(seven) && IsPrime(eleven));
    for (size_t i = 0; i < 10; ++i) {
        three *= 3;
        five *= 5;
        seven *= 7;
        eleven *= 11;
        EXPECT_FALSE(IsPrime(three) || IsPrime(five) || IsPrime(seven) || IsPrime(eleven));
    }
}
