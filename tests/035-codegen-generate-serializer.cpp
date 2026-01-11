#include <networkprotocoldsl/codegen/generate_serializer.hpp>
#include <networkprotocoldsl/codegen/outputcontext.hpp>
#include <networkprotocoldsl/codegen/protocolinfo.hpp>
#include <networkprotocoldsl/lexer/tokenize.hpp>
#include <networkprotocoldsl/parser/parse.hpp>
#include <networkprotocoldsl/sema/analyze.hpp>

#include <fstream>
#include <gtest/gtest.h>

using namespace networkprotocoldsl;
using namespace networkprotocoldsl::codegen;

class Test_035_codegen_generate_serializer_GenerateSerializerTest : public ::testing::Test {
protected:
  std::shared_ptr<const sema::ast::Protocol> protocol_;
  std::unique_ptr<OutputContext> ctx_;
  std::unique_ptr<ProtocolInfo> info_;

  void SetUp() override {
    std::string test_file =
        std::string(TEST_DATA_DIR) + "/023-source-code-http-client-server.txt";
    std::ifstream file(test_file);
    ASSERT_TRUE(file.is_open());
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    auto maybe_tokens = lexer::tokenize(content);
    ASSERT_TRUE(maybe_tokens.has_value());

    auto result = parser::parse(maybe_tokens.value());
    ASSERT_TRUE(result.has_value());

    auto maybe_protocol = sema::analyze(result.value());
    ASSERT_TRUE(maybe_protocol.has_value());
    protocol_ = maybe_protocol.value();

    ctx_ = std::make_unique<OutputContext>("test::http");
    info_ = std::make_unique<ProtocolInfo>(protocol_);
  }
};

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, GeneratesHeader) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_FALSE(result.header.empty());
  EXPECT_TRUE(result.errors.empty());
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, GeneratesSource) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_FALSE(result.source.empty());
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasGuard) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("#ifndef") != std::string::npos);
  EXPECT_TRUE(result.header.find("#define") != std::string::npos);
  EXPECT_TRUE(result.header.find("#endif") != std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasNamespace) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("namespace test::http") != std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderIncludesDataTypes) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("#include \"data_types.hpp\"") !=
              std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceIncludesHeader) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.source.find("#include \"serializer.hpp\"") !=
              std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceHasNamespace) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.source.find("namespace test::http") != std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderIncludesStates) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("#include \"states.hpp\"") !=
              std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, ClosingBracesMatch) {
  auto result = generate_serializer(*ctx_, *info_);

  // Count opening and closing braces - they should match
  int open_braces = 0;
  int close_braces = 0;
  for (char c : result.header) {
    if (c == '{') open_braces++;
    if (c == '}') close_braces++;
  }
  EXPECT_EQ(open_braces, close_braces) << "Braces should be balanced in header";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, NoErrorsReported) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.errors.empty())
      << "Should not have errors, but got: "
      << (result.errors.empty() ? "" : result.errors[0]);
}

// Tests for future implementation - these will need updating when serializer is complete

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasIncludeString) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("#include <string>") != std::string::npos);
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasMessageSerializerClasses) {
  auto result = generate_serializer(*ctx_, *info_);

  // Should have serializer classes for write transitions
  // HTTP Request is a write transition (client writes it)
  EXPECT_TRUE(result.header.find("HTTPRequestSerializer") != std::string::npos)
      << "Should have HTTPRequestSerializer class";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasSetDataMethod) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("void set_data(") != std::string::npos)
      << "Serializers should have set_data method";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasResetMethod) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("void reset()") != std::string::npos)
      << "Serializers should have reset method";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasNextChunkMethod) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("next_chunk()") != std::string::npos)
      << "Serializers should have next_chunk method";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasAdvanceMethod) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("void advance()") != std::string::npos)
      << "Serializers should have advance method";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasIsCompleteMethod) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("is_complete()") != std::string::npos)
      << "Serializers should have is_complete method";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceHasStateMachine) {
  auto result = generate_serializer(*ctx_, *info_);

  // Should have switch statements for stage handling
  EXPECT_TRUE(result.source.find("switch (stage_)") != std::string::npos)
      << "Source should have stage-based state machine";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceHandlesStaticOctets) {
  auto result = generate_serializer(*ctx_, *info_);

  // HTTP protocol has static octets like "HTTP/"
  EXPECT_TRUE(result.source.find("HTTP/") != std::string::npos ||
              result.source.find("static octets") != std::string::npos)
      << "Source should handle static octets";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceHandlesLoops) {
  auto result = generate_serializer(*ctx_, *info_);

  // HTTP protocol has loops for headers
  EXPECT_TRUE(result.source.find("loop_index_") != std::string::npos)
      << "Source should handle loops with loop_index_";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceBalancedBraces) {
  auto result = generate_serializer(*ctx_, *info_);

  int open_braces = 0;
  int close_braces = 0;
  for (char c : result.source) {
    if (c == '{') open_braces++;
    if (c == '}') close_braces++;
  }
  EXPECT_EQ(open_braces, close_braces) << "Braces should be balanced in source";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderHasAutoGeneratedComment) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("auto-generated") != std::string::npos)
      << "Header should have auto-generated comment";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, SourceHasAutoGeneratedComment) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.source.find("auto-generated") != std::string::npos)
      << "Source should have auto-generated comment";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, HeaderIncludesUtility) {
  auto result = generate_serializer(*ctx_, *info_);

  EXPECT_TRUE(result.header.find("#include <utility>") != std::string::npos)
      << "Header should include <utility> for std::move";
}

TEST_F(Test_035_codegen_generate_serializer_GenerateSerializerTest, AdvanceMarksCompleteAtEnd) {
  auto result = generate_serializer(*ctx_, *info_);

  // The advance() method should mark complete when reaching final stage
  EXPECT_TRUE(result.source.find("complete_ = true") != std::string::npos)
      << "advance() should mark complete when serialization finishes";
}
