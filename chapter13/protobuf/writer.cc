#include <iostream>
#include <fstream>

#include "message.pb.h"

using namespace std;

int main(){
  zy::Content msg1;
  msg1.set_id(22);
  msg1.set_str("zhouyang");
  fstream output("./log",ios::out|ios::trunc|ios::binary);
  if(!msg1.SerializeToOstream(&output)){
    cerr<<"Failed to writer message!"<<endl;
    return -1;
  }
  return 0;
}