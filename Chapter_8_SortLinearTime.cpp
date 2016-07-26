#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution_Sort_LineTime{ //线性时间排序算法
private:
	vector<int> A;  //原始输入序列 A中的元素必须>=0
	vector<int> B;  //输出序列
	int A_length;

	int Find_k(vector<int> &x){ //找到数组中最大元素
		int max=INT_MIN;
		for(int i=0;i<x.size();i++)
			if(max<x[i])
				max=x[i];
		return max;
	}

	void Counting_Sort(vector<int> &a,vector<int> &b,int k){ //计数排序,输出结果在b中,a和b大小必须相同
		vector<int> C(k+1,0);
		for(int i=0;i<A.size();i++)
			C[a[i]]=C[a[i]]+1;
		//C[i] contains the number of element equal to i
		for(int i=1;i<=k;i++)
			C[i]=C[i]+C[i-1];
		for(int i=a.size()-1;i>=0;i--){
			b[C[a[i]]-1]=A[i];          //注意和书上的差别，书上数组B是从[1,...,lenght]这里是从[0,...,length-1]
			C[a[i]]--;
		}
	}

	void Counting_Sort_Fixed(vector<int> &a,vector<int> &b,vector<int> &c,int k){ 
		vector<int> C(k+1,0);
		for(int i=0;i<a.size();i++)
			C[a[i]]=C[a[i]]+1;
		//C[i] contains the number of element equal to i
		for(int i=1;i<=k;i++)
			C[i]=C[i]+C[i-1];
		for(int i=a.size()-1;i>=0;i--){
			b[C[a[i]]-1]=c[i];          //注意和书上的差别，书上数组B是从[1,...,lenght]这里是从[0,...,length-1]
			C[a[i]]--;
		}
	}

	void Counting_Sort_Fixed(vector<int> &a,vector<string> &b,vector<string> &c,int k){ //用于字符串排序
		vector<int> C(k+1,0);
		for(int i=0;i<a.size();i++)
			C[a[i]]=C[a[i]]+1;
		//C[i] contains the number of element equal to i
		for(int i=1;i<=k;i++)
			C[i]=C[i]+C[i-1];
		for(int i=a.size()-1;i>=0;i--){
			b[C[a[i]]-1]=c[i];          //注意和书上的差别，书上数组B是从[1,...,lenght]这里是从[0,...,length-1]
			C[a[i]]--;
		}
	}

public:
	Solution_Sort_LineTime(int a[],int len){
		for(int i=0;i<len;i++)
			A.push_back(a[i]);
		A_length=len;
		B=A;
	}

	void Radix_SORT(int d){			 //基数排序排序位数为d的
		vector<int> B(A.size(),0);   //存放每次排序后的A,最后会赋回A
		vector<int> A_i(A.size(),0); //存放A的第i位数字，用于计数排序
		int j=0;
		while(j<d){
			for(int i=0;i<A.size();i++){
				A_i[i]=A[i];
				for(int k=0;k<j;k++)
					A_i[i]=A_i[i]/10;
				A_i[i]=A_i[i]%10;
			}
			int k=Find_k(A_i);
			Counting_Sort_Fixed(A_i,B,A,k);
			A=B;
			j++;
		}
		Print_A(A);
	}

	void Counting_SORT(){ // 计数排序，排列自己的数组A
		int k=Find_k(A);
		Counting_Sort(A,B,k);
		Print_A(B);
	}

	void Print_A(vector<int> A){   //打印数组
		cout<<"Vector:"<<endl;
		for(int i=0;i<A.size();i++)
			cout<<A[i]<<"  ";
		cout<<endl;		
	}

	void Str_Counting_SORT(vector<string> &str){ //字符串的基数排序
		int d=INT_MIN;                //d是最大字符串长度
		for(int i=0;i<str.size();i++){
			int temp=str[i].length();
			if(d<temp)
				d=temp;
		}
		vector<string> B(str.size());      //存放每次排序后的str,最后会赋回str
		vector<int> str_i(str.size());    //存放str的第i位数字，用于计数排序
		while( d > 0 ){
			for(int i = 0;i < str.size(); i++){
				int temp = str[i].length();
				if( temp < d )
					str_i[i] = 0;
				else
					str_i[i] = str[i][d-1]-'A'+1;
			}
			int k = Find_k(str_i);
			Counting_Sort_Fixed(str_i,B,str,k);
			str = B;
			d--;
		}
	}
};

int main(){	
	//int a[]={2,5,3,0,2,3,0,3};
	//int a[]={16,4,1,12,17,9,3,2,8,1,7};
	int a[]={329,457,657,839,436,720,355};
	int len=sizeof(a)/sizeof(int);
	string str[10]={"DFE","a","adfd","dcDE","ABC","DS","DDFS","X","CD","ZFEW"};
	vector<string> str_v;
	for(int i=0;i<10;i++)
		str_v.push_back(str[i]);
	Solution_Sort_LineTime s(a,len);
	//s.Radix_SORT(3);//基数排序
	s.Str_Counting_SORT(str_v);//字符串排序

	system("pause");
	return 0;
}
