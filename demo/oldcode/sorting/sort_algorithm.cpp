#include<iostream>
#include<vector>

using namespace std;

//1冒泡排序
void bubble_sort(vector<int> nums){
	for(int i=0;i<nums.size();++i){
		for(int j=i+1;j<nums.size();++j){
			if(nums[i]>nums[j]){
				int temp=nums[j];
				nums[j]=nums[i];
				nums[i]=temp;
			}
		}
	}
	return ;
}

//2插入排序
void insert_sort(vector<int>& nums){
	for(int i=1;i<nums.size();++i){
		for(int j=i-1;j>=0;--j){
			if(nums[j+1]<nums[j]){
				int temp=nums[j];
				nums[j]=nums[j+1];
				nums[j+1]=temp;
			}
			else{
				break;
			}
		}
	}
	return ;
}

//3并归排序
void merge(vector<int>& nums,int index1,int index2,int index3){	
	vector<int> l,r;
	for(int i=index1;i<=index2;++i){
		l.push_back(nums[i]);
	}
	for(int i=index2+1;i<=index3;++i){
		r.push_back(nums[i]);
	}
	int i=0,j=0;
	l.push_back(INT32_MAX);
	r.push_back(INT32_MAX);
	for(int k=index1;k<=index3;++k){
		if(l[i]<r[j]){
			nums[k]=l[i];
			++i;
		}
		else{
			nums[k]=r[j];
			++j;
		}
	}
	return;
}

void merge_sort(vector<int>& nums,int left,int right){
	if(left<right){
		int middle=left+(right-left)/2;
		merge_sort(nums,left,middle);
		merge_sort(nums,middle+1,right);
		merge(nums,left,middle,right);
	}
	return;
}

//4快速排序
int patition(vector<int> &nums,int left,int right){
	int x=nums[right];
	int i=left-1;
	for(int j=left;j<=right-1;++j){
		if(nums[j]<x){
			i++;
			int temp=nums[i];
			nums[i]=nums[j];
			nums[j]=temp;
		}
	}
	int temp=nums[right];
	nums[right]=nums[i+1];
	nums[i+1]=temp;
	return i+1;
}

void quick_sort(vector<int> &nums,int left,int right){
	int q;
	if(left<right){
		q=patition(nums,left,right);
		quick_sort(nums,left,q-1);
		quick_sort(nums,q+1,right);
	}
}

//5选择排序
void select_sort(vector<int>& nums){
	for(int i=0;i<nums.size();++i){
		int min_index=i;
		for(int j=i+1;j<nums.size();++j){
			if(nums[min_index]>nums[j]){
				min_index=j;
			}
		}
		int temp=nums[i];
		nums[i]=nums[min_index];
		nums[min_index]=temp;
	}
	return;
}

//6计数排序
void counting_sort(vector<int>& nums){
	int min=nums[0],max=nums[0];
	for(int i=0;i<nums.size();++i){
		if(min>nums[i]){
			min=nums[i];
		}
		if(max<nums[i]){
			max=nums[i];
		}
	}
	int record[max-min+1];
	for(int i=0;i<max-min+1;++i){
		record[i]=0;
	}
	for(int i=0;i<nums.size();++i){
		++record[nums[i]-min];
	}
	int index=0;
	for(int i=0;i<nums.size();++i){
		while(record[index]==0){
			++index;
		}
		nums[i]=index+min;
		--record[index];
	}
	return;
}

//7桶排序
void bucket_sort(vector<int>& nums){
	vector<vector<int>> bucket(10,vector<int>());
	for(int i=0;i<nums.size();++i){
		bucket[nums[i]/10].push_back(nums[i]);
		for(int j=bucket[nums[i]/10].size()-2;j>=0;--j){
			if(bucket[nums[i]/10][j]>nums[i]){
				bucket[nums[i]/10][j+1]=bucket[nums[i]/10][j];
				if(j==0){
					bucket[nums[i]/10][0]=nums[i];
				}
			}
			else{
				bucket[nums[i]/10][j+1]=nums[i];
				break;
			}
		}
	}
	for(int i=nums.size()-1;i>=0;--i){
		while(bucket.back().size()==0){
			bucket.pop_back();
		}
		nums[i]=bucket.back().back();
		bucket.back().pop_back();
	}
	return;
}

//8希尔排序
void insertsort(vector<int>& nums,int left,int right,int diff){
	for(int i=left+diff;i<right;i+=diff){
		for(int j=i;j>left;j-=diff){
			if(nums[j]<nums[j-diff]){
				swap(nums[j],nums[j-diff]);
			}
			else{
				break;
			}
		}
	}
}

void shell_sort(vector<int>& nums){
	int left=0;
	int right=nums.size();
	for(int diff=right-left;diff>0;diff/=2){
		for(int i=0;i<right;++i){
			insertsort(nums,left+i,right,diff);
		}
	}
	return;
}


int main(){
	vector<int> nums{5,6,8,3,6,1,4,9,3,0,5,6,2,4,6,7,19,5,42,64,34,34,56,8,98,33};
	int count=100000;
	for(int i=0;i<count;++i){
		nums.push_back(rand());
	}
	//insert_sort(nums);
	//merge_sort(nums,0,nums.size()-1);
	quick_sort(nums,0,nums.size()-1);
	//counting_sort(nums);
	//bucket_sort(nums);
	//shell_sort(nums);
	for(auto num:nums){
		cout<<num<<" ";
	}
	cout<<endl;
	return 0;
}
