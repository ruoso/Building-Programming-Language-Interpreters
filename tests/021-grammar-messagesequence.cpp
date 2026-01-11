#include <networkprotocoldsl/lexer/token.hpp>
#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/grammar/messagesequence.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <vector>

using namespace networkprotocoldsl;

TEST(Test_021_grammar_messagesequence, SingleMessagePartMatch) {
  auto maybe_tokens = lexer::tokenize("tokens { \"stringLiteral\" }");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessagePart::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
}

TEST(Test_021_grammar_messagesequence, SingleMessageSequenceMatch) {
  auto maybe_tokens = lexer::tokenize("tokens { \"stringLiteral\" }");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessageSequence::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
}

TEST(Test_021_grammar_messagesequence, SingleMessageSequenceMatch2) {
  auto maybe_tokens = lexer::tokenize("terminator { \"stringLiteral\" }");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessageSequence::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
}

TEST(Test_021_grammar_messagesequence, MessageFor) {
  auto maybe_tokens =
      lexer::tokenize("for i in list { tokens { \"stringLiteral\" } }");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessageForLoop::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
}

TEST(Test_021_grammar_messagesequence, LongMessageSequenceMatch) {
  auto maybe_tokens =
      lexer::tokenize("    tokens { verb } "
                      "    terminator { \" \" } "
                      "    tokens { request_target } "
                      "    terminator { \" \" } "
                      "    tokens { "
                      "        \"HTTP/\" major_version \".\" minor_version "
                      "    } "
                      "    terminator { \"\\r\\n\" } ");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessageSequence::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
  auto seq = std::get<std::shared_ptr<const parser::tree::MessageSequence>>(
      result.node.value());
  ASSERT_EQ(6, seq->size());
}

TEST(Test_021_grammar_messagesequence, MessageParts) {
  auto maybe_tokens =
      lexer::tokenize("parts {"
                      "    tokens { verb } "
                      "    terminator { \" \" } "
                      "    tokens { request_target } "
                      "    terminator { \" \" } "
                      "    tokens { "
                      "        \"HTTP/\" major_version \".\" minor_version "
                      "    } "
                      "    terminator { \"\\r\\n\" }"
                      "} ");
  ASSERT_TRUE(maybe_tokens.has_value());
  std::vector<lexer::Token> &tokens = maybe_tokens.value();
  auto result =
      parser::grammar::MessageParts::parse(tokens.cbegin(), tokens.cend());
  ASSERT_EQ(result.begin, tokens.cend());
  ASSERT_TRUE(result.node.has_value());
  auto seq = std::get<std::shared_ptr<const parser::tree::MessageSequence>>(
      result.node.value());
  ASSERT_EQ(6, seq->size());
}
