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
void LeftForward(LIST &head,int k){
	/*
	int i;
	position last = head->next;//�洢�ƶ���֮���last
	position final = head->next;
	while(final->next!=NULL){//�洢ԭ�������һλ 
		final=final->next;
	} 
	
	for(i=1;i<k;i++){
		last=last->next;//�ҵ���last��λ�� 
	}final->next=head->next;
	head->next=last->next;
	last->next=NULL;
	
	*/
	//���õ�д��  Ҳ����ת��Ϊѭ������ 
	int n;
	position tail=head->next;
	position new_tail=head->next;
	while(tail->next!=NULL){
		n++;
		tail=tail->next;
	}
	k=k%n;
	for (i=1;i<k;i++){
		new_tail=new_tail->next;
	}
	tail->next=head->next;
	head->next=new_tail->next;
	new_tail->next=NULL;
	
}
void RightForward(LIST &head,int k){
	int n;
	position tail=head->next;
	position new_tail=head->next;
	while(tail->next!=NULL){
		n++;
		tail=tail->next;
	}
	k=k%n;
	for (i=1;i<n-k;i++){
		new_tail=new_tail->next; 
	}
	tail->next=head->next;
	head->next=new_tail->next;
	new_tail->next=NULL;
}
void INSERT (position p1,position p2){//���� ��p2����p1�� 
	p2->next=p1->next;
	p1->next=p2; 
}
void merge (LIST &L1,LIST &L2){
	//���轵�� ������
	position p=L1->next;
	position prev=L1;
	position q=L2->next;
	position temp=NULL;
	while(p!=NULL&&q!NULL){
		if(p->data<=q->data){
			temp=q->next;
			INSERT(prev,q);
			prev=q;
			q=temp;
		}else{
			prev=p;
			p=p->next;
		}
	}
	if(q!=NULL){//while ѭ�������� p��NULL ������prev->next ����q 
		prev->next=q;	
	}
	L2->next=NULL;
}

int main() {
	
	
}
