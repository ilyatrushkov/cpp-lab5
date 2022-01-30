// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef INCLUDE_MYSTACK_HPP
#define INCLUDE_MYSTACK_HPP

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
  MyStack(MyStack &&stack) noexcept = default;
  auto operator=(MyStack &&stack) noexcept -> MyStack& = default;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  ~MyStack();
};

template <typename T>
void MyStack<T>::push(T &&value) {
  // Stack is empty
  if (!_top_item) {
    _top_item = new Item<T>;
    _top_item -> value = value;
    _top_item -> previous = nullptr;
  } else {  // Stack is empty
//    Item<T> *tmp{top_item};
    auto *tmp = new Item<T>;
    tmp -> value = _top_item -> value;
    tmp -> previous = _top_item -> previous;
    _top_item -> value = value;
    _top_item -> previous = tmp;
  }
}

template <typename T>
void MyStack<T>::push(const T &value) {
  // Stack is empty
  if (!_top_item) {
    _top_item = new Item<T>;
    _top_item -> value = value;
    _top_item -> previous = nullptr;
  } else {     // Stack is not empty
    //    Item<T> *tmp{top_item};
    auto *tmp = new Item<T>;
    tmp -> value = _top_item -> value;
    tmp -> previous = _top_item -> previous;
    _top_item -> value = value;
    _top_item -> previous = tmp;
  }
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

#endif  // INCLUDE_MYSTACK_HPP
