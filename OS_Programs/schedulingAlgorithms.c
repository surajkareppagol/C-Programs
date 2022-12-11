/*
 *  AUTHOR : SHADOWW
 *  LAST MODIFFIED : 14 / 07 / 2022
 */

//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#define MAX 100

//////////////////////////////////////////////////////////////////////////////

int numberOfProcesses, choice, type, timeQuantum, algorithmStat[MAX][10];
float aTurnAroundTime = 0, aWaitingTime = 0;

//////////////////////////////////////////////////////////////////////////////

void arrangeStat(int);
void displayStat();
void granttChart(int);
void fcfsAlgorithm();
void srtfAlgorithm();
void priorityNPAlgorithm();
void priorityPAlgorithm();
int findIndex(int);
int checkBurstTime();
int isProcessExecuted(int processSent[numberOfProcesses], int);
void roundRobinAlgorithm();

//////////////////////////////////////////////////////////////////////////////

int main()
{
  int indexNumber;
  printf("----------------------------------------------\n");
  printf("| 1.FCFS | 2.SJF | 3.PRORITY | 4.ROUND-ROBIN |\n");
  printf("----------------------------------------------\n");
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
  else if (choice == 3)
  {
    printf("ENTER THE PRORITY ORDER : ");
    for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
      scanf("%d", &algorithmStat[indexNumber][7]); // PRIORITY ORDER
    printf("\n-----------------------------------\n");
    printf("| 1.NON-PREEMPTIVE | 2.PREEMPTIVE |\n");
    printf("-----------------------------------\n");
    printf("CHOICE : ");
    scanf("%d", &type);
    if (type == 1)
      priorityNPAlgorithm();
    else
      priorityPAlgorithm();
  }
  else if (choice == 4)
  {
    printf("ENTER THE TIME QUANTUM : ");
    scanf("%d", &timeQuantum);
    roundRobinAlgorithm();
  }
  else
    printf("INVALID CHOICE.\n");
  return 0;
}

//////////////////////////////////////////////////////////////////////////////

// ARRANGE STATS IN INCREASING ORDER
void arrangeStat(int indexValue)
{
  int indexI, indexJ, numberOfIndex, indexNumber = numberOfProcesses, processNumber, arrivalTime, burstTime, prorityOrder, tempElement;
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
    if (choice == 3)
      prorityOrder = algorithmStat[indexNumber - 1][7];
    processNumber = algorithmStat[indexNumber - 1][0];
    arrivalTime = algorithmStat[indexNumber - 1][1];
    burstTime = algorithmStat[indexNumber - 1][2]; // SWAP TEMP = A
    if (choice == 3)
      algorithmStat[indexNumber - 1][7] = algorithmStat[numberOfIndex][7];
    algorithmStat[indexNumber - 1][0] = algorithmStat[numberOfIndex][0];
    algorithmStat[indexNumber - 1][1] = algorithmStat[numberOfIndex][1];
    algorithmStat[indexNumber - 1][2] = algorithmStat[numberOfIndex][2]; // SWAP A = B
    if (choice == 3)
      algorithmStat[numberOfIndex][7] = prorityOrder;
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
  printf("\n\n---------------------------------------------------------------------------------------\n");
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
  int i, indexI, indexJ, indexNumber, indexValue, count = 0, totalBTime = 0, processExecutedFor = 0, tempElement, processNumber, flag = 1, processOnChart = -1;
  int processExecution[MAX], processExecutionTime[MAX], processDone[MAX], processForChart[MAX], chartTime[MAX];

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

    for (indexValue = 0; indexValue < count; indexValue++)
    {
      if (algorithmStat[indexValue][6] > 0)
      {
        tempElement = algorithmStat[indexValue][6];
        processNumber = indexValue;
        break;
      }
    }
    for (i = 1; i < count; i++)
    {
      if (tempElement > algorithmStat[i][6] && !(algorithmStat[i][6] < 1))
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

  indexValue = 0;
  for (indexNumber = totalBTime - 1; indexNumber >= 0; indexNumber--)
    if (processExecution[indexNumber] != processOnChart)
    {
      processOnChart = processExecution[indexNumber];
      processForChart[indexValue] = processExecution[indexNumber];
      chartTime[indexValue] = processExecutionTime[indexNumber];
      indexValue += 1;
    }

  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("| P%d | ", processForChart[indexNumber]);
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("      %d", chartTime[indexNumber]);

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

// PRORITY NON-PREEMPTIVE
void priorityNPAlgorithm()
{
  int i, indexI, indexJ, indexNumber, indexValue = 0, count = 0, processExecutedFor = 0, processNumber, tempProcess = -1, tempElement;
  int processExecution[MAX];
  arrangeStat(1);

  for (indexI = 0; indexI < numberOfProcesses; indexI++)
    algorithmStat[indexI][6] = algorithmStat[indexI][2]; // COPY BURST TIME

  for (indexI = 0; indexI < numberOfProcesses; indexI++)
  {
    if (processExecutedFor > algorithmStat[numberOfProcesses - 1][2])
      count = numberOfProcesses; // IF ALL PROCESSES ALREADY ARRIVED
    else if (algorithmStat[indexValue][1] != tempProcess)
    {
      tempProcess = algorithmStat[indexValue][1];
      for (indexJ = 0; indexJ < numberOfProcesses; indexJ++)
        if (algorithmStat[indexJ][1] == tempProcess) // CHECK HOW MANY PROCESSES ARRIVED
          count += 1;
    }

    for (indexNumber = 0; indexNumber < count; indexNumber++) // FIND HIGHEST PRORITY
    {
      if (algorithmStat[indexNumber][7] > -1)
      {
        tempElement = algorithmStat[indexNumber][7];
        processNumber = indexNumber;
        break;
      }
    }
    for (i = 1; i < count; i++)
    {
      if (tempElement > algorithmStat[i][7] && algorithmStat[i][7] > -1)
      {
        tempElement = algorithmStat[i][7];
        processNumber = i;
      }
    }                                                           // FIND HIGHEST PRIORITY
    processExecutedFor += algorithmStat[processNumber][6];      // EXECUTE
    algorithmStat[indexI][3] = processExecutedFor;              // COMPLETION TIME
    processExecution[indexI] = algorithmStat[processNumber][0]; // PUT PID
    algorithmStat[processNumber][6] = 0;                        // BURST TIME = 0
    algorithmStat[processNumber][7] = -1;                       // PRIORITY = -1
    indexValue += 1;
  }

  printf("\n----------------\n"); // GRANTT CHART
  printf("| GRANTT CHART |\n");
  printf("----------------\n\n");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    printf("| P%d | ", processExecution[indexNumber]);
  printf("\n");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    printf("------ ");
  printf("\n");
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    printf("      %d", algorithmStat[indexNumber][3]);

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

// PRORITY PREEMPTIVE
void priorityPAlgorithm()
{
  int i, indexI, indexJ, indexNumber, indexValue, count = 0, totalBTime = 0, processExecutedFor = 0, tempElement, processNumber, flag = 1, processOnChart = -1;
  int processExecution[MAX], processExecutionTime[MAX], processDone[MAX], processForChart[MAX], chartTime[MAX];

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

    for (indexNumber = 0; indexNumber < count; indexNumber++) // FIND HIGHEST PRORITY
    {
      if (algorithmStat[indexNumber][7] > -1)
      {
        tempElement = algorithmStat[indexNumber][7];
        processNumber = indexNumber;
        break;
      }
    }
    for (i = 1; i < count; i++)
    {
      if (tempElement > algorithmStat[i][7] && algorithmStat[i][7] > -1)
      {
        tempElement = algorithmStat[i][7];
        processNumber = i;
      }
    }                                                                      // FIND LOWEST BURST TIME
    processExecutedFor += 1;                                               // EXECUTE FOR 1 ms
    processExecutionTime[indexI] = processExecutedFor;                     // PUT EXECUTION TIME
    processExecution[indexI] = algorithmStat[processNumber][0];            // PUT PID
    algorithmStat[processNumber][6] = algorithmStat[processNumber][6] - 1; // DECREMENT BT
    if (algorithmStat[processNumber][6] == 0)
      algorithmStat[processNumber][7] = -1;
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

  indexValue = 0;
  for (indexNumber = totalBTime - 1; indexNumber >= 0; indexNumber--)
    if (processExecution[indexNumber] != processOnChart)
    {
      processOnChart = processExecution[indexNumber];
      processForChart[indexValue] = processExecution[indexNumber];
      chartTime[indexValue] = processExecutionTime[indexNumber];
      indexValue += 1;
    }

  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("| P%d | ", processForChart[indexNumber]);
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("      %d", chartTime[indexNumber]);

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

// FIND INDEX
int findIndex(int processNumber)
{
  int indexNumber;
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    if (processNumber == algorithmStat[indexNumber][0])
      return indexNumber;
  return -1;
}

//////////////////////////////////////////////////////////////////////////////

// CHECK BURST TIME
int checkBurstTime()
{
  int indexNumber;
  for (indexNumber = 0; indexNumber < numberOfProcesses; indexNumber++)
    if (algorithmStat[indexNumber][6] != 0)
      return 1;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////

//  CHECK IF PROCESS IS ALREADY IN PROCESSSENT[MAX]
int isProcessExecuted(int processSent[numberOfProcesses], int indexJ)
{
  if (processSent[indexJ] != algorithmStat[indexJ][0])
    return 1;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
// PRORITY PREEMPTIVE
void roundRobinAlgorithm()
{
  int i, indexI = 0, indexJ, indexNumber, indexValue, count = 0, processExecutedFor = 0, indexOfProcess, rqIncrementer = 0, flag = 0, trackProcess = 0, totalProcesses, processOnChart = -1, tempElement, processNumber;
  int processExecution[MAX], processExecutionTime[MAX], readyQueue[MAX], processSent[numberOfProcesses], chartTime[MAX], processDone[MAX], processForChart[MAX];
  arrangeStat(1); // ARRANGE THE ARRIVAL TIMES IN INCREASING ORDER

  for (indexJ = 0; indexJ < numberOfProcesses; indexJ++)
  {
    algorithmStat[indexJ][6] = algorithmStat[indexJ][2];
    processSent[indexJ] = -1;
    processDone[indexJ] = -1;
    if (algorithmStat[indexJ][1] == indexI) // CHECK HOW MANY PROCESSES ARRIVED
      count += 1;
  }

  for (indexNumber = 0; indexNumber < count; indexNumber++)
  {
    readyQueue[rqIncrementer] = algorithmStat[indexNumber][0];
    processSent[trackProcess] = algorithmStat[indexNumber][0];
    rqIncrementer += 1;
    trackProcess += 1;
  }

  while (checkBurstTime())
  {
    indexOfProcess = findIndex(readyQueue[indexI]);
    if (algorithmStat[indexOfProcess][6] >= timeQuantum)
    {
      processExecutedFor += timeQuantum;                                                 // EXECUTE FOR 1 ms
      processExecutionTime[indexI] = processExecutedFor;                                 // PUT EXECUTION TIME
      processExecution[indexI] = algorithmStat[indexOfProcess][0];                       // PUT PID
      algorithmStat[indexOfProcess][6] = algorithmStat[indexOfProcess][6] - timeQuantum; // DECREMENT BT

      // CHECK IF NEW PROCESS HAVE BEEN ARRIVED
      if (trackProcess < numberOfProcesses)
      {
        for (i = 1; i < numberOfProcesses; i++)
          if (processSent[i] != algorithmStat[i][0])
            flag = 1;

        if (flag)
        {
          for (indexJ = 1; indexJ <= processExecutedFor; indexJ++)
          {
            if (isProcessExecuted(processSent, indexJ) && indexJ < algorithmStat[numberOfProcesses - 1][1])
            {
              readyQueue[rqIncrementer] = algorithmStat[indexJ][0];
              processSent[trackProcess] = algorithmStat[indexJ][0];
              rqIncrementer += 1;
              trackProcess += 1;
            }
          }
        }
      }
      flag = 0;

      if (algorithmStat[indexOfProcess][6] != 0)
      {
        readyQueue[rqIncrementer] = algorithmStat[indexOfProcess][0];
        rqIncrementer += 1;
      }
    }
    else
    {
      processExecutedFor += algorithmStat[indexOfProcess][6];
      processExecutionTime[indexI] = processExecutedFor;           // PUT EXECUTION TIME
      processExecution[indexI] = algorithmStat[indexOfProcess][0]; // PUT PID
      algorithmStat[indexOfProcess][6] = 0;
    }
    indexI += 1;
  }

  totalProcesses = indexI;
  indexValue = 0; // CALCULATE THE COMPLETION TIME
  for (indexI = totalProcesses; indexI >= 0; indexI--)
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

  indexValue = 0;
  for (indexNumber = totalProcesses - 1; indexNumber >= 0; indexNumber--)
    if (processExecution[indexNumber] != processOnChart)
    {
      processOnChart = processExecution[indexNumber];
      processForChart[indexValue] = processExecution[indexNumber];
      chartTime[indexValue] = processExecutionTime[indexNumber];
      indexValue += 1;
    }

  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("| P%d | ", processForChart[indexNumber]);
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("------ ");
  printf("\n");
  for (indexNumber = indexValue - 1; indexNumber >= 0; indexNumber--)
    printf("      %d", chartTime[indexNumber]);

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