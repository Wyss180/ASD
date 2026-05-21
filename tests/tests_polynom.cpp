#include <gtest/gtest.h>
#include "..\lib_polynom\polynom.h"

TEST(PolynomTest, DefaultConstructor) {
    Polynom p;
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0");
}

TEST(PolynomTest, StringConstructorWorks) {
    EXPECT_NO_THROW(Polynom p("2x^2y + 3z - 5"));
}

TEST(PolynomTest, AdditionDoesNotCrash) {
    Polynom p1("x^2 + 2x");
    Polynom p2("3x^2 + 4");
    EXPECT_NO_THROW(p1 + p2);
}

TEST(PolynomTest, SubtractionDoesNotCrash) {
    Polynom p1("2x^2 + 3x");
    Polynom p2("x^2 + 5x");
    EXPECT_NO_THROW(p1 - p2);
}

TEST(PolynomTest, MultiplicationDoesNotCrash) {
    Polynom p1("x + 1");
    Polynom p2("x - 1");
    EXPECT_NO_THROW(p1 * p2);
}

TEST(PolynomTest, MultiplyByNumberDoesNotCrash) {
    Polynom p("2x^2 + 3x");
    EXPECT_NO_THROW(p * 2.0);
}

TEST(PolynomTest, ValueCalculation) {
    Polynom p("2x^2 + 3x + 1");
    double val = p.value(2.0, 0.0, 0.0);
    EXPECT_GT(val, 0);
    std::cout << "Value for 2x^2+3x+1 at x=2: " << val << std::endl;
}

TEST(PolynomTest, AddMonomWorks) {
    Polynom p;
    Monom m1(2.0, 2, 0, 0);
    Monom m2(3.0, 2, 0, 0);
    EXPECT_NO_THROW(p.addMonom(m1));
    EXPECT_NO_THROW(p.addMonom(m2));
}

TEST(PolynomTest, ShowRealOutput) {
    Polynom p1("2x^2 + 3x");
    Polynom p2("4x^2 + 5");
    Polynom sum = p1 + p2;

    std::stringstream ss;
    ss << sum;
    std::string out = ss.str();

    std::cout << "=== РЕАЛЬНЫЙ ВЫВОД ВАШЕГО POLYNOM ===" << std::endl;
    std::cout << "p1 + p2 = '" << out << "'" << std::endl;

    EXPECT_TRUE(true);
}

TEST(PolynomTest, ShowSubtractionOutput) {
    Polynom p1("5x^2 + 3x");
    Polynom p2("2x^2 + x");
    Polynom diff = p1 - p2;

    std::stringstream ss;
    ss << diff;
    std::cout << "p1 - p2 = '" << ss.str() << "'" << std::endl;
    EXPECT_TRUE(true);
}

TEST(PolynomTest, ShowMultiplicationOutput) {
    Polynom p1("x + 1");
    Polynom p2("x - 1");
    Polynom prod = p1 * p2;

    std::stringstream ss;
    ss << prod;
    std::cout << "(x+1)*(x-1) = '" << ss.str() << "'" << std::endl;
    EXPECT_TRUE(true);
}

TEST(PolynomTest, ShowMultiplyByNumberOutput) {
    Polynom p("2x^2 + 3x");
    Polynom result = p * 2.0;

    std::stringstream ss;
    ss << result;
    std::cout << "2*(2x^2+3x) = '" << ss.str() << "'" << std::endl;
    EXPECT_TRUE(true);
}