//
// Created by zhouyang on 2016/11/2.
//

#include "str.h"
#include <cstring>

namespace zy {
string::string(const char *str) {
  if (str == NULL) {
    data_ = new char[1];
    data_[0] = '\0';

  } else {
    size_t length = strlen(str);
    data_ = new char[length + 1];
    strcpy(data_, str);
  }
}

string::~string() {
  if (data_) {
    delete data_;
    data_ = NULL;
  }
}

string::string(const string &other) {
  if (!other.data_) {
    data_ = NULL;
  } else {
    data_ = new char[strlen(other.data_) + 1];
    strcpy(data_, other.data_);
  }
}

string &string::operator=(const string &other) {
  if (this != &other) {
    delete[] data_;
    if (!other.data_) {
      data_ = NULL;
    } else {
      data_ = new char[strlen(other.data_) + 1];
      strcpy(data_, other.data_);
    }
  }
  return *this;
}

string &string::operator+(const string &other) {
  if (!other.data_) {
    return *this;
  } else if (!data_) {
    *this = other;
  } else {
    char *new_str = new char[strlen(data_) + strlen(other.data_) + 1];
    strcpy(new_str, data_);
    strcat(new_str, other.data_);
    delete data_;
    data_ = new_str;
  }
  return *this;
}

bool string::operator==(const string &other) const {
  size_t length;
  if ((length = strlen(data_)) != strlen(other.data_))
    return false;
  return memcmp(data_, other.data_, length) == 0;
}

bool string::operator!=(const string &other) const {
  return !(*this == other);
}

int string::size() const {
  if (!data_)
    return 0;
  return strlen(data_);
}

//friend function should care about namespace, or else the friend function cannot access the private member of the class instance
std::ostream &operator<<(std::ostream &os, const zy::string &str) {
  os << str.data_;
  return os;
}

void string::print() const {
  std::cout << data_ << std::endl;
}

}