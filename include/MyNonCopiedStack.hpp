// Copyright 2022 Trushkov ILya ilya.tr20002@gmail.com

#ifndef INCLUDE_MYNONCOPIEDSTACK_HPP_
#define INCLUDE_MYNONCOPIEDSTACK_HPP_

#include <utility>
#include "StackItem.hpp"

template <typename T>
class MyNonCopiedStack {
 private:
  Item<T> *_top_item = nullptr;
 public:
  MyNonCopiedStack() = default;
  MyNonCopiedStack(const MyNonCopiedStack &stack) = delete;
  auto operator=(const MyNonCopiedStack &stack) -> MyNonCopiedStack& = delete;
  MyNonCopiedStack(MyNonCopiedStack &&stack) noexcept = default;
  auto operator=(MyNonCopiedStack &&stack) noexcept ->
   MyNonCopiedStack& = default;
  template <typename ... Args> void push_emplace(Args&& ... value);
  void push(T&& value);
  const T& head() const;
  T pop();
  ~MyNonCopiedStack();
};

template <typename T>
template <typename ... Args>
void MyNonCopiedStack<T>::push_emplace(Args&& ... value) {
  auto *tmp = _top_item;
  _top_item = new Item<T>{{std::forward<Args>(value) ... }, tmp};
}

template <typename T>
void MyNonCopiedStack<T>::push(T &&value) {
  auto *tmp = _top_item;
  _top_item = new Item<T>{std::forward<T>(value), tmp};
}

template <typename T>
const T& MyNonCopiedStack<T>::head() const {
  return _top_item -> value;
}

template <typename T>
T MyNonCopiedStack<T>::pop() {
  if (!_top_item) {
    throw std::exception();
  }
  auto value = std::move(_top_item -> value);
  _top_item = _top_item -> previous;
  return value;
}

template<typename T>
MyNonCopiedStack<T>::~MyNonCopiedStack() {
  while (_top_item) {
    auto *tmp = _top_item;
    _top_item = _top_item -> previous;
    delete tmp;
  }
}

#endif  // INCLUDE_MYNONCOPIEDSTACK_HPP_
