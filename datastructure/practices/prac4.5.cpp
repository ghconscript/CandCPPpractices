/*
lc 25
给你链表的头节点 `head` ，每 `k` 个节点一组进行翻转，请你返回修改后的链表。
`k` 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 `k` 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

*/
struct ListNode{
	int data;
	ListNode * next;
	ListNode(int x) : data(x), next(nullptr) {}
};
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode dummy(-1);//虚拟头节点
		ListNode* curr = &dummy, *nextHead = head;
		while(true){
			int count = 0;
			for(; count<k && nextHead; count++) nextHead = nextHead->next;
			if(count != k) break;
			curr->next = reverseList(head, nextHead);
			curr = head;
			head = nextHead;
		}
		return dummy.next;
	}
protected:
	ListNode* reverseList(ListNode* head, ListNode* nextHead){
		ListNode* pre = nextHead;
		while(head != nextHead){
			ListNode* next = head->next;
			head->next = pre;
			pre = head;
			head = next;
		}
		return pre;
	}
};
