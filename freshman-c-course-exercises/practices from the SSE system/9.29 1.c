#include<stdio.h>
struct Day{
	int year ;
	int month;
	int date ;
}ipt_day ;
int days(struct Day ipt_day){
	int sum;
	int i;
	int day_per_month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31,};
	if((ipt_day.year % 4 == 0 && ipt_day.year % 100!= 0)||ipt_day.year % 400 == 0){
		day_per_month[3]=29;
	}
	for(i=0;i<ipt_day.month;i++){
		sum+=day_per_month[i];
	}
	sum+=ipt_day.date;
	return sum;
}
int main(){

	printf("请输入日期（年，月，日）");
	scanf("%d,%d,%d",&ipt_day.year,&ipt_day.month,&ipt_day.date);
	int sum=days(ipt_day);
	printf("\n%d月%d日是%d年的第%d天。" ,ipt_day.month,ipt_day.date,ipt_day.year,sum);
	return 0;
}

