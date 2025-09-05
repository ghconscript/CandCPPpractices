#include<stdio.h>
int main() {
	int i;

	for(i=1000; i<10000; i++) {
		int firstDigit = number / 1000;
		int secondDigit = (number / 100) % 10;
		int thirdDigit = (number / 10) % 10;
		int fourthDigit = number % 10;

		if (firstDigit == secondDigit && thirdDigit == fourthDigit && firstDigit!= thirdDigit) {
			double root = sqrt(number);
			if (root == (int)root) {
				printf("Lorry_No. is %d.\n", number);
				return 0;
			}
		}


	}
