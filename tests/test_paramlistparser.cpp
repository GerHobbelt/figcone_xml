#include "assert_exception.h"
#include <figcone_xml/parser.h>
#include <gtest/gtest.h>
#include <sstream>

namespace test_paramlistparser {

auto parseParam(const std::string& str)
{
    auto input = std::stringstream{str};
    auto parser = figcone::xml::Parser{};
    return parser.parse(input);
}

TEST(TestParamListParser, Basic)
{
    auto result = parseParam(R"(<root testIntList = "[1, 2, 3]" />)");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, BasicWithoutMacro)
{
    auto result = parseParam(R"(<root testIntList = "[1, 2, 3]"/>)");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, BasicAltWhitespace)
{
    auto result = parseParam(R"(<root testIntList = "[1,2,3]" />)");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, WithString)
{
    auto result = parseParam(R"(<root testStrList = "['Hello', world, ' ']" />)");
    auto& tree = result.asItem();
    EXPECT_EQ(tree.param("testStrList").valueList(), (std::vector<std::string>{"Hello", "world", " "}));
}

TEST(TestParamListParser, WithStringAltWhitespace)
{
    auto result = parseParam(R"(<root testStrList = " [ 'Hello'
,  world,
 ''
 ]" />)");
    auto& tree = result.asItem();
    EXPECT_EQ(tree.param("testStrList").valueList(), (std::vector<std::string>{"Hello", "world", ""}));
}

TEST(TestParamListParser, Empty)
{
    auto result = parseParam(R"(<root testIntList = "[]" />)");
    auto& tree = result.asItem();
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{}));
}

TEST(TestParamListParser, EmptyAltWhitespace)
{
    auto result = parseParam(R"(<root testIntList = "[
 ]" />)");
    auto& tree = result.asItem();
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{}));
}

TEST(TestParamListParser, EmptyLastElementError)
{
    assert_exception<figcone::ConfigError>(
            [&]
            {
                parseParam(R"(<root testIntList ="[1,2,]" />)");
            },
            [](const figcone::ConfigError& e)
            {
                ASSERT_EQ(std::string{e.what()}, "Parameter list 'testIntList' element is missing");
            });
}

TEST(TestParamListParser, EmptyFirstElementError)
{
    assert_exception<figcone::ConfigError>(
            [&]
            {
                parseParam(R"(<root testIntList = "[,1,2]" />)");
            },
            [](const figcone::ConfigError& e)
            {
                ASSERT_EQ(std::string{e.what()}, "Parameter list 'testIntList' element is missing");
            });
}

TEST(TestParamListParser, EmptyElementError)
{
    assert_exception<figcone::ConfigError>(
            [&]
            {
                parseParam(R"(<root testIntList = "[1, ,3 ]" />)");
            },
            [](const figcone::ConfigError& e)
            {
                ASSERT_EQ(std::string{e.what()}, "Parameter list 'testIntList' element is missing");
            });
}

TEST(TestParamListParser, EmptyLastElementAltWhitespaceError)
{
    assert_exception<figcone::ConfigError>(
            [&]
            {
                parseParam(R"(<root testIntList ="[1,2,
]" />)");
            },
            [](const figcone::ConfigError& e)
            {
                ASSERT_EQ(std::string{e.what()}, "Parameter list 'testIntList' element is missing");
            });
}

TEST(TestParamListParser, EmptyWithSeparatorError)
{
    assert_exception<figcone::ConfigError>(
            [&]
            {
                parseParam(R"(<root testIntList = "[,]" />)");
            },
            [](const figcone::ConfigError& e)
            {
                ASSERT_EQ(std::string{e.what()}, "Parameter list 'testIntList' element is missing");
            });
}

} //namespace test_paramlistparser
