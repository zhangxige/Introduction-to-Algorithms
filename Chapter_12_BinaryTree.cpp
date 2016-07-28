#include<iostream>
#include<vector>
#include<cmath>
#include<stack>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *lchild,*rchild,*parent;
	TreeNode():lchild(NULL),rchild(NULL),parent(NULL){}
}; 

class Solution_BinaryTree{ //二叉搜索树
private:
	TreeNode *root;

	TreeNode* CreatNode(int n){ //创建一个节点
		TreeNode* temp;
		temp = new TreeNode;
		temp->val = n;
		return temp;
	}

public:
	TreeNode *Return_Root(){     //返回根节点对外借口
		return root;
	}
	
	// a中输入的数据必须为二叉搜索树的合法数据 也就是说 父节点的数据一定要大于其左子树的数据小于其右子树数据（关键字）
	bool Creat_Tree(int a[],int n){ //如果a[i]<0就在该插入节点的位置插入NULL
		if( n<1 ){
			cout<<"Input vector a is empty"<<endl;
			return false;
		}
		root=new TreeNode;
		root->val = a[0];
		vector<int> p_id(n,0);           //存储树的关系结构
		vector<TreeNode*> Tree_address;	 //存储生成的节点地址
		p_id[0]=-1;                      //根节点没有父节点
		Tree_address.push_back(root);
		int num=0;                       // num=1表示左孩子 num=2表示右孩子
		for(int i = 0,j=1; j<n ; j++){  //找到树的结构关系
			if(a[j]<0) Tree_address.push_back(NULL);
			else{
				TreeNode* temp = CreatNode(a[j]);
				Tree_address.push_back(temp);
			}
			if(a[i]<0){
				while(a[i]<0&&i<n){
					i++;
				}
			}
			p_id[j]=i;
			num++;
			if(num==2){
				i++;
				num=0;
			}
		}
		// 根据p_id的关系结构构造树结构
		for(int j=1; j<n ; j++){
			if(j%2!=0){
				Tree_address[p_id[j]]->lchild=Tree_address[j];
				if(Tree_address[j]!=NULL)
					Tree_address[j]->parent=Tree_address[p_id[j]];
			}
			else{
				Tree_address[p_id[j]]->rchild=Tree_address[j];
				if(Tree_address[j]!=NULL)
					Tree_address[j]->parent=Tree_address[p_id[j]];
			}
		}
		return true;
	}

	void display(TreeNode *root)        //显示树形结构  先序遍历
	{ 
		if( root != NULL ) { 
			cout<<root->val; 
			if(root->lchild != NULL || root->rchild != NULL) { 
				 cout<<'('; 
				 display(root->lchild); 
			} 
			if(root->rchild != NULL || root->lchild != NULL) { 
				 cout<<','; 
				 display(root->rchild); 
				 cout<<')'; 
			} 
		} 
	} 

	void Preorder_Recursion( TreeNode *root ){ //先序递归遍历
		if( root != NULL ){
			cout<<root->val<<"  ";
			Preorder_Recursion( root->lchild );
			Preorder_Recursion( root->rchild );
		}
	}

	void Inorder_Recursion( TreeNode *root ){ //中序递归遍历
		if( root != NULL ){
			Inorder_Recursion( root->lchild );
			cout<<root->val<<"  ";
			Inorder_Recursion( root->rchild );
		}
	}

	void Postorder_Recursion( TreeNode *root ){ //先序递归遍历
		if( root != NULL ){
			Postorder_Recursion( root->lchild );
			Postorder_Recursion( root->rchild );
			cout<<root->val<<"  ";
		}
	}

	void PreOrder_NonRecursion(TreeNode *root)     //非递归前序遍历 
	{
		stack<TreeNode*> s;
		TreeNode *p=root;
		while(p!=NULL||!s.empty())
		{
			while(p!=NULL)
			{
				cout<<p->val<<" ";
				s.push(p);
				p=p->lchild;
			}
			if(!s.empty())
			{
				p=s.top();
				s.pop();
				p=p->rchild;
			}
		}
	}

	void InOrder_NonRecursion(TreeNode *root)      //非递归中序遍历
	{
		stack<TreeNode*> s;
		TreeNode *p=root;
		while(p!=NULL||!s.empty())
		{
			while(p!=NULL)
			{
				s.push(p);
				p=p->lchild;
			}
			if(!s.empty())
			{
				p=s.top();
				cout<<p->val<<" ";
				s.pop();
				p=p->rchild;
			}
		}    
	} 

	void PostOrder_NonRecursion(TreeNode *root)    //非递归后序遍历
	{
		stack<TreeNode*> s;
		TreeNode *p=root;
		TreeNode *temp;
		while( p != NULL || !s.empty() ){
		}
	} 

	TreeNode *Tree_Search(TreeNode *root,int k){  //递归版本查询关键字是否存在
		if( root == NULL || k == root->val ){
			return root;
		}
		if( k < root->val )
			return Tree_Search( root->lchild,k );
		else
			return Tree_Search( root->rchild,k );
	}
	
	TreeNode *Iterative_Tree_Search(TreeNode *root,int k){ //非递归 迭代版本查询关键字是否存在
		TreeNode* temp = root;
		while( temp != NULL && temp->val != k ){
			if( k < temp->val )
				temp = temp->lchild;
			else if( k > temp->val )
				temp = temp->rchild;
		}
		return temp;
	}

	TreeNode *Tree_Maximum(TreeNode *root){   //返回最大值
		TreeNode *temp = root;
		while( temp->rchild != NULL )
			temp = temp->rchild;
		return temp;
	}

	TreeNode *Tree_Minimum(TreeNode *root){   //返回最小值
		TreeNode *temp = root;
		while( temp->lchild != NULL )
			temp = temp->lchild;
		return temp;
	}

	TreeNode *Tree_Successor(TreeNode *root){  //返回某一个节点的后继节点,这里root表示任意一个节点
		TreeNode *temp=root;
		if( temp->rchild != NULL )
			return Tree_Minimum( temp->rchild );
		temp = root->parent;
		while(temp != NULL && root == temp->rchild ){
			root = temp;
			temp = temp->parent;
		}
		return temp;
	}

	TreeNode *Tree_Predecessor(TreeNode *root){  //返回某一个节点的前驱节点,这里root表示任意一个节点
		TreeNode *temp=root;
		if( temp->lchild != NULL )
			return Tree_Maximum( temp->lchild );
		temp = root->parent;
		while(temp != NULL && root == temp->lchild ){
			root = temp;
			temp = temp->parent;
		}
		return temp;
	}

	void Tree_Insert(TreeNode *root,int k){  //插入节点
		TreeNode *y,*x,*z;
		z=CreatNode(k);
		y=NULL;
		x=root;
		while( x != NULL){
			y=x;
			if( z->val < x->val )
				x = x->lchild;
			else
				x = x->rchild;
		}
		z->parent = y;
		if( y == NULL )
			root = z;             // 当树为空时
		else if( z->val < y->val)
			y->lchild = z;
		else
			y->rchild = z;
	}

	void Transplant(TreeNode *root,TreeNode *u,TreeNode *v){  //调整节点
		if( u->parent == NULL)
			root = v;
		else if ( u == u->parent->lchild )
			u->parent->lchild = v;
		else 
			u->parent->rchild = v;
		if( u!= NULL )
			v->parent = u->parent;
	}

	bool Tree_Delete(TreeNode *root,TreeNode *z){  //删除节点 z
		TreeNode *y;
		if( z->lchild == NULL )
			Transplant(root,z,z->rchild);
		else if( z->rchild ==NULL )
			Transplant(root,z,z->lchild);
		else{
			y = Tree_Minimum(z->rchild);
			if( y->parent != z ){
				Transplant(root,y,y->rchild);
				y->rchild = z->rchild;
				y->rchild ->parent = y;
			}
			Transplant(root,z,y);
			y->lchild = z->lchild;
			y->lchild->parent = y;
		}
	}
};


int main(){	
	int a[] = {4,2,5,-1,3,-1,8,-1,-1,7,-1,-1};//按照每一层树高插入元素，如果a[i]<0,表示插入位置为NULL
	//int a[] = {6,5,7,2,5,-1,8};
	int len = sizeof(a)/sizeof(int);
	Solution_BinaryTree s;
	s.Creat_Tree(a,len);

	s.display( s.Return_Root() );

	system("pause");
	return 0;
}
