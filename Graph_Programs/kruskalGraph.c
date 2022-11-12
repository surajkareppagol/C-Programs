/*
 *   AUTHOR : SHADOWW
 *   LAST MODIFIED : 12 / 12 / 2022
 */

//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#define MAX 20

int graph[MAX][MAX], graphData[MAX][3], edgeCheckList[MAX];
int numberOfVertices = 0, minimalCost = 0, numberOfEdgesInGraph = 0, numberOfEdgesInMSGraph = 0, edgeChecker = 0;
char edgesInMSGraph[MAX][4];

void sortGraph();
int isNotCyclic(char, char);
int isEdgeAlreadyUsed(int *);

int main()
{
  int indexI, indexJ, indexNumber = 0, indexValue;

  // Ask user for Number of vertices
  printf("ENTER THE NUMBER OF VERTICES : ");
  scanf("%d", &numberOfVertices);

  // Ask user to enter the data in matrix form
  printf("ENTER THE GRAPH DATA IN MATRIX FORM :\n");
  for (indexI = 0; indexI < numberOfVertices; indexI++)
    for (indexJ = 0; indexJ < numberOfVertices; indexJ++)
      scanf("%d", &graph[indexI][indexJ]);

  // Call Sort graph
  sortGraph();

  for (indexI = 0; indexI < numberOfEdgesInGraph; indexI++)
  {
    if (isNotCyclic(graphData[indexI][0], graphData[indexI][1]))
    {
      edgesInMSGraph[indexNumber][0] = toascii(65 + graphData[indexI][0]);
      edgesInMSGraph[indexNumber][1] = toascii(65 + graphData[indexI][1]);
      indexNumber += 1;
      numberOfEdgesInMSGraph += 1;
      minimalCost += graphData[indexI][2];
    }
  }

  printf("THE EDGES INCLUDED IN MINIMUM SPANNING GRAPH ARE : ");
  for (indexValue = 0; indexValue < indexNumber; indexValue++)
    printf("%s, ", edgesInMSGraph[indexValue]);
  printf("\nTHE MINIMUM COST IS %d.\n", minimalCost);
  return 0;
}

void sortGraph()
{
  int indexI, indexJ, indexNumber = 0, tempElement, numberOfIndex, graphIndexI, graphIndexJ, graphWeight;
  for (indexI = 0; indexI < numberOfVertices; indexI++)
    for (indexJ = 0; indexJ < numberOfVertices; indexJ++)
      if (graph[indexI][indexJ] != 0)
      {
        graphData[indexNumber][0] = indexI;
        graphData[indexNumber][1] = indexJ;
        graphData[indexNumber][2] = graph[indexI][indexJ];
        indexNumber++;
        numberOfEdgesInGraph++;
      }

  // SORT THE EDGES
  for (indexI = 0; indexI < numberOfEdgesInGraph; indexI++)
  {
    tempElement = graphData[0][2];
    numberOfIndex = 0;
    for (indexJ = 1; indexJ < indexNumber; indexJ++)
      if (tempElement < graphData[indexJ][2])
      {
        tempElement = graphData[indexJ][2];
        numberOfIndex = indexJ;
      }
    graphIndexI = graphData[indexNumber - 1][0];
    graphIndexJ = graphData[indexNumber - 1][1];
    graphWeight = graphData[indexNumber - 1][2]; // SWAP TEMP = A

    graphData[indexNumber - 1][0] = graphData[numberOfIndex][0];
    graphData[indexNumber - 1][1] = graphData[numberOfIndex][1];
    graphData[indexNumber - 1][2] = graphData[numberOfIndex][2]; // SWAP A = B

    graphData[numberOfIndex][0] = graphIndexI;
    graphData[numberOfIndex][1] = graphIndexJ;
    graphData[numberOfIndex][2] = graphWeight; // SWAP B = TEMP
    indexNumber -= 1;
  }
  printf("THE EDGES ARE : ");
  for (indexI = 0; indexI < numberOfEdgesInGraph; indexI++)
    printf("%c%c, ", toascii(graphData[indexI][0] + 65), toascii(graphData[indexI][1] + 65));
  printf("\n");
}

int isEdgeAlreadyUsed(int *indexNumberOfEdge)
{
  int indexI;
  for (indexI = 0; indexI < edgeChecker; indexI++)
    if (edgeCheckList[indexI] == *indexNumberOfEdge)
      return 0;
  return 1;
}

int isNotCyclic(char verticeOne, char verticeTwo)
{
  int indexI = 0, indexJ = 0, indexNumber = 0, indexValue = 0, runFor = 0, flagOne = 0, flagTwo = 0;
  char beginVertice, endVertice, firstVertice, secondVertice;

  ///////////////////////////////////////////////////////
  beginVertice = toascii(verticeOne + 65);
  endVertice = 0;

  firstVertice = toascii(verticeOne + 65);
  secondVertice = toascii(verticeTwo + 65);

  for (indexI = 0; indexI < MAX; indexI++)
    edgeCheckList[indexI] = -1;

  edgeChecker = 0;
  runFor = numberOfEdgesInMSGraph;

  if (numberOfEdgesInMSGraph > 0)
  {
    for (indexI = 0; indexI < runFor; indexI++)
    {

      // If second vertice equal to first vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][0] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][0];
          secondVertice = endVertice = edgesInMSGraph[indexJ][1];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }

      // If second vertice equal to second vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][1] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][1];
          secondVertice = endVertice = edgesInMSGraph[indexJ][0];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }
    }
  }

  ///////////////////////////////////////////////////////
  beginVertice = toascii(verticeOne + 65);
  endVertice = 0;

  firstVertice = toascii(verticeOne + 65);
  secondVertice = toascii(verticeTwo + 65);

  for (indexI = 0; indexI < MAX; indexI++)
    edgeCheckList[indexI] = -1;

  edgeChecker = 0;
  runFor = numberOfEdgesInMSGraph;

  if (numberOfEdgesInMSGraph > 0)
  {
    for (indexI = 0; indexI < runFor; indexI++)
    {

      // If second vertice equal to second vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][1] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][1];
          secondVertice = endVertice = edgesInMSGraph[indexJ][0];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }

      // If second vertice equal to first vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][0] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][0];
          secondVertice = endVertice = edgesInMSGraph[indexJ][1];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }
    }
  }
  ///////////////////////////////////////////////////////

  beginVertice = toascii(verticeTwo + 65);
  endVertice = 0;

  firstVertice = toascii(verticeTwo + 65);
  secondVertice = toascii(verticeOne + 65);

  for (indexI = 0; indexI < MAX; indexI++)
    edgeCheckList[indexI] = -1;

  edgeChecker = 0;
  runFor = numberOfEdgesInMSGraph;

  if (numberOfEdgesInMSGraph > 0)
  {
    for (indexI = 0; indexI < runFor; indexI++)
    {

      // If second vertice equal to first vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][0] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][0];
          secondVertice = endVertice = edgesInMSGraph[indexJ][1];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }

      // If second vertice equal to second vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][1] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][1];
          secondVertice = endVertice = edgesInMSGraph[indexJ][0];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }
    }
  }

  ///////////////////////////////////////////////////////

  beginVertice = toascii(verticeTwo + 65);
  endVertice = 0;

  firstVertice = toascii(verticeTwo + 65);
  secondVertice = toascii(verticeOne + 65);

  for (indexI = 0; indexI < MAX; indexI++)
    edgeCheckList[indexI] = -1;

  edgeChecker = 0;
  runFor = numberOfEdgesInMSGraph;

  if (numberOfEdgesInMSGraph > 0)
  {
    for (indexI = 0; indexI < runFor; indexI++)
    {

      // If second vertice equal to second vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][1] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][1];
          secondVertice = endVertice = edgesInMSGraph[indexJ][0];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }

      // If second vertice equal to first vertice in next edge
      for (indexJ = 0; indexJ < runFor; indexJ++)
      {
        if (secondVertice == edgesInMSGraph[indexJ][0] && isEdgeAlreadyUsed(&indexJ))
        {
          firstVertice = edgesInMSGraph[indexJ][0];
          secondVertice = endVertice = edgesInMSGraph[indexJ][1];
          edgeCheckList[edgeChecker] = indexJ;
          edgeChecker += 1;
          if (beginVertice == endVertice)
            return 0;
          break;
        }
      }
    }
  }

  ///////////////////////////////////////////////////////
  return 1;
}
