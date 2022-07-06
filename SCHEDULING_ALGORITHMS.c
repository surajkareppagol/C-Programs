/*
 *  AUTHOR : SHADOWW
 *  LAST MODIFFIED : 06 / 07 / 2022
 */

#include <stdio.h>
#define MAX 100

int n, choice, algoChoice, algoStat[MAX][7];

// ARRANGE BURST TIME
void arrangeBT(int iNum)
{
  int i, j, x, indexNumber = n, processNumber, arrivalTime, burstTime, tempElement;
  for (j = 0; j < n; j++)
  {
    tempElement = algoStat[0][iNum];
    x = 0;
    for (i = 1; i < indexNumber; i++)
    {
      if (tempElement < algoStat[i][iNum])
      {
        tempElement = algoStat[i][iNum];
        x = i;
      }
    }
    processNumber = algoStat[indexNumber - 1][0];
    arrivalTime = algoStat[indexNumber - 1][1];
    burstTime = algoStat[indexNumber - 1][2]; // SWAP TEMP = A
    algoStat[indexNumber - 1][0] = algoStat[x][0];
    algoStat[indexNumber - 1][1] = algoStat[x][1];
    algoStat[indexNumber - 1][2] = algoStat[x][2]; // SWAP A = B
    algoStat[x][0] = processNumber;
    algoStat[x][1] = arrivalTime;
    algoStat[x][2] = burstTime; // SWAP B = TEMP
    indexNumber -= 1;
  }
}

// DISPLAY ALL STATS
void displayStat()
{
  int i, j;
  printf("\n---------------------------------------------------------------------------------------\n");
  printf("| PID | ARRIVAL TIME | BURST TIME | COMPLETION TIME | TURN AROUND TIME | WAITING TIME |\n");
  printf("---------------------------------------------------------------------------------------\n");
  for (i = 0; i < n; i++)
  {
    printf("| P%d  | %3d          | %3d        | %3d             | %3d              | %3d          |\n", algoStat[i][0], algoStat[i][1], algoStat[i][2], algoStat[i][3], algoStat[i][4], algoStat[i][5]);
    printf("---------------------------------------------------------------------------------------\n");
  }
}

// DISPLAY GRANTT CHART
void granttChart(int Inum)
{
  int indexNumber;
  printf("\n----------------\n");
  printf("| GRANTT CHART |\n");
  printf("----------------\n\n");
  for (indexNumber = 0; indexNumber < Inum; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < Inum; indexNumber++)
    printf("| P%d | ", algoStat[indexNumber][0]);
  printf("\n");
  for (indexNumber = 0; indexNumber < Inum; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < Inum; indexNumber++)
    printf("      %d", algoStat[indexNumber][3]);
}

// FCFS ALGORITHM
void fcfsFun()
{
  int indexNumber;
  float tTAT = 0, tWT = 0;
  algoStat[0][3] = algoStat[0][1] + algoStat[0][2];
  for (indexNumber = 1; indexNumber < n; indexNumber++)
    algoStat[indexNumber][3] = algoStat[indexNumber - 1][3] + algoStat[indexNumber][2];
  for (indexNumber = 0; indexNumber < n; indexNumber++)
  {
    algoStat[indexNumber][4] = algoStat[indexNumber][3] - algoStat[indexNumber][1];
    algoStat[indexNumber][5] = algoStat[indexNumber][4] - algoStat[indexNumber][2];
  }
  for (indexNumber = 0; indexNumber < n; indexNumber++)
  {
    tTAT += algoStat[indexNumber][4];
    tWT += algoStat[indexNumber][5];
  }

  displayStat();
  printf("\n\n");
  printf("AVERAGE TURN AROUND TIME : %.2f ms\nAVERAGE WAITING TIME : %.2f ms\n", tTAT / n, tWT / n);
}

// SRTF ALGORITHM
void sjfPFun()
{
  int i, indexI, indexJ, indexNumber, indexValue, count = 0, totalBTime = 0, processExecutedFor = 0, tempElement, processNumber, flag = 1, readyQueue[MAX], processExecution[MAX], processExecutionTime[MAX], processDone[MAX];
  float tTAT = 0, tWT = 0;
  arrangeBT(1);
  for (indexI = 0; indexI < n; indexI++)
  {
    algoStat[indexI][6] = algoStat[indexI][2];
    totalBTime += algoStat[indexI][2]; // Find total Burst Time
    processDone[indexI] = -1;
  }
  for (indexI = 0; indexI < totalBTime; indexI++)
  {
    for (indexJ = 0; indexJ < n; indexJ++)
    {
      if (algoStat[indexJ][1] == indexI)
      {
        readyQueue[indexI] = algoStat[indexI][0];
        count += 1;
      }
    }
    tempElement = algoStat[0][6];
    processNumber = 0;
    for (i = 1; i < count; i++)
    {
      if (tempElement > algoStat[i][6] && algoStat[i][6] != 0)
      {
        tempElement = algoStat[i][6];
        processNumber = i;
      }
    }                                                            // Find lowest Burst time
    processExecutedFor += 1;                                     // Execute for 1 second
    processExecutionTime[indexI] = processExecutedFor;           // Put Execution Time
    processExecution[indexI] = algoStat[processNumber][0];       // Put PID
    algoStat[processNumber][6] = algoStat[processNumber][6] - 1; // Decrement BT
  }

  indexValue = 0;
  for (indexI = totalBTime - 1; indexI >= 0; indexI--)
  {
    for (i = 0; i < indexValue; i++)
    {
      if (processExecution[indexI] == processDone[i])
        flag = 0;
    }
    if (flag)
    {
      for (indexJ = 0; indexJ < n; indexJ++)
      {
        if (processExecution[indexI] == algoStat[indexJ][0])
          processNumber = indexJ;
      }
      algoStat[processNumber][3] = processExecutionTime[indexI];
      processDone[indexValue] = processExecution[indexI];
      indexValue += 1;
    }
    flag = 1;
  }

  // GRANTT CHART

  printf("\n----------------\n");
  printf("| GRANTT CHART |\n");
  printf("----------------\n\n");
  for (indexNumber = 0; indexNumber < totalBTime; indexNumber++)
    printf("---- ");
  printf("\n");
  for (indexNumber = 0; indexNumber < totalBTime; indexNumber++)
    printf("|P%d| ", processExecution[indexNumber]);
  printf("\n");
  for (indexNumber = 0; indexNumber < totalBTime; indexNumber++)
    printf("---- ");
  printf("\n");
  for (indexNumber = 0; indexNumber < totalBTime; indexNumber++)
    printf("  %d", processExecutionTime[indexNumber]);

  // CALCULATIONS
  for (indexNumber = 0; indexNumber < n; indexNumber++)
  {
    algoStat[indexNumber][4] = algoStat[indexNumber][3] - algoStat[indexNumber][1];
    algoStat[indexNumber][5] = algoStat[indexNumber][4] - algoStat[indexNumber][2];
  }
  for (indexNumber = 0; indexNumber < n; indexNumber++)
  {
    tTAT += algoStat[indexNumber][4];
    tWT += algoStat[indexNumber][5];
  }

  // DISPLAY STAT
  displayStat();

  printf("\n\n");
  printf("AVERAGE TURN AROUND TIME : %.2f ms\nAVERAGE WAITING TIME : %.2f ms\n", tTAT / n, tWT / n);
}

int main()
{
  int i;
  printf("------------------\n");
  printf("| 1.FCFS | 2.SJF |\n");
  printf("------------------\n");
  printf("CHOOSE THE ALGORITHM : ");
  scanf("%d", &choice);
  printf("ENTER THE NUMBER OF PROCESS : ");
  scanf("%d", &n);
  printf("ENTER THE PROCESS NUMBERS: ");
  for (i = 0; i < n; i++)
    scanf("%d", &algoStat[i][0]);
  printf("ENTER THE ARRIVAL TIMES: ");
  for (i = 0; i < n; i++)
    scanf("%d", &algoStat[i][1]);
  printf("ENTER THE BURST TIMES: ");
  for (i = 0; i < n; i++)
    scanf("%d", &algoStat[i][2]);
  if (choice == 1)
    fcfsFun();
  else if (choice == 2)
  {
    printf("\n-----------------------------------\n");
    printf("| 1.NON-PREEMPTIVE | 2.PREEMPTIVE |\n");
    printf("-----------------------------------\n");
    printf("CHOICE : ");
    scanf("%d", &algoChoice);
    if (algoChoice == 1)
    {
      arrangeBT(2);
      granttChart(n);
      fcfsFun();
    }
    else if (algoChoice == 2)
      sjfPFun();
  }
  else
    printf("INVLID CHOICE.\n");
  return 0;
}