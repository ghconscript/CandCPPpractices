//给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。
#include<iostream>
using namespace std;
struct Node {
	int data;
	Node *next;
};

typedef Node* pos;
typedef Node* head;
class Solution {
public:
	pos reverse(pos head) {
		pos prev = NULL;
		pos cur = head ->next;
		pos tmp = cur->next;
		while (cur!= NULL) {
			tmp = cur-> next;
			cur->next = prev;
			prev = cur;
			cur = tmp;
		}
		head->next = prev;
		tmp = NULL;
		return head;
	}
	pos fun(pos head,int n){
		if(head->next == NULL) return head;
		if(head->next->next == NULL){
			head->next = NULL;
			return head;
		}
		pos cur = head;
		for(int i=0;i<n-1;i++){
			cur = cur->next;
		}
		pos tmp = cur ->next;
		cur->next = tmp ->next;
		delete tmp;
		return head;
		
	}
	

};
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
int main() {
	pos head1 = new Node;
	Utils::newLink(head1, 6);
	Utils::printLink(head1);
	Solution sol;
	cout<<sol.fun(sol.reverse(head1),2);
	sol.reverse(head1);
	Utils::printLink(head1);
	return 0;
}
