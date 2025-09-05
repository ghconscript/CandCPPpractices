#include<stdio.h>
void BeforeDay(int *pyear, int *pmonth, int *pday);
int  IsRun(int y);
int main() {
	printf("please input the date of today:");
	int y, m, d;
	int*pyear = &y;
	int*pmonth = &m;
	int*pday = &d;


	scanf("%d-%d-%d", &y, &m, &d);
	BeforeDay(pyear, pmonth, pday);

	printf("%d-%d-%d", *pyear, *pmonth, *pday);
}
int IsRun(int y) {
	if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
		return 1;
	else
		return 0;
}
void BeforeDay(int *pyear, int *pmonth, int *pday) {
	int days[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
	if (*pday != 1)
		(*pday)--;
	else {
		if(*pmonth!=1) {

			if (IsRun(*pyear)) {
				(*pmonth)--;
				*pday = days[1][*pmonth-1];
			} else {
				(*pmonth)--;
				*pday = days[0][*pmonth-1];
			}
		} else {
			(*pyear)--;
			(*pmonth)=12;
			(*pday)=31;
		}

	}

}
