#include <gtest/gtest.h>
#include "..\lib_monom\monom.h"

TEST(MonomTest, DefaultConstructor) {
    Monom m;
    EXPECT_DOUBLE_EQ(m.getCoeff(), 0.0);
    EXPECT_EQ(m.getDegX(), 0);
    EXPECT_EQ(m.getDegY(), 0);
    EXPECT_EQ(m.getDegZ(), 0);
}

TEST(MonomTest, ParameterConstructor) {
    Monom m(3.5, 2, 1, 0);
    EXPECT_DOUBLE_EQ(m.getCoeff(), 3.5);
    EXPECT_EQ(m.getDegX(), 2);
    EXPECT_EQ(m.getDegY(), 1);
    EXPECT_EQ(m.getDegZ(), 0);
}

TEST(MonomTest, CopyConstructor) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(m1);
    EXPECT_DOUBLE_EQ(m2.getCoeff(), 2.0);
    EXPECT_EQ(m2.getDegX(), 1);
    EXPECT_EQ(m2.getDegY(), 2);
    EXPECT_EQ(m2.getDegZ(), 3);
}

TEST(MonomTest, EqualityOperator) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(2.0, 1, 2, 3);
    Monom m3(3.0, 1, 2, 3);
    Monom m4(2.0, 0, 2, 3);

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_FALSE(m1 == m4);
}

TEST(MonomTest, InequalityOperator) {
    Monom m1(2.0, 1, 2, 3);
    Monom m2(2.0, 1, 2, 3);
    Monom m3(3.0, 1, 2, 3);

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(MonomTest, GreaterOperator) {
    Monom m1(1.0, 2, 0, 0);
    Monom m2(1.0, 1, 0, 0);
    Monom m3(1.0, 2, 1, 0);
    Monom m4(1.0, 2, 0, 1);

    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m3 > m1);
    EXPECT_TRUE(m3 > m4);
}

TEST(MonomTest, Addition) {
    Monom m1(2.0, 1, 0, 0);
    Monom m2(3.0, 1, 0, 0);
    Monom result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 5.0);
    EXPECT_EQ(result.getDegX(), 1);
}

TEST(MonomTest, AdditionDifferentDegreesThrows) {
    Monom m1(2.0, 1, 0, 0);
    Monom m2(3.0, 2, 0, 0);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(MonomTest, Subtraction) {
    Monom m1(5.0, 1, 0, 0);
    Monom m2(3.0, 1, 0, 0);
    Monom result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 2.0);
}

TEST(MonomTest, Multiplication) {
    Monom m1(2.0, 1, 0, 0);
    Monom m2(3.0, 0, 2, 0);
    Monom result = m1 * m2;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 6.0);
    EXPECT_EQ(result.getDegX(), 1);
    EXPECT_EQ(result.getDegY(), 2);
}

TEST(MonomTest, Division) {
    Monom m1(6.0, 2, 1, 0);
    Monom m2(2.0, 1, 1, 0);
    Monom result = m1 / m2;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 3.0);
    EXPECT_EQ(result.getDegX(), 1);
    EXPECT_EQ(result.getDegY(), 0);
}

TEST(MonomTest, DivisionByZeroThrows) {
    Monom m1(2.0, 1, 0, 0);
    Monom m2(0.0, 0, 0, 0);

    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(MonomTest, DivisionNegativeDegreeThrows) {
    Monom m1(2.0, 1, 0, 0);
    Monom m2(3.0, 2, 0, 0);

    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(MonomTest, MultiplyByNumber) {
    Monom m(2.0, 1, 0, 0);
    Monom result = m * 3.0;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 6.0);
    EXPECT_EQ(result.getDegX(), 1);
}

TEST(MonomTest, DivideByNumber) {
    Monom m(6.0, 1, 0, 0);
    Monom result = m / 2.0;

    EXPECT_DOUBLE_EQ(result.getCoeff(), 3.0);
}

TEST(MonomTest, DivideByZeroNumberThrows) {
    Monom m(2.0, 1, 0, 0);
    EXPECT_THROW(m / 0.0, std::invalid_argument);
}

TEST(MonomTest, UnaryMinus) {
    Monom m(2.0, 1, 0, 0);
    Monom result = -m;

    EXPECT_DOUBLE_EQ(result.getCoeff(), -2.0);
    EXPECT_EQ(result.getDegX(), 1);
}

TEST(MonomTest, Value) {
    Monom m(2.0, 2, 1, 0);
    double val = m.value(3.0, 4.0, 5.0);

    EXPECT_DOUBLE_EQ(val, 72.0);
}

TEST(MonomTest, OutputOperator) {
    Monom m(3.5, 2, 1, 0);
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "3.5x^2y");

    Monom m2(1.0, 2, 0, 0);
    std::stringstream ss2;
    ss2 << m2;
    EXPECT_EQ(ss2.str(), "x^2");

    Monom m3(0.0, 1, 1, 1);
    std::stringstream ss3;
    ss3 << m3;
    EXPECT_EQ(ss3.str(), "0");
}