#include<iostream>
#include<vector>

using namespace std;

class smartptr{
private:
	int* value;
	int* count;
public:
	smartptr(){
		value=new int(0);
		count=new int(0);
	}
	smartptr(int val){
		value=new int(val);
		count=new int(1);
		myprintor(*this);
	}
	smartptr(const smartptr& sptr){
		value=sptr.value;
		++(*sptr.count);
		count=sptr.count;
		myprintor(*this);
	}
	~smartptr(){
		if(*count>0){
			cout<<"value:"<<*value<<" "<<"count:"<<*count-1<<endl;
			if(--(*count)==0){
				cout<<"析构函数调用new"<<endl;
				delete value;
				delete count;
				value=NULL;
				count=NULL;
			}
		}
	}
	smartptr& operator=(const smartptr& sptr){
		if(sptr.value==value){
			return *this;
		}
		if(*count>0){
			cout<<"value:"<<*value<<" "<<"count:"<<*count-1<<endl;
			if(--(*count)==0){
				cout<<"析构函数调用new"<<endl;
				delete value;
				delete count;
				value=NULL;
				count=NULL;
			}
		}
		value=sptr.value;
		count=sptr.count;
		++(*count);
		myprintor(*this);
		return *this;
	}
	
	int& operator*() const {
		return *value;
	}

	int* operator->() const {
		return &(operator*());
	}
	
	friend ostream& operator<<(ostream& ou,smartptr& sptr){
		ou<<"value:"<<*sptr.value<<" "<<"count:"<<*sptr.count<<endl;
		return ou;
	}
	friend void myprintor(const smartptr& sptr){
		cout<<"value:"<<*sptr.value<<" "<<"count:"<<*sptr.count<<endl;
	}
};
int main(){
	smartptr sp(3);
	cout<<*sp<<endl;
	vector<smartptr> sptr_vec(100,smartptr(4));
	vector<smartptr> ptr_vec(100,smartptr(5));
	for(int i=0;i<100;++i){
		sptr_vec[i]=ptr_vec[i];
	}
	return 0;
}
