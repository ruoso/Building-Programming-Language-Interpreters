#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_PROPERTY_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_PROPERTY_HPP

#include <networkprotocoldsl/parser/grammar/expression.hpp>
#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>

namespace networkprotocoldsl::parser::grammar {

class Property : public support::RecursiveParser<Property> {
public:
  static void search_space(lexer::token::Identifier name){};
  static void search_space(lexer::token::Identifier name,
                           lexer::token::punctuation::KeyValueSeparator){};

  using RecursiveParser::parse;
  static ParseStateReturn
  parse(lexer::TokenIterator begin, lexer::TokenIterator end,
        lexer::token::Identifier name,
        lexer::token::punctuation::KeyValueSeparator s) {
    if (begin == end)
      return {std::nullopt, begin, end};
    auto expression = Expression::parse(begin, end);
    begin = expression.begin;
    if (!std::holds_alternative<lexer::token::punctuation::StatementEnd>(
            *begin)) {
      return {std::nullopt, begin, end};
    }
    begin++;
    auto expropt = expression.node;
    if (expropt.has_value()) {
      if (std::holds_alternative<tree::Expression>(expropt.value())) {
        tree::Expression expr = std::get<tree::Expression>(expropt.value());
        tree::PropertyPtr prop =
            std::make_shared<const tree::Property>(name.name, expr);
        return {prop, begin, end};
      } else {
        return {std::nullopt, begin, end};
      }
    } else {
      return {std::nullopt, begin, end};
    }
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif