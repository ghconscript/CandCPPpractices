#include <iostream>
#include <fstream>
#include <string.h>
#define MAX 100
using namespace std;
typedef struct{
	char elements[MAX];// elemtype == char
	int top;//顶值对应的索引 
}STACK;
void InitStack(STACK &S){
    S.top = -1;  
}
bool Empty(STACK S){
	if(S.top<0)
		return true;
	else
		return false; 
}
char Top(STACK S){
	if (Empty(S))
		return -1;
	else
	return (S.elements[S.top]);
}
void Pop(STACK &S){
	if (Empty(S)){
	cout<<"栈空"<<endl;
	return; 
	}
	else 
		S.top=S.top-1;
}
void Push(char x,STACK &S){
	if (S.top==MAX-1)
	{
		cout<<"栈满"<<endl;
		return; 
	}else{
		S.top=S.top+1;
		S.elements[S.top]=x;
		return;
	} 
} 
int Priority(char op){
	if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
int main(){
	ifstream inFile;
	inFile.open("data.txt");
	string mid,back;
	STACK stack;
	InitStack(stack);
	getline(inFile, mid);
	cout << mid << endl;
	int i=0;
	char c=mid[i];
	while (c!='\0'){
		
		if(c>='0'&&c<='9'){
			back += c;//相当于直接输出 
			
		}else if(c=='('){
			Push(c,stack);
			
		}else if(c==')'){
			while(stack.elements[stack.top]!='('){
				back += stack.elements[stack.top];
				Pop(stack);
			}
			Pop(stack);//弹出左括号 
			
		}else{
			while(Priority(c)<=Priority(stack.elements[stack.top])){
				back += stack.elements[stack.top];
				Pop(stack);
			}
			Push(c,stack);
		}
		i++;
		c=mid[i];
		
	}
		while(!Empty(stack)){
			back +=stack.elements[stack.top];
			Pop(stack);
		}
	
	cout<<back<<endl;
}

