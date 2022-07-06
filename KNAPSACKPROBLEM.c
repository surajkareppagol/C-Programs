/*   DO NOT EDIT THIS
 *   AUTHOR : SHADOWW
 *   LAST MODIFIED : 05 / 07 / 2022
 */

#include <stdio.h>
#define MAX 20

int i, j, n, x, indexNumber, maxCapacity;
float knapsackStat[MAX][6], totalProfit = 0, remainingCapacity, elementW, elementP, elementPW, tempElement;

void arrangePWRatio()
{
  // Find the minimum p/w ratio
  indexNumber = n;
  for (j = 0; j < n; j++)
  {
    tempElement = knapsackStat[0][2];
    x = 0;
    for (i = 1; i < indexNumber; i++)
    {
      if (tempElement > knapsackStat[i][2])
      {
        tempElement = knapsackStat[i][2];
        x = i;
      }
    }
    if (x == indexNumber - 1)
      continue;
    elementW = knapsackStat[indexNumber - 1][0];
    elementP = knapsackStat[indexNumber - 1][1];
    elementPW = knapsackStat[indexNumber - 1][2]; // SWAP TEMP = A
    knapsackStat[indexNumber - 1][0] = knapsackStat[x][0];
    knapsackStat[indexNumber - 1][1] = knapsackStat[x][1];
    knapsackStat[indexNumber - 1][2] = knapsackStat[x][2]; // SWAP A = B
    knapsackStat[x][0] = elementW;
    knapsackStat[x][1] = elementP;
    knapsackStat[x][2] = elementPW; // SWAP B = TEMP
    indexNumber -= 1;
  }
}

void displayResult(int type)
{
  if (type == 1)
  {
    printf("\nPROFIT / WEIGHT RATIO : \n\n");
    printf("-------------------------------\n");
    printf("| WEIGHT | PROFIT | P/W RATIO |\n");
    printf("-------------------------------\n");
    for (i = 0; i < n; i++)
    {
      printf("|%6.2f  | %6.2f | %6.2f    |\n", knapsackStat[i][0], knapsackStat[i][1], knapsackStat[i][2]);
      printf("-------------------------------\n");
    }
  }
  else
  {
    printf("\nSOLUTION : \n\n");
    printf("-----------------------------------------------------------\n");
    printf("| WEIGHT | PROFIT | P/W RATIO |   Xi   | TPROFIT  | Rc    |\n");
    printf("-----------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
      printf("|%6.2f  | %6.2f | %6.2f    | %6.2f | %6.2f   | %6.2f|\n", knapsackStat[i][0], knapsackStat[i][1], knapsackStat[i][2], knapsackStat[i][3], knapsackStat[i][4], knapsackStat[i][5]);
      printf("-----------------------------------------------------------\n");
    }
  }
}

int main()
{
  printf("\n\nENTER THE NUMBER OF OBJECTS AND MAX CAPACITY : ");
  scanf("%d%d", &n, &maxCapacity);
  printf("ENTER THE WEIGHTS OF THE OBJECTS : ");
  for (i = 0; i < n; i++)
    scanf("%f", &knapsackStat[i][0]); // STORE THE WEIGHTS
  printf("ENTER THE PROFITS OF THE OBJECTS : ");
  for (i = 0; i < n; i++)
    scanf("%f", &knapsackStat[i][1]); // STORE THE PROFITS
  for (i = 0; i < n; i++)             // CALCULATE P/W RATIO
    knapsackStat[i][2] = knapsackStat[i][1] / knapsackStat[i][0];
  arrangePWRatio(); // FUNCTION TO ARRANGE P/W RATIO
  displayResult(1); // DISPLAY 1
  remainingCapacity = maxCapacity;
  for (i = 0; i < n; i++)
  {
    if (knapsackStat[i][0] <= remainingCapacity)
    {
      knapsackStat[i][3] = 1;                                       // Xi
      knapsackStat[i][4] = knapsackStat[i][3] * knapsackStat[i][1]; // TPROFIT
      knapsackStat[i][5] = remainingCapacity - knapsackStat[i][0];  // Rc
      remainingCapacity = knapsackStat[i][5];
    }
    else
    {
      knapsackStat[i][3] = remainingCapacity / knapsackStat[i][0];  // Xi
      knapsackStat[i][4] = knapsackStat[i][3] * knapsackStat[i][1]; // TPROFIT
      knapsackStat[i][5] = 0;                                       // Rc
      remainingCapacity = knapsackStat[i][5];
    }
  }

  displayResult(2); // DISPLAY 2
  printf("\n\nOBJECT'S WEIGHT INCLUDED : ( ");
  for (i = 0; i < n; i++)
  {
    printf("%.2f, ", knapsackStat[i][3]);
    totalProfit += knapsackStat[i][4];
  }
  printf(")\n\n");
  printf("THE TOTAL PROFIT IS : %.2f\n\n", totalProfit);
  return 0;
}