#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution_SORT {
private:
	vector<int> A;        //存放数据
	int A_length;					//数组长度

	void Merge(int p,int q,int r){  //合并两个有序表
		int n1=q-p+1;
		int n2=r-q;
		vector<int> L,R;
		int i,j;
		for(i=0;i<n1;i++)
			L.push_back(A[p+i]);
		for(j=0;j<n2;j++)
			R.push_back(A[q+1+j]);
		L.push_back(INT_MAX);
		R.push_back(INT_MAX);
		i=0;
		j=0;
		for(int k=p;k<=r;k++){
			if(L[i]<=R[j]){
				A[k]=L[i];
				i++;
			}
			else{
				A[k]=R[j];
				j++;
			}
		}
	}

	void Merge_Sort(int p,int r){       //归并排序
		if(p<r){
			int q=(p+r)/2;
			Merge_Sort(p,q);
			Merge_Sort(q+1,r);
			Merge(p,q,r);
		}
	}

	int Partion(int p,int r){               //快速排序使得A[p..i]<A[i+1]<A{i+2,...r}
		int x=A[r];
		int i=p-1;
		for(int j=p;j<=r-1;j++){
			if(A[j]<=x){
				i=i+1;
				swap(A[i],A[j]);
			}
		}
		swap(A[i+1],A[r]);
		return i+1;
	}	
	
	void Quik_Sort(int p,int r){           //快速排序部分有序
		if(p<r){
			int q=Partion(p,r);
			 Quik_Sort(p,q-1);
			 Quik_Sort(q,r);
		}
	}

	void Insertion_Sort(vector<int*> A,int length){		//带参数的插入排序用于Shell_Sort,通过指针操作原数组
			for(int j=1;j<length;j++){
			int key=*A[j];
			int i=j-1;
			while(i>=0&&*A[i]>key){
				*A[i+1]=*A[i];
				i=i-1;
			}
			*A[i+1]=key;
		}
	}
	void Shell_Sort(int d){				//希尔排序，插入排序的改进版本,d表示增量
 		while(d>=1){
			for(int i=0;i<d;i++){
				vector<int*> temp;
				int j=i;
				while(j<=A_length-1){
					temp.push_back(&A[j]);
					j+=d;
				}
				Insertion_Sort(temp,temp.size());
			}
			d--;
			A;
		}
	}

public:
	Solution_SORT():A_length(0){}
	Solution_SORT(int a[],int n){
		for(int i=0;i<n;i++)
			A.push_back(a[i]);
		A_length=n;
	}

	void print_A(vector<int> data,int n){		//打印出数组A
		cout<<"result:"<<endl;
		for(int i=0;i<n;i++)
			cout<<data[i]<<"  ";
		cout<<endl;
	}

	void Insertion_SORT(){				//插入排序
		for(int j=1;j<A_length;j++){
			int key=A[j];
			int i=j-1;
			while(i>=0&&A[i]>key){
				A[i+1]=A[i];
				i=i-1;
			}
			A[i+1]=key;
		}
		print_A(A,A_length);
	}

	void Merge_SORT(){                  //归并排序对外借口
		 Merge_Sort(0, A_length-1);
		 print_A(A,A_length);
	}

	void Quick_SORT(){                 //快速查找
		Quik_Sort(0,A_length-1);
	    print_A(A,A_length);
	}

	int Find_2Fen(int p,int r,int key){//算法导论2.3-6
		if(p<=r){
			int q=(p+r)/2;
			if(A[q]==key) return q;
			else if(A[q]>key)
				return Find_2Fen(p,q,key);
			else
				return Find_2Fen(q+1,r,key);
		}
	}
	int Find_2FEN(int key){           //算法导论2.3-6
		return Find_2Fen(0,A_length-1,key);
	}

	bool Find_add_equal_x(int x){          //算法导论2.3-7
		 Merge_SORT();
		 int i=0;
		 int j=A_length-1;
		 while(i<j){
			int temp=A[i]+A[j];
			if(temp==x) return true;
			else if(temp<x) i++;
			else j--;
		 }
		 return false;
	}
	void Shell_SORT(int n){            //希尔排序对外借口
		if(n<A_length){
			Shell_Sort(3);
			print_A(A,A_length);
		}
		else 
			cout<<"input n is wrong!"<<endl;
	}
};

int main(){	
	//int a[]={5,2,4,6,1,3,45,32,21,51};
	int a[]={16,4,10,14,7,9,3,2,8,1,7};
	int len=sizeof(a)/sizeof(int);
	 Solution_SORT s(a,len);

	 s.Shell_SORT(4);
	system("pause");
	return 0;
}
