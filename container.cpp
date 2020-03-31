#include<deque>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<list>

using namespace std;

void dequetest(){
	deque<int> deq;
	for(int i=0;i<1000;i++){
		deq.push_back(rand());
		deq.push_front(rand());
	}
	
	for(auto& num:deq){
		cout<<num<<" ";
	}
	cout<<endl;

	int num=deq.front();
	cout<<"first emelemt:"<<num<<endl;
	deq.pop_front();
	num=deq.front();
	cout<<"first emelemt:"<<num<<endl;

	num=deq.back();
	cout<<"last emelemt:"<<num<<endl;
	deq.pop_back();
	num=deq.back();
	cout<<"last emelemt:"<<num<<endl;

	deq.resize(10);
	for(auto& num:deq){
		cout<<num<<" ";
	}
	cout<<endl;
	

	deq.insert(deq.begin()+4,8,6);
	for(auto& num:deq){
		cout<<num<<" ";
	}
	cout<<endl;

	deq.erase(deq.begin()+4,deq.begin()+12);
	for(auto& num:deq){
		cout<<num<<" ";
	}
	cout<<endl;
}

void listtest(){
	list<int>  lst;
	for(int i=0;i<50;++i){
		lst.push_back(rand());
	}
	for(auto it=lst.begin();it!=lst.end();++it){
		cout<<*it<<endl;
	}
	cout<<"///////////////////////////////////////////"<<endl;
	lst.insert(lst.begin(),24);
	for(auto it=lst.begin();it!=lst.end();++it){
		cout<<*it<<endl;
	}
	cout<<"///////////////////////////////////////////"<<endl;
	lst.erase(lst.begin(),lst.end());
	for(auto it=lst.begin();it!=lst.end();++it){
		cout<<*it<<endl;
	}
	cout<<"///////////////////////////////////////////"<<endl;
}

int main(){
	srand((int)time(0));
	//dequetest();
	listtest();
	return 0;
}
