#include "vector.h"
using zy::vector;

int main(){
  vector<int> arr1(1,10);
  arr1.print();
  for(int i =0;i<10;i++)
    arr1.push_back(i);
  arr1.print();
  arr1.push_front(199);
  arr1.print();
  assert(!arr1.empty());
  arr1.clear();
  assert(arr1.empty());
  arr1.push_back(1);
  arr1.print();
  arr1.erase(0);
  arr1.print();
  arr1.clear();
  for(int i=0;i<10000;++i)
    arr1.push_back(rand());
  arr1.print();
  assert(arr1.size() == 10000);
  return 0;
}