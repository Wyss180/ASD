#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestEasyExampleLib, can_create_with_init_construct) {
	// Arrange
	int x = 10;
	int y = 2;

	// Act & Assert
	ASSERT_NO_THROW(Stack<int> s(10));
}