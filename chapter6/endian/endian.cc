#include <iostream>
using namespace std;

int main(){
	union{
		int a;
		char ch[2];
	} temp;
	temp.a = 0x1234;
	if(temp.ch[0] == 0x34)
		cout<<"little endian"<<endl;
	else if(temp.ch[1] == 0x12)
		cout<<"big endian"<<endl;
	return 0;

}
