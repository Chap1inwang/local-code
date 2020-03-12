#include<exception>
#include<iostream>
using namespace std;

double divide(int a,int b){
	if(b==0){
		throw bad_exception();
	}
	else{
		return (double)a/b;
	}
}

int main(){
	int a,b;
	cin>>a>>b;
	try{
		cout<< divide(a,b)<<endl;
	}
	catch(bad_exception& e){
		cout<<e.what()<<endl;
	}
	return 0;
}
