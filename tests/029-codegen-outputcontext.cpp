#include <networkprotocoldsl/codegen/outputcontext.hpp>

#include <cctype>
#include <gtest/gtest.h>

using namespace networkprotocoldsl::codegen;

TEST(Test_029_codegen_outputcontext, OpenNamespace) {
  OutputContext ctx("myapp::smtp");
  EXPECT_EQ(ctx.open_namespace(), "namespace myapp::smtp {\n");
}

TEST(Test_029_codegen_outputcontext, CloseNamespace) {
  OutputContext ctx("myapp::smtp");
  EXPECT_EQ(ctx.close_namespace(), "} // namespace myapp::smtp\n");
}

TEST(Test_029_codegen_outputcontext, SimpleNamespace) {
  OutputContext ctx("protocol");
  EXPECT_EQ(ctx.open_namespace(), "namespace protocol {\n");
  EXPECT_EQ(ctx.close_namespace(), "} // namespace protocol\n");
}

TEST(Test_029_codegen_outputcontext, HeaderGuard) {
  OutputContext ctx("myapp::smtp");
  std::string guard = ctx.header_guard("data_types.hpp");
  EXPECT_EQ(guard, "GENERATED_MYAPP_SMTP_DATA_TYPES_HPP");
}

TEST(Test_029_codegen_outputcontext, HeaderGuardNested) {
  OutputContext ctx("protocols::network::http");
  std::string guard = ctx.header_guard("parser.hpp");
  EXPECT_EQ(guard, "GENERATED_PROTOCOLS_NETWORK_HTTP_PARSER_HPP");
}

TEST(Test_029_codegen_outputcontext, HeaderGuardRemovesConsecutiveUnderscores) {
  OutputContext ctx("my__app");
  std::string guard = ctx.header_guard("test.hpp");
  // Should not have consecutive underscores
  EXPECT_EQ(guard.find("__"), std::string::npos);
}

TEST(Test_029_codegen_outputcontext, TargetNamespace) {
  OutputContext ctx("myapp::smtp");
  EXPECT_EQ(ctx.target_namespace(), "myapp::smtp");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralSimple) {
  std::string result = OutputContext::escape_string_literal("hello");
  EXPECT_EQ(result, "\"hello\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralNewline) {
  std::string result = OutputContext::escape_string_literal("hello\r\nworld");
  EXPECT_EQ(result, "\"hello\\r\\nworld\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralTab) {
  std::string result = OutputContext::escape_string_literal("col1\tcol2");
  EXPECT_EQ(result, "\"col1\\tcol2\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralBackslash) {
  std::string result = OutputContext::escape_string_literal("path\\to\\file");
  EXPECT_EQ(result, "\"path\\\\to\\\\file\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralQuote) {
  std::string result = OutputContext::escape_string_literal("say \"hello\"");
  EXPECT_EQ(result, "\"say \\\"hello\\\"\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralEmpty) {
  std::string result = OutputContext::escape_string_literal("");
  EXPECT_EQ(result, "\"\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralNullByte) {
  std::string input;
  input.push_back('\0');
  std::string result = OutputContext::escape_string_literal(input);
  // Null byte should be escaped as hex
  EXPECT_TRUE(result.find("\\x00") != std::string::npos);
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralCRLF) {
  std::string result = OutputContext::escape_string_literal("\r\n");
  EXPECT_EQ(result, "\"\\r\\n\"");
}

TEST(Test_029_codegen_outputcontext, EscapeStringLiteralMixedContent) {
  std::string result = OutputContext::escape_string_literal("GET /path HTTP/1.1\r\n");
  EXPECT_EQ(result, "\"GET /path HTTP/1.1\\r\\n\"");
}

TEST(Test_029_codegen_outputcontext, HeaderGuardWithDots) {
  OutputContext ctx("my.app.smtp");
  std::string guard = ctx.header_guard("parser.hpp");
  // Dots should be converted to underscores
  EXPECT_TRUE(guard.find(".") == std::string::npos);
  EXPECT_TRUE(guard.find("_") != std::string::npos);
}

TEST(Test_029_codegen_outputcontext, HeaderGuardPreservesCase) {
  OutputContext ctx("MyApp::SMTP");
  std::string guard = ctx.header_guard("Parser.hpp");
  // Should be all uppercase
  for (char c : guard) {
    if (std::isalpha(c)) {
      EXPECT_TRUE(std::isupper(c)) << "Character '" << c << "' should be uppercase";
    }
  }
}

TEST(Test_029_codegen_outputcontext, NestedNamespaceOpen) {
  OutputContext ctx("a::b::c::d");
  EXPECT_EQ(ctx.open_namespace(), "namespace a::b::c::d {\n");
}

TEST(Test_029_codegen_outputcontext, EmptyNamespace) {
  OutputContext ctx("");
  // Should still produce valid output
  EXPECT_FALSE(ctx.open_namespace().empty());
  EXPECT_FALSE(ctx.close_namespace().empty());
}
