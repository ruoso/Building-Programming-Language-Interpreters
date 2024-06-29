#ifndef INCLUDED_NETWORKPROTOCOLDSL_PARSER_SUPPORT_RECURSIVEPARSER_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_PARSER_SUPPORT_RECURSIVEPARSER_HPP

#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/node.hpp>

#include <iostream>

namespace networkprotocoldsl::parser::support {

template <class ParserContext> class RecursiveParser {
public:
  template <typename... Args>
  static ParseStateReturn parse(lexer::TokenIterator begin,
                                lexer::TokenIterator end, Args... args) {
    if constexpr (sizeof...(args) == 0 || is_in_search_space<Args...>::value) {
      if (begin == end) {
        return {std::nullopt, begin, end};
      }
      auto token = *begin++;
      return std::visit(
          [=](auto t) { return ParserContext::parse(begin, end, args..., t); },
          token);
    } else {
      return {std::nullopt, begin, end};
    }
  }

private:
  template <typename... Args> struct is_in_search_space {
    template <typename T>
    static constexpr auto check(T *)
        -> decltype(std::declval<T>().search_space(std::declval<Args>()...),
                    std::true_type{});

    template <typename> static constexpr std::false_type check(...);

    using type = decltype(check<ParserContext>(nullptr));
    static constexpr bool value = type::value;
  };
};

} // namespace networkprotocoldsl::parser::support

#endif