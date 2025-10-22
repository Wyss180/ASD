#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"


TEST(Brackets, empty) { EXPECT_TRUE(check_breckets("")); }
TEST(Brackets, with_spaces) { EXPECT_TRUE(check_breckets(" ( ) [ ] { } ")); }
TEST(Brackets, tabs_and_newlines) { EXPECT_TRUE(check_breckets("\n[\n]")); }
TEST(Brackets, letters_still_error) { EXPECT_FALSE(check_breckets("(a)")); }
TEST(Brackets, numbers_still_error) { EXPECT_FALSE(check_breckets("(1)")); }