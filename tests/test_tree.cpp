#include <gtest/gtest.h>
#include <sstream>
#include "Tree.h"


TEST(TreeLCR, LCROutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream buffer;
    tree.lcr(buffer);
    std::string output = buffer.str();

    EXPECT_TRUE(output.find("(3:three)") != std::string::npos);
    EXPECT_TRUE(output.find("(5:five)") != std::string::npos);
    EXPECT_TRUE(output.find("(7:seven)") != std::string::npos);
}

TEST(TreeLCR, LCRHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    tree.lcr(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("LCR:") != std::string::npos);
}

TEST(TreeLCR, LCRSingleElement) {
    Tree<int, std::string> tree;
    tree.insert(42, "answer");

    std::stringstream buffer;
    tree.lcr(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("(42:answer)") != std::string::npos);
}

TEST(TreeLCR, LCREmptyTree) {
    Tree<int, std::string> tree;
    std::stringstream buffer;
    tree.lcr(buffer);
    EXPECT_TRUE(buffer.str().empty() || buffer.str().find("LCR:") != std::string::npos);
}


TEST(TreeLRC, LRCOutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream buffer;
    tree.lrc(buffer);
    std::string output = buffer.str();

    EXPECT_TRUE(output.find("(3:three)") != std::string::npos);
    EXPECT_TRUE(output.find("(5:five)") != std::string::npos);
    EXPECT_TRUE(output.find("(7:seven)") != std::string::npos);
}

TEST(TreeLRC, LRCHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    tree.lrc(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("LRC:") != std::string::npos);
}

TEST(TreeLRC, LRCRootComesLast) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    std::stringstream buffer;
    tree.lrc(buffer);
    std::string output = buffer.str();

    size_t pos3 = output.find("(3:three)");
    size_t pos5 = output.find("(5:five)");
    EXPECT_TRUE(pos3 != std::string::npos && pos5 != std::string::npos);
    EXPECT_LT(pos3, pos5);
}

TEST(TreeLRC, LRCEmptyTree) {
    Tree<int, std::string> tree;
    std::stringstream buffer;
    tree.lrc(buffer);
    EXPECT_TRUE(buffer.str().empty() || buffer.str().find("LRC:") != std::string::npos);
}


TEST(TreeCLR, CLROutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream buffer;
    tree.clr(buffer);
    std::string output = buffer.str();

    EXPECT_TRUE(output.find("(3:three)") != std::string::npos);
    EXPECT_TRUE(output.find("(5:five)") != std::string::npos);
    EXPECT_TRUE(output.find("(7:seven)") != std::string::npos);
}

TEST(TreeCLR, CLRHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    tree.clr(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("CLR:") != std::string::npos);
}

TEST(TreeCLR, CLRRootComesFirst) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    std::stringstream buffer;
    tree.clr(buffer);
    std::string output = buffer.str();

    size_t pos5 = output.find("(5:five)");
    size_t pos3 = output.find("(3:three)");
    EXPECT_TRUE(pos5 != std::string::npos && pos3 != std::string::npos);
    EXPECT_LT(pos5, pos3);
}

TEST(TreeCLR, CLREmptyTree) {
    Tree<int, std::string> tree;
    std::stringstream buffer;
    tree.clr(buffer);
    EXPECT_TRUE(buffer.str().empty() || buffer.str().find("CLR:") != std::string::npos);
}


TEST(TreeWidth, WidthHasLevelStructure) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();

    EXPECT_TRUE(output.find("Level 0") != std::string::npos);
    EXPECT_TRUE(output.find("Level 1") != std::string::npos);
}

TEST(TreeWidth, WidthOutputsAllElements) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();

    EXPECT_TRUE(output.find("(5:five)") != std::string::npos);
    EXPECT_TRUE(output.find("(3:three)") != std::string::npos);
    EXPECT_TRUE(output.find("(7:seven)") != std::string::npos);
}

TEST(TreeWidth, WidthHasCorrectLabel) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("WIDTH:") != std::string::npos);
}

TEST(TreeWidth, WidthRootOnLevel0) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Level 0: (5:five)") != std::string::npos);
}

TEST(TreeWidth, WidthSingleElement) {
    Tree<int, std::string> tree;
    tree.insert(42, "answer");

    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("(42:answer)") != std::string::npos);
}

TEST(TreeWidth, WidthEmptyTree) {
    Tree<int, std::string> tree;
    std::stringstream buffer;
    tree.width(buffer);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("WIDTH: Tree is empty") != std::string::npos);
}


TEST(TreeFind, FindExistingKeyReturnsCorrectValue) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    const std::string* val = tree.find(3);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "three");
}

TEST(TreeFind, FindRootReturnsCorrectValue) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    const std::string* val = tree.find(5);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "five");
}

TEST(TreeFind, FindMissingKeyReturnsNullptr) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");

    const std::string* val = tree.find(99);
    EXPECT_EQ(val, nullptr);
}

TEST(TreeFind, FindInEmptyTreeReturnsNullptr) {
    Tree<int, std::string> tree;
    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TreeFind, FindLeftmostElement) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(2, "two");

    const std::string* val = tree.find(2);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "two");
}


TEST(TreeComplex, AllMethodsTogether) {
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::stringstream ss;
    EXPECT_NO_THROW(tree.lcr(ss));
    EXPECT_NO_THROW(tree.lrc(ss));
    EXPECT_NO_THROW(tree.clr(ss));
    EXPECT_NO_THROW(tree.width(ss));
}

TEST(TreeComplex, AllMethodsOnEmptyTree) {
    Tree<int, std::string> tree;
    std::stringstream ss;
    EXPECT_NO_THROW(tree.lcr(ss));
    EXPECT_NO_THROW(tree.lrc(ss));
    EXPECT_NO_THROW(tree.clr(ss));
    EXPECT_NO_THROW(tree.width(ss));
}