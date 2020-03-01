// CSP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <queue>

int nodeNumber;
int edgeNumber;
const int colorNumber = 3;
int stepCount = 0;
int Method;


typedef struct NODE
{
	int degree = 0;
	int color = 0;
	std::bitset<colorNumber> domain;

} NODE;

typedef struct EDGE
{
	int left;
	int right;
} EDGE;

// Printing the color array.
void printSolution(int assigment[])
{
	printf("Solution Exists: The colors in order are the following \n");
	for (int i = 1; i <= nodeNumber; i++)
	{
		printf(" %d ", assigment[i]);
	}
	printf("\n");
}

// Check is it safe to proceed with the function, if the selected node exists and color can be filled
bool isSafe(int v, int** matrix, int assignment[], int color)
{
	for (int i = 1; i <= nodeNumber; i++)
	{
		if (matrix[v][i] && color == assignment[i])
		{
			return false;
		}
	}
	return true;
}

void updateNeighboursDomains(NODE* nodes, int** matrix, int currentNodeIndex, int domainIndex)
{
	for (int i = 1; i <= nodeNumber; i++)
	{
		if (matrix[currentNodeIndex][i] == 1)
		{
			nodes[i].domain[domainIndex] = false;
		}
	}
}

void resetNeighboursDomains(NODE* nodes, int** matrix, int currentNodeIndex, int domainIndex)
{
	for (int i = 1; i <= nodeNumber; i++)
	{
		if (matrix[currentNodeIndex][i] == 1)
		{
			nodes[i].domain[domainIndex] = true;
		}
	}
}


int selectUnassignedNode(NODE *nodes)
{
	for (int i = 1; i <= nodeNumber; i++)
	{
		if (nodes[i].color == 0)
		{
			return i;
		}
	}

	return 0;
}


//Function to solve the backtracking problem
bool recursiveBacktracking(NODE* nodes, int** matrix, int assignment[], int v)
{
	if (v == nodeNumber)
	{
		return true;
	}

	int currentNodeIndex;
	currentNodeIndex = selectUnassignedNode(nodes);
	//currentNodeIndex = selectUnassignedMVR(nodes); AZ MVR SEHOGY SEM AKART MENNI, NO IDEA WHY 

	if (currentNodeIndex == 0)
	{
		return false;
	}

	for (int i = 0; i < nodes[currentNodeIndex].domain.size(); i++)
	{
		if (nodes[currentNodeIndex].domain[i] == true)
		{
			if (isSafe(v, matrix, assignment, i + 1))
			{
				// Give color to current node
				nodes[currentNodeIndex].color = i + 1;
				assignment[v] = i + 1;
				
				stepCount++;

				// Recursion to assign colors to the nodes
				if (recursiveBacktracking(nodes, matrix, assignment, v + 1) == true)
				{
					return true;
				}

				// Remove color if no solution
				assignment[v] = 0;
				nodes[currentNodeIndex].color = 0;
				
			}
		}
	}
	// If no color can be assigned to a node
	return false;
}


//Function to start the backtracking procedure.
bool backtrackingSearch(NODE* nodes, int** matrix)
{
	// Create color array
	int *assignment = new int[nodeNumber];
	for (int i = 1; i <= nodeNumber; i++)
	{
		assignment[i] = 0;
	}

	// Start the backtrack
	if (recursiveBacktracking(nodes, matrix, assignment, 1) == false)
	{
		printf("Solution does not exist");
		return false;
	}

	for (int i = 1; i <= nodeNumber; i++)
	{
		if (assignment[i] == 0)
		{
			assignment[i] = 1;
		}
	}

	// Print the solution 
	printSolution(assignment);

	std::cout << "\nStepcount: " << stepCount << "\n";

	return true;
}



int main()
{
	// Reading input from file
	std::ifstream file;
	file.open("input.txt");
	if (file.is_open())
	{
		file >> nodeNumber >> edgeNumber;
	}
	else
	{
		return 0;
	}

	int i, j, k;
	NODE *nodes = new NODE[nodeNumber + 1];
	EDGE *edges = new EDGE[edgeNumber + 1];
	std::queue<EDGE> edgeQueue;

	// Create adjacency matrix
	int **adjacency = new int*[nodeNumber + 1];
	for (i = 1; i <= nodeNumber; i++)
	{
		adjacency[i] = new int[nodeNumber + 1];
	}
	for (i = 1; i <= nodeNumber; i++)
	{
		for (j = 1; j <= nodeNumber; j++)
		{
			adjacency[i][j] = 0;
		}
	}

	// Read domain and set bits to 1
	for (int i = 1; i <= nodeNumber; i++)
	{
		for (int j = 0; j < nodes[i].domain.size(); j++)
		{
			nodes[i].domain.set(j, 1);
		}
	}

	// Read edges and adjacency matrix
	for (i = 1; i <= edgeNumber; ++i)
	{
		file >> edges[i].left >> edges[i].right;
		edgeQueue.push(edges[i]);
		nodes[edges[i].left].degree++;
		nodes[edges[i].right].degree++;
		adjacency[edges[i].left][edges[i].right] = 1;
		adjacency[edges[i].right][edges[i].left] = 1;
	}

	std::cout << "Backtrack starting ..." << "\n";
	backtrackingSearch(nodes, adjacency);


	return 0;
}

