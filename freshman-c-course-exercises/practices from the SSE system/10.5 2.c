#include <stdio.h>
#include <string.h>
void Inverse(char rstr[]);

main()
{
	char  str[80];

	printf("Input a string:\n");
	gets(str);
	Inverse(str);
	printf("The inversed string is:\n");
	puts(str);
}

void Inverse(char rstr[])
{
	int i,n;
	char temp;

	for(i=0, n=(strlen(rstr)-1); i<n; i++, n--)
	{
		temp = rstr[i];
		rstr[i] = rstr[n];
		rstr[n] = temp;
	}
}
