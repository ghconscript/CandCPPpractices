#include <iostream>
struct celltype{
	int data;// ElemType == int
	celltype* next;
};
typedef celltype *LIST;// 用头指针代表整个链表
typedef celltype *position // 代表某个node的位置 


void Delete (position p,LIST &L) 
{	position delNode = p->next;
	p->next =delNode->next;
	delete delNode;	
}
void DeleteRepeatElements(LIST& head){// 如果不修改头指针 传入LIST L也可以 
	if(head == NULL||head->next == NULL)
	return;
	position cur = head;
	while (cur!=NULL&& cur->next!=NULL ){
		if (cur->data ==cur->next->data){
		position temp=cur->next;//记录最后一个重复节点 
		while (temp->next!=NULL && temp->next->data == cur->data){
			temp = temp->next;
		}
		position toDelete = cur->next;//第一个重复的 
		cur->next = temp->next;//修改指针的位置 跳过重复的Node 
		while (toDelete != temp->next){
			position nexttoDelete = toDelete->next;
			delete toDelete;
			toDelete = nexttoDelete;
		
		}
		else{
			cur = cur->next;
		}
	}
	}
}
void Reverse(LIST &head){
	if (head==NULL||head->next==NULL)
	return;
	position cur=head;
	position nextTemp=NULL;
	position prev=NULL;
	while(cur!=NULL){
		nextTemp=cur->next;//防止逆置找不到 暂存一下 
		cur->next=prev;//指针反向 
		prev=cur;//前驱指针后移一位 
		cur=nextTemp;//指针后移至暂存的后一位 
	}
	head=prev;//循环结束更新头指针 
}
int main() {
	
}
