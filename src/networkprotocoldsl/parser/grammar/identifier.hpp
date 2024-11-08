#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_IDENTIFIER_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_IDENTIFIER_HPP

#include <memory>

#include <networkprotocoldsl/lexer/token/identifier.hpp>
#include <networkprotocoldsl/parser/grammar/traits.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>
#include <networkprotocoldsl/parser/tree/identifierreference.hpp>

namespace networkprotocoldsl::parser::grammar {

class IdentifierReference
    : public support::RecursiveParser<IdentifierReference, ParseTraits> {
public:
  static void partial_match() {}
  static ParseStateReturn match(TokenIterator begin, TokenIterator end,
                                lexer::token::Identifier i) {
    return {std::make_shared<tree::IdentifierReference>(i.name), begin, end};
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif