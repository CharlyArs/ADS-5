// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int SIZE>
class TStack {
 private:
  T storage[SIZE];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == SIZE - 1;
  }

  void push(const T& item) {
    if (isFull()) {
      throw "Full stack";
    }
    storage[++topIndex] = item;
  }

  T get() const {
    if (isEmpty()) {
      throw "Empty stack";
    }
    return storage[topIndex];
  }

  void pop() {
    if (isEmpty()) {
      throw "Empty stack";
    }
    topIndex--;
  }
};

#endif  // INCLUDE_TSTACK_H_
