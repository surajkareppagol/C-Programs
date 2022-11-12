/*
 *   AUTHOR : SHADOWW
 *   LAST MODIFIED : 12 / 12 / 2022
 */

//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 40

void asciiSmall();
void asciiBig();
//////////////////////////////////////////////////////////////////////////////

int indexes[MAX];
char text[MAX];
char upSmall[26][4] = {" _ ", " _ ", " __", " _ ", " __", " __", " _ ", "   ", "___", " __", "| _", "|  ", " _ ", "| |", " _ ", " _ ", " _ ", " _ ", " _ ", "___", "   ", "   ", "   ", "\\ /", "   ", "___"};
char middleSmall[26][4] = {"|_|", "|_|", "|  ", "| |", "|__", "|__", "|_ ", "|_|", " | ", "  |", "|| ", "|  ", "|||", "|\\|", "| |", "|_|", "| |", "|_|", "|_ ", " | ", "| |", "\\ /", "|||", " / ", "|_|", " / "};
char bottomSmall[26][4] = {"| |", "|_|", "|__", "|_|", "|__", "|  ", "|_|", "| |", "___", " _|", "||_", "|__", "|||", "| |", "|_|", "|  ", "|_\\", "|\\ ", " _|", " | ", "|_|", " / ", "|_|", "/ \\", " _|", "___"};

char levelOne[26][9] = {"|======|", "|====== ", "|=======", "|====== ", "|=======", "|=======", "|======|", "|      |", "========", "========", "| ======", "|       ", "|=    =|", "|===   |", "|======|", "|======|", "|======|", "|======|", "========", "========", "|      |", "\\      /", "|      |", "\\     /", "\\      /", "========"};
char levelTwo[26][9] = {"|      |", "|      |", "|       ", "|      |", "|       ", "|       ", "|      |", "|      |", "   |    ", "    |   ", "| |     ", "|       ", "| \\  / |", "|  |   |", "|      |", "|      |", "|      |", "|      |", "|       ", "   |    ", "|      |", " \\    / ", "|      |", " \\   / ", " \\    / ", "   /  / "};
char levelThree[26][9] = {"|======|", "|====== ", "|       ", "|      |", "|=======", "|=======", "|       ", "|======|", "   |    ", "    |   ", "|<      ", "|       ", "|  \\/  |", "|  |   |", "|      |", "|======|", "|    _ |", "|======|", "|=======", "   |    ", "|      |", "  \\  /  ", "|  /\\  |", "  \\ /  ", "  \\==/  ", "  /  /  "};
char levelFour[26][9] = {"|      |", "|      |", "|       ", "|      |", "|       ", "|       ", "|  ====|", "|      |", "   |    ", " |  |   ", "| |     ", "|       ", "|      |", "|  |   |", "|      |", "|       ", "|    \\|", "|\\ \\    ", "       |", "   |    ", "|      |", "   \\/   ", "| /  \\ |", "  / \\  ", "   ||   ", " /  /   "};
char levelFive[26][9] = {"|      |", "|====== ", "|=======", "|====== ", "|=======", "|       ", "|======|", "|      |", "========", " ===|   ", "| ======", "|=======", "|      |", "|  ====|", "|======|", "|       ", "|=====\\", "| \\ \\   ", "=======|", "   |    ", "|======|", "   ^^   ", "|=    =|", " /   \\ ", "   ||   ", "========"};

char alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// Main Function
int main()
{
	char choice, art;
	do
	{
		printf("\n| Small Art (s) | Big Art (b) |");
		printf("\nEnter the choice and text: ");
		scanf("%s%s", &art, text);
		if (tolower(art) == 's')
			asciiSmall();
		else if (tolower(art) == 'b')
			asciiBig();
		printf("\n\nConvert more text?(Y)es or (N)o : ");
		scanf("%s", &choice);
	} while (tolower(choice) == 'y');
	return 0;
}

// Print Ascii Text
void asciiSmall()
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
		printf("%s ", upSmall[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", middleSmall[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", bottomSmall[indexes[k]]);
	printf("\n");
}

void asciiBig()
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
		printf("%s ", levelOne[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", levelTwo[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", levelThree[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", levelFour[indexes[k]]);
	printf("\n");

	for (k = 0; k < length; k++)
		printf("%s ", levelFive[indexes[k]]);
	printf("\n");
}