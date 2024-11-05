#include "networkprotocoldsl/parser/tree/expression.hpp"
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
/*
TEST(parser, basic) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: Open; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
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
TEST(parser, identifier_reference_parameters) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: Open<a=1>; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(
        std::holds_alternative<parser::tree::ParameterizedIdentifierReferencePtr>(expr));
    auto ref = std::get<parser::tree::ParameterizedIdentifierReferencePtr>(expr);
    ASSERT_EQ("Open", ref->identifier->name);
  }
}
TEST(parser, many_props) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: Open; some: thing; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(2, msg->properties->size());
}

TEST(parser, many_parameters) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: Open<a=1,b=2>; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(
        std::holds_alternative<parser::tree::ParameterizedIdentifierReferencePtr>(expr));
    auto ref = std::get<parser::tree::ParameterizedIdentifierReferencePtr>(expr);
    ASSERT_EQ("Open", ref->identifier->name);
    auto prop = ref->parameters;
    ASSERT_EQ(2, prop->size());
  }
}
TEST(parser, precedence) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: 2 + 3 * 4; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(expr));
    auto binop = std::get<parser::tree::BinaryOperatorPtr>(expr);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Plus>(binop->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(binop->lhs));
    ASSERT_EQ(2, std::get<parser::tree::IntegerLiteralPtr>(binop->lhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(binop->rhs));
    auto mult = std::get<parser::tree::BinaryOperatorPtr>(binop->rhs);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Multiply>(mult->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->lhs));
    ASSERT_EQ(3, std::get<parser::tree::IntegerLiteralPtr>(mult->lhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->rhs));
    ASSERT_EQ(4, std::get<parser::tree::IntegerLiteralPtr>(mult->rhs)->value);

  }
}
*/
TEST(parser, precedence2) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: 2 * 3 + 4; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(expr));
    auto binop = std::get<parser::tree::BinaryOperatorPtr>(expr);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Plus>(binop->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(binop->rhs));
    ASSERT_EQ(4, std::get<parser::tree::IntegerLiteralPtr>(binop->rhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(binop->lhs));
    auto mult = std::get<parser::tree::BinaryOperatorPtr>(binop->lhs);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Multiply>(mult->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->lhs));
    ASSERT_EQ(2, std::get<parser::tree::IntegerLiteralPtr>(mult->lhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->rhs));
    ASSERT_EQ(3, std::get<parser::tree::IntegerLiteralPtr>(mult->rhs)->value);
  }
}
TEST(parser, precedence3) {
  using namespace networkprotocoldsl;
  std::string input("message \"HTTP Request\" { when: 2 * 3 * 4; }");
  auto output = lexer::tokenize(input);
  auto ret = parser::parse(output->cbegin(), output->cend());

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(1, ret.value()->size());
  auto msg = ret.value()->at("HTTP Request");
  ASSERT_EQ("HTTP Request", msg->name);
  ASSERT_EQ(1, msg->properties->size());
  for (const auto &pair : *(msg->properties)) {
    ASSERT_EQ("when", pair.first);
    auto expr = pair.second;
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(expr));
    auto binop = std::get<parser::tree::BinaryOperatorPtr>(expr);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Multiply>(binop->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(binop->rhs));
    ASSERT_EQ(4, std::get<parser::tree::IntegerLiteralPtr>(binop->rhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::BinaryOperatorPtr>(binop->lhs));
    auto mult = std::get<parser::tree::BinaryOperatorPtr>(binop->lhs);
    ASSERT_TRUE(std::holds_alternative<lexer::token::punctuation::Multiply>(mult->operator_token));
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->lhs));
    ASSERT_EQ(2, std::get<parser::tree::IntegerLiteralPtr>(mult->lhs)->value);
    ASSERT_TRUE(std::holds_alternative<parser::tree::IntegerLiteralPtr>(mult->rhs));
    ASSERT_EQ(3, std::get<parser::tree::IntegerLiteralPtr>(mult->rhs)->value);
  }
}