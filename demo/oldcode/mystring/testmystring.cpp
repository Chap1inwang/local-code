#include<iostream>
#include"mystring.h"

using namespace std;

int main(){
	mystring ob1;
	mystring ob2("this is a string");
	mystring ob3="tail of string";
	ob2+=ob3;
	ob1=ob2;
	cout<<ob1<<endl;
	cout<<ob2<<" "<<"fsd"<<endl;
	cout<<ob2.compare(ob3)<<endl;
	cout<<ob1.back()<<" "<<ob1.front()<<endl;
	return 0;
}
