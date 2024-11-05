#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_IDENTIFIERREFERENCE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_IDENTIFIERREFERENCE_HPP

#include "networkprotocoldsl/lexer/token/identifier.hpp"
#include "networkprotocoldsl/lexer/token/punctuation.hpp"
#include "networkprotocoldsl/lexer/tokenize.hpp"
#include "networkprotocoldsl/parser/node.hpp"
#include "networkprotocoldsl/parser/tree/expression.hpp"
#include <memory>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>
#include <optional>

namespace networkprotocoldsl::parser::grammar {

class Expression;
class IdentifierReferenceParameter : public support::RecursiveParser<IdentifierReferenceParameter> {
public:
    static void partial_match(){}
    static void partial_match(lexer::token::Identifier){}
    static Expression* recurse_one(lexer::token::Identifier, lexer::token::punctuation::Equal){return nullptr;}
    static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, 
                                  lexer::token::Identifier name, lexer::token::punctuation::Equal, tree::Expression expr) {

        return { std::make_shared<const tree::Property>(name.name, expr), begin, end };
    }
};

class IdentifierReferenceParameters : public support::RecursiveParser<IdentifierReferenceParameters> {
public:
    static void partial_match(){}
    static IdentifierReferenceParameter* recurse_many(lexer::token::punctuation::AngleBracketOpen){return nullptr;}
    static void recurse_many_has_separator(lexer::token::punctuation::AngleBracketOpen){}
    static void recurse_many_separator(lexer::token::punctuation::AngleBracketOpen, lexer::token::punctuation::Comma){}
    static void partial_match(lexer::token::punctuation::AngleBracketOpen,std::vector<tree::PropertyPtr>){}
    static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::punctuation::AngleBracketOpen, std::vector<tree::PropertyPtr> prop, lexer::token::punctuation::AngleBracketClose) {
        auto dict = std::make_shared<tree::Dictionary>();
        for (auto p : prop) {
            if (dict->find(p->name) != dict->end()) {
                return { std::nullopt, begin, end };
            }
            dict->insert({ p->name, p->value });
        }
        return { dict, begin, end };
    }
};

class IdentifierReference : public support::RecursiveParser<IdentifierReference> {
public:
    static void partial_match(){}
    static IdentifierReferenceParameters* recurse_maybe(lexer::token::Identifier) { return nullptr; }
    static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::Identifier name, std::nullopt_t) {
        return {std::make_shared<const tree::IdentifierReference>(name.name), begin,
                end};
    }
    static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::Identifier name, tree::Expression parameters) {
        return std::visit([&](auto& t){ return parse(begin, end, name, t);}, parameters);
    }

    static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::Identifier name, tree::DictionaryPtr parameters) {
        return { std::make_shared<const tree::ParameterizedIdentifierReference>(std::make_shared<const tree::IdentifierReference>(name.name), parameters),
                begin,end};
    }
};

}

#endif
