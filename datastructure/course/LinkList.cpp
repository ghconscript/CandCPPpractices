#include <iostream>
using namespace std;
struct celltype {
	int data;// ElemType == int
	celltype* next;
};
typedef celltype *LIST;// 用头指针代表整个链表
typedef celltype *position; // 代表某个node的位置


void Delete (position p,LIST &L) {
	position delNode = p->next;
	p->next =delNode->next;
	delete delNode;
}
void DeleteRepeatElements(LIST& head) { // 如果不修改头指针 传入LIST L也可以
	if(head == NULL||head->next == NULL)
		return;
	position cur = head->next;
	while (cur!=NULL&& cur->next!=NULL ) {
		if (cur->data ==cur->next->data) {
			position temp=cur->next;//记录最后一个重复节点
			while (temp->next!=NULL && temp->next->data == cur->data) {
				temp = temp->next;
			}
			position toDelete = cur->next;//重复的
			cur->next = temp->next;//修改指针的位置 跳过重复的Node
			position end = temp->next;
			while (toDelete->data!= end->data) {
				position nexttoDelete = toDelete->next;
				delete toDelete;
				toDelete = nexttoDelete;
			}
		} else {
			cur = cur->next;
		}
	}

}
void Reverse(LIST &head) {
	if (head==NULL||head->next==NULL)
		return;
	position cur=head->next;
	position nextTemp=NULL;
	position prev=NULL;
	while(cur!=NULL) {
		nextTemp=cur->next;//防止逆置找不到 暂存一下
		cur->next=prev;//指针反向
		prev=cur;//前驱指针后移一位
		cur=nextTemp;//指针后移至暂存的后一位
	}
	head->next=prev;//循环结束更新头指针
}
void LeftForward(LIST &head,int k) {
	/*
	int i;
	position last = head->next;//存储移动完之后的last
	position final = head->next;
	while(final->next!=NULL){//存储原来的最后一位
		final=final->next;
	}

	for(i=1;i<k;i++){
		last=last->next;//找到了last的位置
	}final->next=head->next;
	head->next=last->next;
	last->next=NULL;

	*/
	//更好的写法  也可以转化为循环链表
	int n=0;
	position tail=head->next;
	position new_tail=head->next;
	while(tail->next!=NULL) {
		n++;
		tail=tail->next;
	}
	k=k%n;
	for (int i=1; i<k; i++) {
		new_tail=new_tail->next;
	}
	tail->next=head->next;
	head->next=new_tail->next;
	new_tail->next=NULL;

}
void RightForward(LIST &head,int k) {
	int n=0;
	position tail=head->next;
	position new_tail=head->next;
	while(tail->next!=NULL) {
		n++;
		tail=tail->next;
	}
	k=k%n;
	for (int i=1; i<n-k; i++) {
		new_tail=new_tail->next;
	}
	tail->next=head->next;
	head->next=new_tail->next;
	new_tail->next=NULL;
}
void INSERT (position p1,position p2) { //辅助 将p2插入p1后
	p2->next=p1->next;
	p1->next=p2;
}
void merge (LIST &L1,LIST &L2) {
	//假设降序 并后降序
	position p=L1->next;
	position prev=L1;
	position q=L2->next;
	position temp=NULL;
	while(p!=NULL&&q!=NULL) {
		if(p->data<=q->data) {
			temp=q->next;
			INSERT(prev,q);
			prev=q;
			q=temp;
		} else {
			prev=p;
			p=p->next;
		}
	}
	if(q!=NULL) { //while 循环结束后 p是NULL 所以是prev->next 等于q
		prev->next=q;
	}
	L2->next=NULL;
}

LIST createList(int arr[],int n) {
	LIST head = new celltype;
	head->next = NULL;
	position tail = head;
	for (int i = 0; i<n; i++) {
		position newNode = new celltype;
		newNode->data = arr[i];
		newNode->next = NULL;
		tail->next=newNode;
		tail = newNode;
	}
	return head;
}
void printList(LIST head,const string &msg) {
	cout<<msg;
	position p=head->next;
	while(p!=NULL) {
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
void destroyList(LIST &head) {
	position p = head;
	position temp = p;
	while (p!=NULL) {
		temp = p;
		p=p->next;
		delete temp;
	}
	head = NULL;
}
int main() {
	int data1[]= {1,2,2,3,3,3,4};
	int data2[]= {1,2,3,4,5};
	int data3[]= {1,2,3,4,5};
	LIST L1= createList(data1,7);
	LIST L2 = createList(data2,5);
	LIST L3 = createList(data3,5);
	printList(L1, "测试1-删除重复前：");
	DeleteRepeatElements(L1);
	printList(L1, "测试1-删除重复后：");
	destroyList(L1);
	printList(L2, "测试2-反转前：");
	Reverse(L2);
	printList(L2, "测试2-反转后：");
	destroyList(L2);
	printList(L3, "测试3-左移前：");
	LeftForward(L3, 2);
	printList(L3, "测试3-左移2位后：");
	destroyList(L3);
	cout<<endl;
	return 0;

}
