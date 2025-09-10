#include <iostream>
#define MAX 100
using namespace std;
struct List{
	int elements[MAX];// ElemType == int 
	int last;
};
void Delete(struct List& L, int target){
	int i;
	for (i=target;i<L.last;i++) {
		L.elements[i]=L.elements[i+1];	
	}
	L.last-=1;
}
void DeleteRepeatElements(struct List&L){
	int i,j=1;
	for(i=1;i<=Last;i++){
		if(L.elements[i]!=L.elements[i-1]){
			L.elements[j]=L.elements[i];
			j++;
		}
		L.last=j;
	} 
}
void Reverse(struct List &L){
	int i;
	int j;
	for (i=0;i<=L.Last/2;i++){
		j=L.elements[i];
		L.elements[i]=L.elements[L.last-i];
		L.elements[L.last-i]=j;
	}
}
void LeftForward(&List,int k);
void RightForward(&List int k);
void combine(&List);
int main(){
	
	
	
	
	return 0;
}
