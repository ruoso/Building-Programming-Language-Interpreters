#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_PROPERTY_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_PROPERTY_HPP

#include "networkprotocoldsl/lexer/token/punctuation.hpp"
#include "networkprotocoldsl/parser/tree/expression.hpp"
#include <cstddef>
#include <networkprotocoldsl/parser/grammar/expression.hpp>
#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>

namespace networkprotocoldsl::parser::grammar {

class Property : public support::RecursiveParser<Property> {
public:
  static void partial_match(){};
  static void partial_match(lexer::token::Identifier){};
  static Expression* recurse_one(lexer::token::Identifier,
                                lexer::token::punctuation::KeyValueSeparator) {
    return nullptr;
  }
  static void partial_match(lexer::token::Identifier,
                            lexer::token::punctuation::KeyValueSeparator,
                            tree::Expression) {}

  static ParseStateReturn match(lexer::TokenIterator begin,
                                lexer::TokenIterator end,
                                lexer::token::Identifier name,
                                lexer::token::punctuation::KeyValueSeparator,
                                tree::Expression expr,
                                lexer::token::punctuation::StatementEnd) {
    tree::PropertyPtr prop =
        std::make_shared<const tree::Property>(name.name, expr);
    return {prop, begin, end};
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif