//
// Created by zhouyang on 2016/11/2.
//

#ifndef STL_STR_H
#define STL_STR_H

#include <MacTypes.h>
#include <iostream>

namespace zy {
//a simple string implement for string refer to backend in action
class string {
 public:
  string(const char *str = NULL);

  string(const string &other);

  ~string();

  string &operator=(const string &other);

  string &operator+(const string &other);

  bool operator==(const string &other) const ;

  bool operator!=(const string &other) const ;

  int size() const;

  friend std::ostream &operator<<(std::ostream &os,const string &str);

  void print() const;

 private:

  char *data_;
};

 //std::ostream &operator <<(std::ostream &os,const string &str);

}

#endif //STL_STR_H
