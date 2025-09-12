#include <iostream>
#include <algorithm>
#define MAX 100
using namespace std;
struct List{
	int elements[MAX];// ElemType == int 
	int last;
};
void Delete(struct List& L, int target){
	if(target>L.last||target<0){
		cout<<"���Ϸ�";
		return; 
	}
	
	else{
	int i;
	for (i=target;i<L.last;i++) {
		L.elements[i]=L.elements[i+1];	
	}
	L.last-=1;
	return;
	}
	
}
void DeleteRepeatElements(struct List& L){
	if(L.last<=0) return;

	int i,j=1;
	for(i=1;i<=L.last;i++){
		if(L.elements[i]!=L.elements[i-1]){
			L.elements[j]=L.elements[i];
			j++;
		}
		
	} 
	L.last=j-1;
}
void Reverse(struct List &L){
	if(L.last<=0 )return;

	int i;
	int j;
	for (i=0;i<(L.last+1)/2;i++){//����żʱ��1��2 
		j=L.elements[i];
		L.elements[i]=L.elements[L.last-i];
		L.elements[L.last-i]=j;
	}
}
void LeftForward(struct List& L,int k){
	if(L.last<=0||k<=0)return;
	//!����k>last����� 
	k=k%(L.last+1);
	if(k==0) return;
	//int temp[k]���� Ҫ��̬�����ڴ�;C++�е�new int[k] ���ص���ָ��int*���� Ҫ��ָ����� �������þ�̬���������� 
	int* temp=new int [k]; 
	int i;int j; 
	copy(L.elements,L.elements+k,temp);//std�е�copy������ָ�� 
	for (i=0;i<=L.last-k;i++){
		L.elements[i]=L.elements[i+k];
	}
	for(i=L.last-k+1,j=0;i<=L.last;i++,j++){
		L.elements[i]=temp[j];
	}
	delete[] temp;
}
void RightForward(struct List&L, int k){
	if(L.last<=0||k<=0)return;
	k=k%(L.last+1);
	if(k==0) return;
	int* temp=new int [k];
	int i;  
	copy(L.elements+L.last+1-k,L.elements+L.last+1,temp);
	for (i=L.last;i>=k;i--){
		L.elements[i]=L.elements[i-k];
	}
	for(i=0;i<=k-1;i++){
		L.elements[i]=temp[i];
	}
	delete[] temp;
}
void merge(struct List& L1,const struct List &L2){
	//��������Ϊ�������� ��L2����L1 �ռ临�Ӷ�С 
	if(L1.last+L2.last+2>MAX){
	cout<<"Խ����"<<endl;
	return; 
	}
	/*int i,j,k;
	struct List combineList;
	combineList.last=L1.last+L2.last+2;
	for (i=0,j=0,k=0;i<=L1.last&&j<=L2.last;k++){
		if (L1.elements[i]>=L2.elements[j]){
			combineList.elements[k]=L1.elements[i];
			i++;
		}else{
			combineList.elements[k]=L2.elements[j];
			j++;
		}
		
	}*/
	//���õ�д��: �Ӻ���ǰ����
	int i=L1.last;
	int j=L2.last;
	int k=L1.last+L2.last+1;
	L1.last=k;
	
	while(i>=0&&j>=0){
		if(L1.elements[i]>L2.elements[j]){
			L1.elements[k--]=L1.elements[i--];
		}else{
			L1.elements[k--]=L2.elements[j--];
		}
	}
	while(j>=0){
		L1.elements[k--]=L2.elements[j--];
	}
	
}
int main(){
	return 0;
}
