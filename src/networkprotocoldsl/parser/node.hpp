#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_NODE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_NODE_HPP

#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/tree/expression.hpp>
#include <networkprotocoldsl/parser/tree/message.hpp>

#include <optional>
#include <variant>

namespace networkprotocoldsl::parser {

using ParseNode = std::variant<tree::MessagePtr, tree::Expression>;

struct ParseStateReturn {
  std::optional<ParseNode> node;
  lexer::TokenIterator begin;
  lexer::TokenIterator end;
};

} // namespace networkprotocoldsl::parser

#endif
