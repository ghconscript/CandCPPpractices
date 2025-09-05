#include<stdio.h>
#include<string.h>
char* reverse(int a,char*str,int*i){
	
	if(a/10==0){
	
	str[*i]=a+'0';
	(*i)++;
	str[*i]='\0';
	return str;}
	else{
		reverse(a/10,str,i);
		str[*i]=a%10+'0';
		(*i)++;
		return str;
		
	}
}
int main(){
	int input;
	char str[100];
	int a=0;
	int*i=&a;	
	printf("\n输入整数:");
	scanf("%d",&input);
	char*opt=reverse(input,str,i);
	printf("\n输出是:%s",opt);
	
}
