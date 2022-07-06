/*
 *  AUTHOR : SHADOWW
 *  LAST MODIFFIED : 06 / 07 / 2022
 */

//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#define MAX 100

//////////////////////////////////////////////////////////////////////////////

int numberOfProcesses, choice, type, algorithmStat[MAX][7];
float aTurnAroundTime = 0, aWaitingTime = 0;

//////////////////////////////////////////////////////////////////////////////

// ARRANGE STATS IN INCREASING ORDER
void arrangeStat(int indexValue)
{
  int indexI, indexJ, numberOfIndex, indexNumber = numberOfProcesses, processNumber, arrivalTime, burstTime, tempElement;
  for (indexI = 0; indexI < numberOfProcesses; indexI++)
  {
    tempElement = algorithmStat[0][indexValue];
    numberOfIndex = 0;
    for (indexJ = 1; indexJ < indexNumber; indexJ++)
      if (tempElement < algorithmStat[indexJ][indexValue])
      {
        tempElement = algorithmStat[indexJ][indexValue];
        numberOfIndex = indexJ;
      }
    processNumber = algorithmStat[indexNumber - 1][0];
    arrivalTime = algorithmStat[indexNumber - 1][1];
    burstTime = algorithmStat[indexNumber - 1][2]; // SWAP TEMP = A
    algorithmStat[indexNumber - 1][0] = algorithmStat[numberOfIndex][0];
    algorithmStat[indexNumber - 1][1] = algorithmStat[numberOfIndex][1];
    algorithmStat[indexNumber - 1][2] = algorithmStat[numberOfIndex][2]; // SWAP A = B
    algorithmStat[numberOfIndex][0] = processNumber;
    algorithmStat[numberOfIndex][1] = arrivalTime;
    algorithmStat[numberOfIndex][2] = burstTime; // SWAP B = TEMP
    indexNumber -= 1;
  }
}

//////////////////////////////////////////////////////////////////////////////

// DISPLAY ALL STATS
void displayStat()
{
  int indexI;
  printf("\n---------------------------------------------------------------------------------------\n");
  printf("| PID | ARRIVAL TIME | BURST TIME | COMPLETION TIME | TURN AROUND TIME | WAITING TIME |\n");
  printf("---------------------------------------------------------------------------------------\n");
  for (indexI = 0; indexI < numberOfProcesses; indexI++)
  {
    printf("| P%d  | %3d          | %3d        | %3d             | %3d              | %3d          |\n", algorithmStat[indexI][0], algorithmStat[indexI][1], algorithmStat[indexI][2], algorithmStat[indexI][3], algorithmStat[indexI][4], algorithmStat[indexI][5]);
    printf("---------------------------------------------------------------------------------------\n");
  }
}

//////////////////////////////////////////////////////////////////////////////

// DISPLAY GRANTT CHART FOR FCFS AND SJF(NP)
void granttChart(int indexValue)
{
  int indexNumber;
  printf("\n----------------\n");
  printf("| GRANTT CHART |\n");
  printf("----------------\n\n");
  for (indexNumber = 0; indexNumber < indexValue; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < indexValue; indexNumber++)
    printf("| P%d | ", algorithmStat[indexNumber][0]);
  printf("\n");
  for (indexNumber = 0; indexNumber < indexValue; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < indexValue; indexNumber++)
    printf("      %d", algorithmStat[indexNumber][3]);
}

//////////////////////////////////////////////////////////////////////////////

// FCFS ALGORITHM + CALCULATION FOR SJF(NP)
void fcfsAlgorithm()
{
  int indexNumber;
  algorithmStat[0][3] = algorithmStat[0][1] + algorithmStat[0][2];
  for (indexNumber = 1; indexNumber < numberOfProcesses; indexNumber++)
    algorithmStat[indexNumber][3] = algorithmStat[indexNumber - 1][3] + algorithmStat[indexNumber][2];
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
  {
    algorithmStat[indexNumber][4] = algorithmStat[indexNumber][3] - algorithmStat[indexNumber][1];
    algorithmStat[indexNumber][5] = algorithmStat[indexNumber][4] - algorithmStat[indexNumber][2];
  }
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
  {
    aTurnAroundTime += algorithmStat[indexNumber][4];
    aWaitingTime += algorithmStat[indexNumber][5];
  }

  granttChart(numberOfProcesses); // GRANTT CHART
  displayStat();                  // DISPLAY STAT
  printf("\n\n");
  printf("AVERAGE TURN AROUND TIME : %.2f ms\nAVERAGE WAITING TIME : %.2f ms\n", aTurnAroundTime / numberOfProcesses, aWaitingTime / numberOfProcesses);
}

//////////////////////////////////////////////////////////////////////////////

// SRTF ALGORITHM
void srtfAlgorithm()
{
  int i, indexI, indexJ, indexNumber, indexValue, count = 0, totalBTime = 0, processExecutedFor = 0, tempElement, processNumber, flag = 1;
  int processExecution[MAX], processExecutionTime[MAX], processDone[MAX];

  arrangeStat(1); // ARRANGE THE ARRIVAL TIMES IN INCREASING ORDER
  for (indexI = 0; indexI < numberOfProcesses; indexI++)
  {
    algorithmStat[indexI][6] = algorithmStat[indexI][2]; // COPY BURST TIME
    totalBTime += algorithmStat[indexI][2];              // FIND TOTAL BURST TIME
    processDone[indexI] = -1;
  }
  for (indexI = 0; indexI < totalBTime; indexI++)
  {
    for (indexJ = 0; indexJ < numberOfProcesses; indexJ++)
    {
      if (algorithmStat[indexJ][1] == indexI) // CHECK HOW MANY PROCESSES ARRIVED
        count += 1;
    }
    tempElement = algorithmStat[0][6];
    processNumber = 0;
    for (i = 1; i < count; i++)
    {
      if (tempElement > algorithmStat[i][6] && algorithmStat[i][6] != 0)
      {
        tempElement = algorithmStat[i][6];
        processNumber = i;
      }
    }                                                                      // FIND LOWEST BURST TIME
    processExecutedFor += 1;                                               // EXECUTE FOR 1 ms
    processExecutionTime[indexI] = processExecutedFor;                     // PUT EXECUTION TIME
    processExecution[indexI] = algorithmStat[processNumber][0];            // PUT PID
    algorithmStat[processNumber][6] = algorithmStat[processNumber][6] - 1; // DECREMENT BT
  }

  indexValue = 0; // CALCULATE THE COMPLETION TIME
  for (indexI = totalBTime - 1; indexI >= 0; indexI--)
  {
    for (i = 0; i < indexValue; i++)
    {
      if (processExecution[indexI] == processDone[i])
        flag = 0;
    }
    if (flag)
    {
      for (indexJ = 0; indexJ < numberOfProcesses; indexJ++)
      {
        if (processExecution[indexI] == algorithmStat[indexJ][0])
          processNumber = indexJ;
      }
      algorithmStat[processNumber][3] = processExecutionTime[indexI];
      processDone[indexValue] = processExecution[indexI];
      indexValue += 1;
    }
    flag = 1;
  }

  printf("\n----------------\n"); // GRANTT CHART
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

  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++) // CALCULATIONS
  {
    algorithmStat[indexNumber][4] = algorithmStat[indexNumber][3] - algorithmStat[indexNumber][1];
    algorithmStat[indexNumber][5] = algorithmStat[indexNumber][4] - algorithmStat[indexNumber][2];
  }
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
  {
    aTurnAroundTime += algorithmStat[indexNumber][4];
    aWaitingTime += algorithmStat[indexNumber][5];
  }
  displayStat(); // DISPLAY STAT
  printf("\n\n");
  printf("AVERAGE TURN AROUND TIME : %.2f ms\nAVERAGE WAITING TIME : %.2f ms\n", aTurnAroundTime / numberOfProcesses, aWaitingTime / numberOfProcesses);
}

//////////////////////////////////////////////////////////////////////////////

int main()
{
  int indexNumber;
  printf("------------------\n");
  printf("| 1.FCFS | 2.SJF |\n");
  printf("------------------\n");
  printf("CHOOSE THE ALGORITHM : ");
  scanf("%d", &choice);
  printf("ENTER THE NUMBER OF PROCESS : ");
  scanf("%d", &numberOfProcesses); // NUMBER OF PROCESSES
  printf("ENTER THE PROCESS NUMBERS: ");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    scanf("%d", &algorithmStat[indexNumber][0]); // PROCESS NUMBERS
  printf("ENTER THE ARRIVAL TIMES: ");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    scanf("%d", &algorithmStat[indexNumber][1]); // ARRIVAL TIMES
  printf("ENTER THE BURST TIMES: ");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    scanf("%d", &algorithmStat[indexNumber][2]); // BURST TIMES
  if (choice == 1)
    fcfsAlgorithm();
  else if (choice == 2)
  {
    printf("\n-----------------------------------\n");
    printf("| 1.NON-PREEMPTIVE | 2.PREEMPTIVE |\n");
    printf("-----------------------------------\n");
    printf("CHOICE : ");
    scanf("%d", &type);
    if (type == 1)
    {
      arrangeStat(2);
      fcfsAlgorithm();
    }
    else if (type == 2)
      srtfAlgorithm();
  }
  else
    printf("INVALID CHOICE.\n");
  return 0;
}

//////////////////////////////////////////////////////////////////////////////