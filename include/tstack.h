// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T storage[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  int getSize() const { 
      return topIndex + 1; 
  }

  bool isEmpty() const { 
      return topIndex == -1; 
  }

  void push(const T& item) {
    if (topIndex < size - 1)
      storage[++topIndex] = item;
    else
      throw "Full stack";
  }

  T get() const {
    if (topIndex >= 0)
      return storage[topIndex];
    else
      throw "Empty stack";
  }

  void pop() {
    if (topIndex >= 0)
      topIndex--;
    else
      throw "Empty stack";
  }
};

#endif  // INCLUDE_TSTACK_H_
