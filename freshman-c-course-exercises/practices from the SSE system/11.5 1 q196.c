#include<stdio.h>
#include<string.h>
void Inverse(char str[]){
    int i,j;
    int len=strlen(str);	
    for(i=0,j= len - 1;i<j;i++,j--){
        char temp;
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
    }
}
int main(){
    char str[80];
    printf("Input a string:\n");
    gets(str);
    Inverse(str);
    printf("Inversed results:\n");
    printf("%s\n",str);
    return 0;
}
