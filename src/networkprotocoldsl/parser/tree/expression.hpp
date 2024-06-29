#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_EXPRESSION_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_TREE_EXPRESSION_HPP

#include <networkprotocoldsl/lexer/token.hpp>

#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>

namespace networkprotocoldsl::parser::tree {

struct BinaryOperator;
using BinaryOperatorPtr = std::shared_ptr<const BinaryOperator>;

struct Dictionary;
using DictionaryPtr = std::shared_ptr<const Dictionary>;

struct IdentifierReference {
  std::string name;
};
using IdentifierReferencePtr = std::shared_ptr<const IdentifierReference>;

struct IntegerLiteral {
  int value;
};
using IntegerLiteralPtr = std::shared_ptr<const IntegerLiteral>;

struct ParameterizedIdentifierReference;
using ParameterizedIdentifierReferencePtr =
    std::shared_ptr<const ParameterizedIdentifierReference>;

struct Property;
using PropertyPtr = std::shared_ptr<const Property>;

struct StringLiteral {
  std::string value;
};
using StringLiteralPtr = std::shared_ptr<const StringLiteral>;

using Expression =
    std::variant<IntegerLiteralPtr, StringLiteralPtr, IdentifierReferencePtr,
                 ParameterizedIdentifierReferencePtr, BinaryOperatorPtr,
                 PropertyPtr, DictionaryPtr>;

struct Property {
  std::string name;
  Expression value;
};

struct BinaryOperator {
  lexer::Token operator_token;
  Expression rhs;
  Expression lhs;
};

struct Dictionary : public std::unordered_map<std::string, Expression> {};

struct ParameterizedIdentifierReference {
  IdentifierReferencePtr identifier;
  DictionaryPtr parameters;
};

} // namespace networkprotocoldsl::parser::tree

#endif