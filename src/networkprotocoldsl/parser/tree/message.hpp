#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_MESSAGE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_MESSAGE_HPP

#include <networkprotocoldsl/parser/tree/expression.hpp>

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace networkprotocoldsl::parser::tree {

struct Message {
  std::string name;
  DictionaryPtr properties;
};
using MessagePtr = std::shared_ptr<const Message>;

struct Messages : public std::unordered_map<std::string, MessagePtr> {
};
using MessagesPtr = std::shared_ptr<const Messages>;

} // namespace networkprotocoldsl::parser::tree

#endif