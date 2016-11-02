#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include <cstddef>
#include <cassert>
#include <iostream>

namespace zy {

template<typename T>
class vector {
  const static int WALK_LENGTH = 64;
 public:
  vector() : array_(NULL), size_(0), capacity_(0) {

  }

  vector(const T &data, size_t size) : array_(NULL), size_(0), capacity_(0) {
    for (size_t i = 0; i < size; ++i)
      push_back(data);
  }

  vector(const vector<T>& other) : array_(NULL), size_(0), capacity_(0) {
    *this = other;
  }

  vector<T> &operator=(const vector<T> &other) {
    if (this == &other)
      return *this;
    clear();
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = allocator(capacity_);
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = other.array_[i];
    }
    return *this;
  }

  ~vector() {
    clear();
  }

  T &operator[](size_t pos) {
    assert(pos < size_);
    return array_[pos];
  }

  const T &operator[](size_t pos) const {
    assert(pos < size_);
    return array_[pos];
  }

  size_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    deallocator(array_);
    size_ = 0;
    capacity_ = 0;
  }

  void push_back(const T &data) {
    insert_after(size_ - 1, data);
  }

  void push_front(const T &data) {
    insert_before(0, data);
  }

  void erase(size_t pos) {
    if (pos < size_) {
      //decrease size_ before move tail of the array
      --size_;
      for (size_t i = pos; i < size_; ++i) {
        array_[i] = array_[i + 1];
      }
    }
  }

  void print() const {
    for (size_t i = 0; i < size_; ++i)
      std::cout << array_[i] << " ";
    std::cout << std::endl;
    std::cout << "size: " << size_ << " capacity: " << capacity_ << std::endl;
  }

 private:

  void insert_after(int pos, const T &data) {
    insert_before(pos + 1, data);
  }

  //key function of class vector
  void insert_before(int pos, const T &data) {
    if (size_ == capacity_) {
      T *oldArray = array_;
      capacity_ += WALK_LENGTH;
      array_ = allocator(capacity_);
      for (size_t i = 0; i < size_; i++) {
        array_[i] = oldArray[i];
      }
      deallocator(oldArray);
    }
    //整体后移一位
    for (size_t i = size_++; i > pos; --i)
      array_[i] = array_[i - 1];
    array_[pos] = data;
  }

  //definition for allocator
  T *allocator(size_t size) {
    return new T[size];
  }

  //definition for deallocator
  void deallocator(T *&arr) {
    if (arr) {
      delete arr;
      arr = NULL;
    }
  }

  T *array_;
  size_t size_;
  size_t capacity_;
};

}
#endif