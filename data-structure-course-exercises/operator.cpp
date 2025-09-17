#include <iostream>
#include <fstream>
#include <string.h>
#define MAX 100
using namespace std;
typedef struct{
	int elements[MAX];// elemtype == char
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
	cout <<"中缀表达式"<< mid << endl;
	int i=0;
	char c=mid[i];
	while (c!='\0'){
		//对于c++风格字符串 可以不依赖/0 
		if(c>='0'&&c<='9'){
			back += c;//直接输出 
			
		}else if(c=='('){
			Push(c,stack);//左括号入栈 
			
		}else if(c==')'){
			while(stack.elements[stack.top]!='('){
				back += stack.elements[stack.top];
				Pop(stack);//不断弹出符号 直到遇到左括号 
			}
			Pop(stack);//弹出左括号  但不加入back 
			
		}else{
			while(Priority(c)<=Priority(stack.elements[stack.top])){
				back += stack.elements[stack.top];
				Pop(stack);//如果栈顶符号优先级大于等于c 将栈顶运算符弹出输出 不断比较新的运算符直到入栈   
			}
			Push(c,stack);//入栈 
		}
		i++;//遍历下一个元素 
		c=mid[i];
		
	}
		while(!Empty(stack)){
			back +=stack.elements[stack.top];
			Pop(stack);//若栈非空的话 不断弹出剩余的栈内符号 
		}
	cout<<back<<endl;
	i=0;
	int temp1,temp2,result;
	char cresult;
	c=back[i];
	
	//计算模块 
	while(i<back.size()){
		
		if(c>='0'&&c<='9'){
			Push(c,stack);//数字直接入栈 
		}else {// 符号 栈顶两个元素运算并将结果压入栈中 
			temp1=int(stack.elements[stack.top])-'0';
			Pop(stack);
			temp2=int(stack.elements[stack.top])-'0';
			Pop(stack);
			switch(c){
				case '+':
					result = temp2+temp1;
					break;
				case '-':
					result = temp2-temp1;
					break;
				case '*':
					result = temp1*temp2;
					break;
				case '/':
					result = temp2/temp1;
					break;
			}
			cresult=result+'0';
			Push(cresult,stack); 
		}
		i++;//back的下一个元素 
		c=back[i];
	}
	cout<<result<<endl;
}

