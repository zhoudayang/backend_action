//
// Created by zhouyang on 2016/11/2.
//

#include "str.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;
using namespace zy;

int main(int argc,char **argv){

  string str1("hello world");
  string str2(str1);
  cout<<str1<<endl<<str2<<endl;

  str1 + ", nihao!";
  cout<<str1<<endl;

  cout<<str1.size()<<" "<<str2.size()<<endl;

  assert(str1!= str2);

  return 0;
}