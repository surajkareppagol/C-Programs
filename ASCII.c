/*
 *  AUTHOR : SHADOWW
 *  LAST MODIFFIED : 07 / 07 / 2022
 */

//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 40

//////////////////////////////////////////////////////////////////////////////

int indexes[MAX];
char text[MAX];
char up[26][4] = {" _ ", " _ ", " __", " _ ", " __", " __", " _ ", "   ", "___", " __", "| _", "|  ", " _ ", "| |", " _ ", " _ ", " _ ", " _ ", " _ ", "___", "   ", "   ", "   ", "\\ /", "   ", "___"};
char middle[26][4] = {"|_|", "|_|", "|  ", "| |", "|__", "|__", "|_ ", "|_|", " | ", "  |", "|| ", "|  ", "|||", "|\\|", "| |", "|_|", "| |", "|_|", "|_ ", " | ", "| |", "\\ /", "|||", " / ", "|_|", " / "};
char bottom[26][4] = {"| |", "|_|", "|__", "|_|", "|__", "|  ", "|_|", "| |", "___", " _|", "||_", "|__", "|||", "| |", "|_|", "|  ", "|_\\", "|\\ ", " _|", " | ", "|_|", " / ", "|_|", "/ \\", " _|", "___"};
char alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

//////////////////////////////////////////////////////////////////////////////
void ascii()
{
	int i, j, k;
	char temp;
	int length = strlen(text);
	for (i = 0; i < length; i++)
	{
		temp = tolower(text[i]);
		for (j = 0; j < 26; j++)
			if (temp == alpha[j])
				indexes[i] = j;
	}

	for (k = 0; k < length; k++)
		printf("%s ", up[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", middle[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", bottom[indexes[k]]);
	printf("\n");
}

//////////////////////////////////////////////////////////////////////////////
int main()
{
	char choice;
	do
	{
		printf("Enter the text: ");
		scanf("%s", text);
		ascii();
		printf("\nHave more text?(Y)es or (N)o : ");
		scanf("%s", &choice);
	} while (tolower(choice) == 'y');
	return 0;
}

//////////////////////////////////////////////////////////////////////////////