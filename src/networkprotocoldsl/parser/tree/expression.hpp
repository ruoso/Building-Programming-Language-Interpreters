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

struct StringLiteral {
  std::string value;
};
using StringLiteralPtr = std::shared_ptr<const StringLiteral>;

struct Parenthetical;
using ParentheticalPtr = std::shared_ptr<const Parenthetical>;

using Expression =
    std::variant<IntegerLiteralPtr, StringLiteralPtr, IdentifierReferencePtr,
                 ParameterizedIdentifierReferencePtr, BinaryOperatorPtr,
                 DictionaryPtr, ParentheticalPtr>;

struct BinaryOperator {
  lexer::Token operator_token;
  Expression lhs;
  Expression rhs;
};

struct Dictionary : public std::unordered_map<std::string, Expression> {};

struct ParameterizedIdentifierReference {
  IdentifierReferencePtr identifier;
  DictionaryPtr parameters;
};

struct Parenthetical {
  Expression expr;
};

} // namespace networkprotocoldsl::parser::tree

#endif