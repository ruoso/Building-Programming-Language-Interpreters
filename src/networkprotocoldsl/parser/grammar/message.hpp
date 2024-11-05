#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_MESSAGE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_MESSAGE_HPP

#include "networkprotocoldsl/lexer/token/keyword.hpp"
#include "networkprotocoldsl/lexer/token/punctuation.hpp"
#include "networkprotocoldsl/lexer/tokenize.hpp"
#include "networkprotocoldsl/parser/tree/message.hpp"
#include "networkprotocoldsl/parser/tree/property.hpp"
#include <networkprotocoldsl/parser/grammar/property.hpp>
#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>

namespace networkprotocoldsl::parser::grammar {

class Message : public support::RecursiveParser<Message> {
public:
  static void partial_match(){};
  static void partial_match(lexer::token::keyword::Message m){}
  static void partial_match(lexer::token::keyword::Message m,
                            lexer::token::literal::String name){}
  static Property* recurse_many(lexer::token::keyword::Message m,
                              lexer::token::literal::String name,
                              lexer::token::punctuation::CurlyBraceOpen){return nullptr;}
  static void partial_match(lexer::token::keyword::Message m,
                            lexer::token::literal::String name,
                            lexer::token::punctuation::CurlyBraceOpen,
                            std::vector<tree::PropertyPtr>);

  static ParseStateReturn
  match(lexer::TokenIterator begin, lexer::TokenIterator end,
        lexer::token::keyword::Message, lexer::token::literal::String name,
        lexer::token::punctuation::CurlyBraceOpen, std::vector<tree::PropertyPtr> props,
        lexer::token::punctuation::CurlyBraceClose) {
    std::shared_ptr<tree::Dictionary> properties =
        std::make_shared<tree::Dictionary>();
    for (auto prop : props) {
      if (properties->find(prop->name) != properties->end()) {
        return {std::nullopt, begin, end};
      }
      properties->insert({prop->name, prop->value});
    }
    tree::MessagePtr node =
        std::make_shared<const tree::Message>(name.value, properties);
    return {node, begin, end};
  }
};

class Messages : public support::RecursiveParser<Messages> {
public:
  static Message* recurse_many(){return nullptr;}
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, std::vector<tree::MessagePtr> msgs) {
    auto ret = std::make_shared<tree::Messages>();
    for (auto m : msgs ) {
      if (ret->find(m->name) != ret->end()) {
        return {std::nullopt, begin, end};
      }
      ret->insert({m->name, m});
    }
    return { ret, begin, end };
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif