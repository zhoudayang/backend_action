#include <iostream>
#include <fstream>

#include "message.pb.h"

using namespace std;


int main(){
  zy::Content message;
  fstream input("./log",ios::in|ios::binary);
  if(!message.ParseFromIstream(&input)){
    cerr<<"failed to parse protobuf message!"<<endl;
    return -1;
  }
  cout<<message.id()<<endl;
  cout<<message.str()<<endl;
}