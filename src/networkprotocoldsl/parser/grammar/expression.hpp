#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_EXPRESSION_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_EXPRESSION_HPP

#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>

namespace networkprotocoldsl::parser::grammar {

class Expression : public support::RecursiveParser<Expression> {
public:
  static void search_space(lexer::token::Identifier name){};

  using RecursiveParser::parse;
  static ParseStateReturn parse(lexer::TokenIterator begin,
                                lexer::TokenIterator end,
                                lexer::token::Identifier name) {
    return {std::make_shared<const tree::IdentifierReference>(name.name), begin,
            end};
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif