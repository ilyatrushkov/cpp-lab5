// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#include <gtest/gtest.h>
#include <stdexcept>

#include "MyStack.hpp"
#include "MyNonCopiedStack.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class CopiedClass {
 private:
  int _val;
 public:
  CopiedClass() = default;
  CopiedClass(CopiedClass &&a) = default;
  CopiedClass(const CopiedClass &a) = default;
};

class NonCopiedClass {
 private:
  int _val1;
  int _val2;
 public:
  NonCopiedClass() = default;
  NonCopiedClass(int a, int b)
      : _val1(a)
      , _val2(b) {};
  NonCopiedClass(NonCopiedClass &&a) noexcept = default;
  auto operator=(NonCopiedClass &&a) noexcept -> NonCopiedClass& = default;
  NonCopiedClass(const NonCopiedClass &a) = delete;
  auto operator=(const NonCopiedClass &a) -> NonCopiedClass& = delete;
  int get_val1() const {
    return _val1;
  }
  int get_val2() const {
    return _val2;
  }
};

TEST(NonCopiedClass, TestConstructible) {
  EXPECT_TRUE(std::is_move_constructible<NonCopiedClass>::value);
  EXPECT_FALSE(std::is_copy_constructible<NonCopiedClass>::value);
}

TEST(CopiedClass, TestConstructible) {
  EXPECT_TRUE(std::is_move_constructible<CopiedClass>::value);
  EXPECT_TRUE(std::is_copy_constructible<CopiedClass>::value);
}

TEST(MyStack, TestMovableAndCopied) {
  EXPECT_TRUE(std::is_move_constructible<MyStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<MyStack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<MyStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<MyStack<int>>::value);
}

TEST(MyNonCopiedStack, TestMovableAndCopied) {
  EXPECT_TRUE(std::is_move_constructible<MyNonCopiedStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<MyNonCopiedStack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<MyNonCopiedStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<MyNonCopiedStack<int>>::value);
}

TEST(MyStack, TestFunctionality) {
  MyStack<int> stack;
  int value1 = 10;
  int value2 = 20;
  stack.push(value1);
  EXPECT_EQ(stack.head(), value1);
  stack.push(value2);
  EXPECT_EQ(stack.head(), value2);
  stack.pop();
  EXPECT_EQ(stack.head(), value1);
  stack.pop();
  EXPECT_THROW(stack.pop(), std::exception);
}

TEST(MyNonCopiedStack, TestFunctionality) {
  MyNonCopiedStack<NonCopiedClass> stack;
  int a = 10;
  int b = 20;
  stack.push_emplace(a, b);
  stack.push(NonCopiedClass(25, 40));
  EXPECT_EQ(stack.head().get_val1(), 25);
  EXPECT_EQ(stack.head().get_val2(), 40);
  stack.pop();
  EXPECT_EQ(stack.head().get_val1(), a);
  EXPECT_EQ(stack.head().get_val2(), b);
  stack.pop();
  EXPECT_THROW(stack.pop(), std::exception);
}
