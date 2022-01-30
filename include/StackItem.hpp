// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef TEMPLATE_STACKITEM_HPP
#define TEMPLATE_STACKITEM_HPP

template <typename T>
struct  Item {
  T value;
  Item<T> *previous;
};

#endif  // TEMPLATE_STACKITEM_HPP
