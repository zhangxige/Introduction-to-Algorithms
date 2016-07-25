#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution_Find_Maxsubarray{
private:
	vector<int> A;
	vector<int> seq;   //sequence numbers seq[0]=low number;seq[1]=high number;seq[2]=sum; 

	vector<int> Find_Crossing_Subarray(int low,int mid,int high){//找到含有mid的最大子串和
		vector<int> order(3); //作用同seq[3]只不过是局部变量
		int left_sum=INT_MIN;
		int sum=0;
		int i=mid;
		while(i>=0){       //找到左子串最大值
			sum+=A[i];
			if(left_sum<sum){
				left_sum=sum;
				order[0]=i;
			}
			i--;
		}
		int right_sum=INT_MIN;
		sum=0;
		i=mid+1;
		while(i<=high){       //找到右子串最大值
			sum+=A[i];
			if(right_sum<sum){
				right_sum=sum;
				order[1]=i;
			}
			i++;
		}
		order[2]=right_sum+left_sum;
		return order;
	}
	vector<int> Find_Maximum_Subarray(int low,int high){
		vector<int> order(3); //作用同seq[3]只不过是局部变量
		vector<int> low_order(3); //作用同seq[3]只不过是局部变量存储左子串三个值
		vector<int> high_order(3); //作用同seq[3]只不过是局部变量存储右子串三个值
		if(low==high){
			order[0]=low;
			order[1]=high;
			order[2]=A[low];
			return order;
		}
		else{
			int mid=(low+high)/2;
			low_order=Find_Maximum_Subarray(low,mid);
			high_order=Find_Maximum_Subarray(mid+1,high);
			order=Find_Crossing_Subarray(low,mid,high);
			if(low_order[2]>=high_order[2]&&low_order[2]>=order[2])
				return low_order;
			else if(high_order[2]>=low_order[2]&&high_order[2]>=order[2])
				return high_order;
			else
				return order;
		}
	}
public:
	Solution_Find_Maxsubarray(bool mark,int a[],int len){ //输入的是原始数据,mark=false即 a[i]>0都成立,mark=true时a中有正有负
		if(mark){
			for(int i=0;i<len;i++)
				A.push_back(a[i]);
		}
		else 
			for(int i=1;i<len;i++)
				A.push_back(a[i]-a[i-1]);
	}
	void Print_A(){
		cout<<"A:"<<endl;
		for(int i=0;i<A.size();i++)
			cout<<A[i]<<"  ";
		cout<<endl;		
	}
	void Find_MAXIMUM_SUBARRAY(){
		seq= Find_Maximum_Subarray(0,A.size()-1);
		if(seq[2]<0){    //算法导论4.1-4
			seq[2]=0;
			cout<<"MAXIMUM SUBARRAY is empty!"<<endl;
			cout<<seq[2];
			return ;
		}
		Print_A();
		cout<<"result:"<<endl;
		for(int i=0;i<seq.size();i++)
			cout<<seq[i]<<"  ";
		cout<<endl;
	}
	//线性时间求解
	void Find_MAXIMUM_SUBARRAY_Linear_time (){  //算法导论4.1-5
		int sum=0;
		int maxsum=INT_MIN;
		int low=0,high=0;
		for(int i=0;i<A.size();i++){
			sum+=A[i];
			if(sum>maxsum){
				maxsum=sum;
				high=i;
			}
			if(sum<0){
				sum=0;
				low=i+1;
			}
		}
		cout<<low<<" "<<high<<" "<<maxsum<<endl;
	}
	//暴力求解方法
	void Find_MAXIMUM_SUBARRAY_Voilence(){  //算法导论4.1-2
		int sum;
		int maxsum=INT_MIN;
		int low=0,high=0;
		for(int i=0;i<A.size();i++){
			sum=0;
			sum+=A[i];
			for(int j=i+1;j<A.size();j++){
				sum+=A[j];
				if(sum>maxsum){
					maxsum=sum;
					high=j;
					low=i;
				}
			}
			maxsum=max(sum,maxsum);
		}
		std::cout<<low<<" "<<high<<" "<<maxsum<<endl;
	} 
};

int main(){	
	//int a[]={48,35,25,19,14,10,7,5,4};
	int a[]={16,4,1,12,17,9,3,2,8,1,7};
	int len=sizeof(a)/sizeof(int);
	Solution_Find_Maxsubarray s(false,a,len);
	s.Find_MAXIMUM_SUBARRAY_Linear_time();
	s.Find_MAXIMUM_SUBARRAY();

	system("pause");
	return 0;
}
