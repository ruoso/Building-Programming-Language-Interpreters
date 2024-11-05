#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_EXPRESSION_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_GRAMMAR_EXPRESSION_HPP

#include "networkprotocoldsl/lexer/token/punctuation.hpp"
#include "networkprotocoldsl/lexer/tokenize.hpp"
#include "networkprotocoldsl/parser/tree/expression.hpp"
#include <cstddef>
#include <memory>
#include <networkprotocoldsl/parser/node.hpp>
#include <networkprotocoldsl/parser/support/recursiveparser.hpp>
#include <networkprotocoldsl/parser/grammar/identifierreference.hpp>

#include <optional>
#include <tuple>

namespace networkprotocoldsl::parser::grammar {

class IntegerLiteral : public support::RecursiveParser<IntegerLiteral> {
public:
  static void partial_match(){}
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::literal::Integer lit) {
    return { std::make_shared<const tree::IntegerLiteral>(lit.value), begin, end };
  }
};

class Expression;
class Parenthetical : public support::RecursiveParser<Parenthetical> {
public:
  static void partial_match(){}
  static Expression* recurse_one(lexer::token::punctuation::ParenthesisOpen){return nullptr;}
  static void partial_match(lexer::token::punctuation::ParenthesisOpen, tree::Expression expr){}
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end, lexer::token::punctuation::ParenthesisOpen, tree::Expression expr, lexer::token::punctuation::ParenthesisClose) {
    return { std::make_shared<const tree::Parenthetical>(expr), begin, end };
  }
};

class PrimaryExpression : public support::RecursiveParser<PrimaryExpression> {
public:
  static std::tuple<IdentifierReference, IntegerLiteral, Parenthetical>* recurse_any(){return nullptr;}
  static ParseStateReturn match(lexer::TokenIterator begin,
                                lexer::TokenIterator end,
                                tree::Expression node) {
    return {node, begin, end}; 
  }
};

class ExpressionPrecedence2 : public support::RecursiveParser<ExpressionPrecedence2> {
public:
  static PrimaryExpression* recurse_one(){return nullptr;}
  static void partial_match(tree::Expression node) {}
  static Expression* recurse_one(tree::Expression node, lexer::token::punctuation::Plus) {return nullptr;}
  static Expression* recurse_one(tree::Expression node, lexer::token::punctuation::Minus) {return nullptr;}
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                tree::Expression lhs, lexer::Token t, tree::Expression rhs) {
    return { std::make_shared<const tree::BinaryOperator>(t, lhs, rhs), begin, end };
  }
};

class ExpressionPrecedence3 : public support::RecursiveParser<ExpressionPrecedence3> {
public:
  static std::tuple<ExpressionPrecedence2, PrimaryExpression>* recurse_any(){return nullptr;}
  static void partial_match(tree::Expression) {}
  static Expression* recurse_one(tree::Expression, lexer::token::punctuation::Multiply) {return nullptr;}
  static Expression* recurse_one(tree::Expression, lexer::token::punctuation::Divide) {return nullptr;}
  static Expression* recurse_one(tree::Expression, lexer::token::punctuation::Modulo) {return nullptr;}
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                tree::Expression lhs, lexer::Token t, tree::Expression rhs) {
    return std::visit(
      [&](auto&& lhs_in) { return parse(begin, end, lhs_in, t, rhs);}, lhs);
  }
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                auto lhs, lexer::Token t, tree::Expression rhs) {
    return std::visit(
      [&](auto&& rhs_in) { return parse(begin, end, lhs, t, rhs_in);}, rhs);
  }
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                tree::BinaryOperatorPtr lhs, lexer::Token t, tree::BinaryOperatorPtr rhs) {
      auto inner_op = std::make_shared<const tree::BinaryOperator>(t, lhs->rhs, rhs->lhs);
      auto inner_left = std::make_shared<const tree::BinaryOperator>(lhs->operator_token, lhs->lhs, inner_op);
      auto outer_op = std::make_shared<const tree::BinaryOperator>(rhs->operator_token, inner_op, rhs->rhs);
      return { outer_op, begin, end };
  }
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                auto lhs, lexer::Token t, tree::BinaryOperatorPtr rhs) {
      auto inner_op = std::make_shared<const tree::BinaryOperator>(t, lhs, rhs->lhs);
      auto outer_op = std::make_shared<const tree::BinaryOperator>(rhs->operator_token, inner_op, rhs->rhs);
      return { outer_op, begin, end };
  }
  static ParseStateReturn match(lexer::TokenIterator begin, lexer::TokenIterator end,
                                tree::BinaryOperatorPtr lhs, lexer::Token t, auto rhs) {
      auto inner_op = std::make_shared<const tree::BinaryOperator>(t, lhs->rhs, rhs);
      auto outer_op = std::make_shared<const tree::BinaryOperator>(lhs->operator_token, lhs->lhs, inner_op);
      return { outer_op, begin, end };
  }
};

class Expression : public support::RecursiveParser<Expression> {
public:
  static std::tuple<ExpressionPrecedence3, ExpressionPrecedence2, PrimaryExpression>* recurse_any(){return nullptr;}
  static ParseStateReturn match(lexer::TokenIterator begin,
                                lexer::TokenIterator end,
                                tree::Expression node) {
    return {node, begin, end}; 
  }
};

} // namespace networkprotocoldsl::parser::grammar

#endif