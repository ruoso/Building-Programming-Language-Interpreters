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

std::optional<std::vector<tree::MessagePtr>> parse(lexer::TokenIterator begin,
                                                   lexer::TokenIterator end) {
  std::vector<tree::MessagePtr> ret;

  while (true) {
    auto match = grammar::Message::parse(begin, end);
    if (!match.node.has_value())
      break;
    auto node = match.node.value();
    if (!std::holds_alternative<tree::MessagePtr>(node))
      return std::nullopt;
    auto msg = std::get<tree::MessagePtr>(node);
    ret.push_back(msg);
    begin = match.begin;
  }
  if (begin != end)
    return std::nullopt;

  return ret;
}

} // namespace networkprotocoldsl::parser