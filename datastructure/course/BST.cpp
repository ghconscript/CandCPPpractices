#include<iostream>
#include"BinarySearch.cpp"
using namespace std;
struct TreeNode{
	int data;
	struct TreeNode *lchild,*rchild;
	TreeNode(int value)
	:data(value),lchild(nullptr),rchild(nullptr){}
};
typedef TreeNode* BST;
typedef TreeNode* pos;
BST Search(int k,BST F){
	BST pos = F;
	if(pos==NULL||k==pos->data){
		return pos;
	}
	if(k<pos->data){
		return Search(k,pos->lchild);
	}
	if(k>pos->data){
		return Search(k,pos->rchild);
	}
}
BST Insert(int data,pos p){
	if(p==nullptr){
		return new TreeNode(data);//返回TreeNode对应的指针
	}else if(data<p->data){
		p->lchild=Insert(data,p->lchild);
	}else if(data>p->data){
		p->rchild=Insert(data,p->rchild);
	}else{
		cout<<"与节点的data相等。本来应该给节点加一个cnt的但是我懒所以直接跳过了"<<endl;
	}
	return p;
}
pos findMinNode(BST root){
	while(root->lchild!=nullptr){
		root = root->lchild;
	}
	return root;
}//不断找左子树的左孩子
BST Delete(BST root,int value){
	if(root==nullptr){
		return root;
	}
	if(value<root->data){
		root->lchild=Delete(root->lchild,value);
	}else if(value>root->data){
		root->rchild=Delete(root->rchild,value);
	}else{
		if(root->lchild==nullptr){
			pos tmp= root->rchild;//如果右也是null 那么相当于直接删除该节点
			delete root;
			return tmp;
		}else if(root->rchild==nullptr){
			pos tmp = root->lchild;
			delete root;
			return tmp;
		}else{
			pos s = findMinNode(root->rchild);//找比它大的最小的那个替代它，即右子树的最左下 
			root->data=s->data;
			root->rchild=Delete(root->rchild,s->data);//把那个s拿上来再删除之 s即sucessor
		}
	}
	return root;
}
void inorderTraversal(BST root){
	if(root==nullptr){
		return;
	}
	inorderTraversal(root->lchild);
	cout<<root->data<<" ";//探到叶子节点的时候会返回然后执行这步，即输出data
	inorderTraversal(root->rchild);
}
int currentDepth = 1;
int sum = 0;
int cnt = 0;
/*double CalculateASL(BST root ,int currentDepth, int &sum,int &cnt){
	if(root == nullptr){
		return 0;
	}
	sum+=c urrentDepth;
	cnt++;
	CalculateASL(root->lchild,currentDepth+1,sum,cnt);
	CalculateASL(root->rchild,currentDepth+1,sum,cnt);
	return static_cast<double>(sum)/cnt;
}*/

int main(){
	
	return 0;	
}
