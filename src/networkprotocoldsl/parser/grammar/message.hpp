#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_MESSAGE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_MESSAGE_HPP

#include <networkprotocoldsl/parser/grammar/property.hpp>
#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>

namespace networkprotocoldsl::parser::grammar {

class Message : public support::RecursiveParser<Message> {
public:
  static void search_space(lexer::token::keyword::Message m){};
  static void search_space(lexer::token::keyword::Message m,
                           lexer::token::literal::String name){};
  static void search_space(lexer::token::keyword::Message m,
                           lexer::token::literal::String name,
                           lexer::token::punctuation::CurlyBraceOpen c){};

  using RecursiveParser::parse;
  static ParseStateReturn parse(lexer::TokenIterator begin,
                                lexer::TokenIterator end,
                                lexer::token::keyword::Message m,
                                lexer::token::literal::String name,
                                lexer::token::punctuation::CurlyBraceOpen c) {
    std::shared_ptr<tree::Dictionary> properties =
        std::make_shared<tree::Dictionary>();
    while (true) {
      if (begin == end)
        return {std::nullopt, begin, end};
      auto next_statement = Property::parse(begin, end);
      auto nodeopt = next_statement.node;
      if (!nodeopt.has_value()) {
        break;
      } else {
        ParseNode node = nodeopt.value();
        if (!std::holds_alternative<tree::Expression>(node)) {
          return {std::nullopt, begin, end};
        }
        auto expr = std::get<tree::Expression>(node);
        if (!std::holds_alternative<tree::PropertyPtr>(expr)) {
          return {std::nullopt, begin, end};
        }
        auto prop = std::get<tree::PropertyPtr>(expr);
        if (properties->find(prop->name) != properties->end()) {
          return {std::nullopt, begin, end};
        }
        begin = next_statement.begin;
        properties->insert({prop->name, prop->value});
      }
    }
    if (begin == end)
      return {std::nullopt, begin, end};
    if (std::holds_alternative<lexer::token::punctuation::CurlyBraceClose>(
            *begin)) {
      begin++;
      tree::MessagePtr node =
          std::make_shared<const tree::Message>(name.value, properties);
      return {node, begin, end};
    } else {
      return {std::nullopt, begin, end};
    }
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif