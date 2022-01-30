// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef INCLUDE_STACKITEM_HPP
#define INCLUDE_STACKITEM_HPP

template <typename T>
struct  Item {
  T value;
  Item<T> *previous;
};

#endif  // INCLUDE_STACKITEM_HPP
