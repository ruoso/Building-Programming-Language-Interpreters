#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_PARSE_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_PARSE_HPP

#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/node.hpp>

#include <optional>
#include <vector>

namespace networkprotocoldsl::parser {

std::optional<std::vector<tree::MessagePtr>> parse(lexer::TokenIterator begin,
                                                   lexer::TokenIterator end);

}

#endif
