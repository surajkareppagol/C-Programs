#include <stdio.h>

int main()
{
	int numberOfLines, startingNumber;
	printf("Enter the number: ");
	scanf("%d", &numberOfLines);
	startingNumber = 1;
	for (int i = 1; i <= numberOfLines; i++)
	{
		for (int j = 1; j <= i * 2; j++)
		{
			if (j % 2 == 0)
				printf(" ");
			else
			{
				printf("%d", startingNumber);
				printf("%d", i);
				startingNumber += 1;
			}
		}
		startingNumber = 1;
		printf("\n");
	}
	return 0;
}
