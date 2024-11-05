#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_PROPERTY_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_PROPERTY_HPP

#include <networkprotocoldsl/parser/tree/expression.hpp>

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace networkprotocoldsl::parser::tree {

struct Property {
  std::string name;
  Expression value;
};
using PropertyPtr = std::shared_ptr<const Property>;

} // namespace networkprotocoldsl::parser::tree

#endif