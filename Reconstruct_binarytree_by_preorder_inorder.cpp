// Definition for binary tree
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Solution {
public:

    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {//一个是先序序列 一个是中序遍历序列
		if(in.size()==1){//如果是叶子节点创建节点返回就
			TreeNode* node;
			node=new TreeNode(pre[0]);
			return node;
		}
		TreeNode* head;//创建该节点
		head=new TreeNode(pre[0]);
		int in_id;
		for(int i=0;i<in.size();i++)//找到该节点在中序遍历序列中位置
			if(in[i]==pre[0]) {
				in_id=i;
				break;
			}
		if(in_id>0) {//如果在对应的中序遍历序列中该节点下标不为0那么pre[1]一定是该节点的左孩子
			vector<int> lpre,lin;
			for(int i=0;i<in_id;i++)
				lin.push_back(in[i]);
			for(int i=1;i<=in_id;i++)
				lpre.push_back(pre[i]);
			head->left=reConstructBinaryTree(lpre,lin);
		}
		if(in_id<in.size()-1){//如果在对应的中序遍历序列中该节点下标不为0那么pre[in_id+1]一定是该节点的右孩子
			vector<int> rpre,rin;
			for(int i=in_id+1;i<in.size();i++){
				rin.push_back(in[i]);
				rpre.push_back(pre[i]);
			}
			head->right=reConstructBinaryTree(rpre,rin);
		}
		return head;
    }
};


int main(){	
	vector<int> pre(8),in(8);
	int pre1[]={1,2,4,7,3,5,6,8};
	int in1[]={4,7,2,1,5,3,8,6};
	for(int i=0;i<8;i++){
		pre[i]=pre1[i];
		in[i]=in1[i];
	}

	Solution s;
	s.reConstructBinaryTree(pre,in);
	
	system("pause");
	return 0;
}
