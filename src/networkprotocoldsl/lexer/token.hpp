#ifndef INCLUDED_NETWORKPROTOCOLDSL_LEXER_TOKEN_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_LEXER_TOKEN_HPP

#include <networkprotocoldsl/lexer/token/identifier.hpp>
#include <networkprotocoldsl/lexer/token/keyword.hpp>
#include <networkprotocoldsl/lexer/token/literal.hpp>
#include <networkprotocoldsl/lexer/token/punctuation.hpp>

#include <variant>

namespace networkprotocoldsl::lexer {

using Token = std::variant<

    token::punctuation::Modulo, token::punctuation::Divide,
    token::punctuation::Multiply, token::punctuation::Minus, token::keyword::In,
    token::keyword::Terminator, token::literal::String,
    token::punctuation::Plus, token::keyword::For, token::keyword::Parts,
    token::literal::Integer, token::punctuation::AngleBracketOpen,
    token::punctuation::CurlyBraceClose, token::punctuation::Equal,
    token::punctuation::StatementEnd, token::Identifier,
    token::keyword::Message, token::keyword::Tokens,
    token::punctuation::AngleBracketClose, token::punctuation::Comma,
    token::punctuation::CurlyBraceOpen, token::punctuation::KeyValueSeparator>;

}

#endif
