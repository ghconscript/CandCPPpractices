#include <iostream>
#include <fstream>
#include <string>
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
int Top(STACK S){
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
void Push(int x,STACK &S){
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
	string mid,back,numStr;
	STACK stack;
	InitStack(stack);
	getline(inFile, mid);
	cout <<"中缀表达式"<< mid << endl;
	int i=0;
	char c;
	for (int i = 0; i < mid.size(); i++){//MID -> BACK
		//对于c++风格字符串 可以不依赖/0 用.sizeof()
		c=mid[i];
		if(c==' ')continue; 
		if(isdigit(c)){//c++风格字符串))
			numStr.clear(); 
            while (i < mid.size() && isdigit(mid[i])){  // 读取连续数字
                numStr += mid[i];
                i++;
            }
            back += numStr + " ";  // 加空格，区分多位数
            i--;  //要考虑到 多位数!!! 
			
		}else if(c=='('){
			Push(c,stack);//左括号入栈 
			
		}else if(c==')'){
			while(!Empty(stack)&&stack.elements[stack.top]!='('){
				back += char(Top(stack));
				back+=' ';
				Pop(stack);//不断弹出符号 直到遇到左括号 
			}
			Pop(stack);//弹出左括号  但不加入back 
			
		}else{
			while(!Empty(stack)&&Priority(c)<=Priority(stack.elements[stack.top])){
				back += char(Top(stack));
				back += ' ';
				Pop(stack);//如果栈顶符号优先级大于等于c 将栈顶运算符弹出输出 不断比较新的运算符直到入栈   
			}
			Push(c,stack);//入栈 
		}
		
	}
		
		
		while(!Empty(stack)){
			back += char(Top(stack));
			back +=' ';
			Pop(stack);//若栈非空的话 不断弹出剩余的栈内符号 
		}
	cout<<back<<endl;
	
	
	
	
	
	
	InitStack(stack);  // 重置栈用于计算
    i = 0;
    while (i < back.size()) {
        char c = back[i];
        
        if (c == ' ') {  // 跳过空格
            i++;
            continue;
        }
        
        if (isdigit(c)) {  // 处理数字
            int num = 0;
            while (i < back.size() && isdigit(back[i])) {
                num = num * 10 + (back[i] - '0');
                i++;
            }
            Push(num, stack);
        }
        else {  // 处理运算符
            // 确保栈中有足够的操作数
            if (stack.top < 1) {
                cout << "表达式错误：操作数不足！" << endl;
                return 1;
            }
            
            int right_operand = Top(stack);  // 修改4：更清晰的变量名
            Pop(stack);
            int left_operand = Top(stack);   // 修改4：更清晰的变量名
            Pop(stack);
            int result = 0;
            
            switch(c) {
                case '+':
                    result = left_operand + right_operand;
                    break;
                case '-':
                    result = left_operand - right_operand;
                    break;
                case '*':
                    result = left_operand * right_operand;
                    break;
                case '/':
                    if (right_operand == 0) {  // 修改5：添加除零检查
                        cout << "错误：除数不能为零！" << endl;
                        return 1;
                    }
                    result = left_operand / right_operand;
                    break;
                default:
                    cout << "错误：未知运算符 " << c << endl;
                    return 1;
            }
            
            Push(result, stack);  // 修改6：直接压入计算结果，不转换为字符
            i++;
        }
    }
    
    // 输出最终结果
    if (!Empty(stack) && stack.top == 0) {  // 确保栈中只有一个结果
        int finalResult = Top(stack);
        cout << "计算结果：" << finalResult << endl;
    }
    else {
        cout << "计算错误：结果异常！" << endl;
    }
    
	/*计算模块 
	while(i<back.size()){
		if(c==' ') continue;
		if(isdigit(c)){
			int num = 0;
            while (i <back.size() && isdigit(back[i])){  // 读取连续数字字符
                num = num * 10 + (back[i] - '0');  // 拼接成整数（如'1''2'→12）
                i++;
			}
			Push(num,stack);
			i--;//数字直接入栈 
		}else {// 符号 栈顶两个元素运算并将结果压入栈中 
			temp1=Top(stack);
			Pop(stack);
			temp2=Top(stack);
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
		
			Push(result,stack); 
		}
		i++;//back的下一个元素 
		c=back[i];
	}
	int finalResult = Top(stack);
	cout << "计算结果：" << finalResult << endl;*/
	
	
	
	return 0; 
}

