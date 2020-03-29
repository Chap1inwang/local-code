#include<functional>
#include<iostream>

using namespace std;

int sum(int i,int j){
	return i+j;
}

int main(){
	auto functor=bind(sum,std::placeholders::_1,12);
	cout<<functor(4);
	return 0;
}
