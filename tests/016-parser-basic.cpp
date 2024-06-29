#include <networkprotocoldsl/lexer/token.hpp>
#include <networkprotocoldsl/lexer/token/identifier.hpp>
#include <networkprotocoldsl/lexer/token/literal.hpp>
#include <networkprotocoldsl/lexer/token/punctuation.hpp>
#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/parse.hpp>

#include <string>

#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

TEST(parser, basic) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: Open; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value().size());
  auto msg = ret.value().at(0);
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(
        std::holds_alternative<parser::tree::IdentifierReferencePtr>(expr));
    auto ref = std::get<parser::tree::IdentifierReferencePtr>(expr);
    ASSERT_EQ("Open", ref->name);
  }
}
