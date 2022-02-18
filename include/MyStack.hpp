// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef INCLUDE_MYSTACK_HPP_
#define INCLUDE_MYSTACK_HPP_

#include <exception>

#include "StackItem.hpp"

template <typename T>
class MyStack {
 private:
  Item<T> *_top_item = nullptr;
 public:
  MyStack() = default;
  MyStack(const MyStack &stack) = delete;
  auto operator=(const MyStack &stack) -> MyStack& = delete;
  MyStack(MyStack &&stack) = default;
  auto operator=(MyStack &&stack) noexcept -> MyStack& = default;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  ~MyStack();
};

template <typename T>
void MyStack<T>::push(T &&value) {
  auto *tmp = new Item<T>{std::forward(value), _top_item};
  _top_item = tmp;
}

template <typename T>
void MyStack<T>::push(const T &value) {
  auto *tmp = new Item<T>{value, _top_item};
  _top_item = tmp;
}

template <typename T>
void MyStack<T>::pop() {
  if (_top_item) {
    _top_item = _top_item -> previous;
  } else {
    throw std::exception();
  }
}

template <typename T>
const T& MyStack<T>::head() const {
  return _top_item -> value;
}

template <typename T>
MyStack<T>::~MyStack() {
  while (_top_item) {
    auto *tmp = _top_item;
    _top_item = _top_item -> previous;
    delete tmp;
  }
}

#endif  // INCLUDE_MYSTACK_HPP_
