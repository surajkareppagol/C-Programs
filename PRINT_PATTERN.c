#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  int n, i, j, k, startRight = 0, startRepeat = 0, detectFirst = 0, detectsecond = 0, flag = 0;
  scanf("%d", &n);

  detectFirst = 2;
  detectsecond = n * 2 - 3;

  startRepeat = n - 1;

  for (i = 0; i < n * 2 - 1; i++)
    printf("%d ", n);
  printf("\n");

  for (i = 0; i < n * 2 - 3; i++)
  {
    startRight = startRepeat;

    for (j = 0; j < n * 2 - 1; j++)
    {
      if (j == n * 2 - 2) // To print n at last
        printf("%d ", n);

      else if (j == n * 2 - 3) // To print n - 1
        printf("%d ", n - 1);

      else if (j >= detectFirst && j <= detectsecond) // To print repeat number
        printf("%d ", startRepeat);

      else if (j >= n && j < n * 2 - 2) // To print 1 2 3 4 5
      {
        startRight += 1;
        printf("%d ", startRight);
      }

      else
        printf("%d ", n - j); // To print 5 4 3 2 1
    }
    if (startRepeat == 1)
      flag = 1;
    if (!flag)
    {
      startRepeat -= 1;
      detectFirst += 1;
      detectsecond -= 1;
    }
    else
    {
      startRepeat += 1;
      detectFirst -= 1;
      detectsecond += 1;
    }
    printf("\n");
  }

  for (i = 0; i < n * 2 - 1; i++)
    printf("%d ", n);
  printf("\n");
  return 0;
}