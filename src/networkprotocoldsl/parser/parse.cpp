#include <networkprotocoldsl/lexer/token.hpp>
#include <networkprotocoldsl/parser/grammar/message.hpp>
#include <networkprotocoldsl/parser/parse.hpp>
#include <networkprotocoldsl/parser/tree/message.hpp>

#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

namespace networkprotocoldsl::parser {

std::optional<tree::MessagesPtr> parse(lexer::TokenIterator begin,
                                       lexer::TokenIterator end) {
  auto ret = grammar::Messages::parse(begin, end);
  if (ret.node.has_value() && std::holds_alternative<tree::MessagesPtr>(ret.node.value())) {
    return std::get<tree::MessagesPtr>(ret.node.value());
  } else {
    return std::nullopt;
  }
}

} // namespace networkprotocoldsl::parser