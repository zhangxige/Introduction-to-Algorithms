#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Heap{
public:
	vector<int> A;                  //存放堆数据
	int A_length;					//存放数据的长度
	int A_size;                     //构造好的堆长度
	Heap():A_length(0){}
	Heap(vector<int> data):A(data),A_length(data.size()),A_size(1){
	}
	Heap(int a[],int n){
		for(int i=0;i<n;i++)
			A.push_back(a[i]);
		A_length=n;
		A_size=1;
	}

};

class Heap_Operation{				//堆操作/维护定义
private:							
	int Parent(int i){              //返回父亲节点编号
		return (i+1)/2-1;			//需要注意如果传进来的i非法
	}
	int	Left(int i){				//返回左孩子节点编号
		return (i+1)*2-1;
	}
	int Right(int i){				//返回右孩子节点编号
		return (i+1)*2;
	}

	void Max_HeapIfy(Heap &H_A,int i){        //调整最大堆，使得parent值大于child值
		int l=Left(i);
		int r=Right(i);
		int largest;
		if(l<=H_A.A_size-1&&H_A.A[l]>H_A.A[i])
			largest=l;
		else
			largest=i;
		if(r<=H_A.A_size-1&&H_A.A[r]>H_A.A[largest])
			largest=r;
		if(largest!=i){
			swap(H_A.A[i],H_A.A[largest]);
			Max_HeapIfy(H_A,largest);
		}
	}
public:
	Heap A;						              //存放堆数据	
	Heap_Operation(vector<int> data):A(data){ //构造函数
		 Build_Max_Heap2(A);
	}
	Heap_Operation(int a[],int n):A(a,n){     //构造函数
		 Build_Max_Heap(A);
	}
	void Build_Max_Heap(Heap &H_A){          //创建堆
		H_A.A_size=A.A_length;
		for(int i=H_A.A_length/2-1;i>=0;i--)
			Max_HeapIfy(H_A,i);
	}
	void Build_Max_Heap2(Heap &H_A){          //创建堆第二种方法
		H_A.A_length=1;
		for(int i=1;i<H_A.A.size();i++)
			Max_Heap_Insert(H_A,H_A.A[i]);
	}

	void Print_Heap(Heap &H_A){				//打印堆
		int mark_endl=2;			//判断是否输出换行标志
		cout<<"this heap ;"<<endl;
		for(int i=0;i<H_A.A.size();i++){//打印的是A中所有元素而不是堆中元素
			cout<<H_A.A[i]<<"("<<i+1<<")  ";
			if(i+2==mark_endl){
				cout<<endl;
				mark_endl*=2;
			}
		}
	}

	void Heap_SORT(Heap &H_A){               //堆排序
		 Build_Max_Heap(H_A);
		 for(int i=H_A.A.size()-1;i>=1;i--){
			swap(H_A.A[0],H_A.A[i]);
			H_A.A_size--;
			Max_HeapIfy(H_A,0);
		 }
	}

	void Heap_Increase_Key(Heap &H_A,int i,int key){ //把堆中标号i的元素增加到key,其中i是非零自然数序列
		i-=1;
		if(key<H_A.A[i]){
			cout<<"new key is smaller than vurrent key!"<<endl;
			return;
		}
		H_A.A[i]=key;
		while(i>0&&H_A.A[Parent(i)]<H_A.A[i]){
			swap(H_A.A[i],H_A.A[Parent(i)]);
			i=Parent(i);
		}
	}

	void Max_Heap_Insert(Heap &H_A,int x){ //把元素x插入到集合中		
		H_A.A.push_back(INT_MIN);	
		H_A.A_length++;
		Heap_Increase_Key(H_A,H_A.A_length,x);
	}

	int Heap_Maximum(Heap &H_A){     //返回具有最大键字的元素
		return H_A.A[0];
	}

	int Heap_Delete(Heap &H_A,int i){//删除节点号为i的节点
		int temp=H_A.A[i-1];		
		swap(H_A.A[H_A.A.size()-1],H_A.A[i-1]);
		H_A.A_size--;
		Max_HeapIfy(H_A,i-1);
		H_A.A.pop_back();
		return temp;
	}

	int Heap_Extract_Max(Heap &H_A){         //返回并删除最大值并
		int temp=Heap_Delete(H_A,1);
		return temp;
	}
};

int main(){
	int a[]={16,4,10,14,7,9,3,2,8,1,7};
	int len=sizeof(a)/sizeof(int);
	Heap_Operation s(a,len);
	s.Print_Heap(s.A);
	
	return 0;
}
