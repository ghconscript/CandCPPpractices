#include <iostream>
struct celltype{
	int data;// ElemType == int
	celltype* next;
};
typedef celltype *LIST;// ��ͷָ�������������
typedef celltype *position // ����ĳ��node��λ�� 


void Delete (position p,LIST &L) 
{	position delNode = p->next;
	p->next =delNode->next;
	delete delNode;	
}
void DeleteRepeatElements(LIST& head){// ������޸�ͷָ�� ����LIST LҲ���� 
	if(head == NULL||head->next == NULL)
	return;
	position cur = head;
	while (cur!=NULL&& cur->next!=NULL ){
		if (cur->data ==cur->next->data){
		position temp=cur->next;//��¼���һ���ظ��ڵ� 
		while (temp->next!=NULL && temp->next->data == cur->data){
			temp = temp->next;
		}
		position toDelete = cur->next;//��һ���ظ��� 
		cur->next = temp->next;//�޸�ָ���λ�� �����ظ���Node 
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
		nextTemp=cur->next;//��ֹ�����Ҳ��� �ݴ�һ�� 
		cur->next=prev;//ָ�뷴�� 
		prev=cur;//ǰ��ָ�����һλ 
		cur=nextTemp;//ָ��������ݴ�ĺ�һλ 
	}
	head=prev;//ѭ����������ͷָ�� 
}
int main() {
	
}
