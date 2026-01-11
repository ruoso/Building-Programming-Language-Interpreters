#include <networkprotocoldsl/operation.hpp>

#include <gtest/gtest.h>

TEST(Test_003_literal_and_add_operations, literal) {
  networkprotocoldsl::operation::Int32Literal i1(10);
  networkprotocoldsl::operation::Int32Literal i2(20);
  networkprotocoldsl::operation::Add a1;
  networkprotocoldsl::Value v = a1({i1({}), i2({})});
  ASSERT_EQ(std::get<int32_t>(v), 30);
}
