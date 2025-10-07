/*给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。
lc 23
*/
#include<iostream>
#include<algorithm>
using namespace std;
struct Node{
	int data;
	Node* next;
};
typedef Node* pos;
typedef Node* head;
class Utils{
	int YourVar;
public:
	static void newLink(pos head, int n) {
		pos tail = head;
		for (int i = 0; i < n; i++) {
			pos tmp = new Node;
			tmp->next = nullptr;//必须初始化 防止野指针 要不然print出来一堆32312645
			tail -> next = tmp;
			cin >> tmp->data;
			tail = tmp;
		}
	}
	static void printLink(pos head){
		pos cur = head->next;
		while(cur!=NULL){
			cout<<cur->data<<endl;
			cur = cur->next;
		}
	}
};
class Solution {
public:
	pos merge(head a,head b) {
		if ((!a)||(!b)) return a ? a : b;
		head h = new Node;
		pos tail = h;
		pos aPtr = a->next;
		pos bPtr = b->next;
		while (aPtr && bPtr){
			if (aPtr->data < bPtr->data){
				tail ->next = aPtr; aPtr=aPtr->next;
			}else{
				tail ->next = bPtr; bPtr=bPtr->next;
			}
			tail = tail->next;
		}
		tail->next = (aPtr?aPtr:bPtr);
		return h;
		
	}
	pos fun1(vector<pos>& lists){//挨个两两合并
		pos ans = nullptr;
		for(int i=0;i<lists.size();i++){
			ans = merge(ans,lists[i]);
		}
		return ans;
	}
	pos fun2(vector<pos>& lists,int l,int r){
		if (l == r) return lists[l];
		if (l > r) return nullptr;
		int mid = (l+r)>>1;
		return merge(fun2(lists,l,mid),fun2(lists,mid+1,r));
	}//分治合并 
};
int main(){
	head head1 = new Node;
	head head2 = new Node;
	head head3 = new Node;
	Utils::newLink(head1,6);
	Utils::newLink(head2,5);
	Utils::newLink(head3,4);
	vector<pos> lists;
	lists.push_back(head1);
	lists.push_back(head2);
	lists.push_back(head3);
	Solution sol;
	Utils::printLink(sol.fun2(lists,0,lists.size()-1));
}
