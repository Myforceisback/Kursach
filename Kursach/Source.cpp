#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
using namespace std;


void BellmanFordalgorithm(int ** matr, int *vis, int N) {
	vis[0] = 0;
	for (int i = 0; i < N; i++) {

		for (int j = 0; j < N; j++) {

			if (vis[matr[i][j]] + matr[i][j] < vis[matr[i][j]])

				vis[matr[i][j]] = vis[matr[i][j]] + matr[i][j];

		}

	}
}
void BellmanFordalgorithm_edges() {
	
		
}
int** create_matrix(int n) {

	int** matrix;
	matrix = (int**)malloc(n * sizeof(int*));

	int s = 1;
	srand(time(NULL));
	for (int i = 0; i < n; i++) // создание матрицы
	{
		matrix[i] = (int*)malloc(n * sizeof(int));
		matrix[i][i] = 0;
		for (int j = s; j < n; j++)
		{
			if (rand() % 100 > 30)
			{
				matrix[i][j] = 0;
			}
			else {
				matrix[i][j] = 1;
			}
		}
		s++;
	}
	s = 1;
	for (int i = 0; i < n; i++) // неориентированный граф
	{
		for (int j = s; j < n; j++)
			matrix[j][i] = matrix[i][j];
		s++;
	}
	return matrix;
}
void main()
{
	int navigate_number = 0;
	while (navigate_number != 6) {

		cout << "Bellman - Ford algorithm" << endl;
		cout << "-_-_-_-_- MENU -_-_-_-_-" << endl;
		cout << "1) Matrix creation and Execute algorithm for adjacency matrix" << endl;
		cout << "2) Edges creation and Execute an algorithm for a list of edges" << endl;
		cout << "3) Write to file" << endl;
		cout << "4) Read from file" << endl;
		cout << "5) Exit" << endl;

		cout << "\nSelect a menu item >> " << " "; cin >> navigate_number;
		cout << endl;
		switch (navigate_number) {

		case(1):
		{
			int n;
			cout << "Number of vertices > "; cin >> n;
			int* visited = new int[n];
			for (int i = 0; i < n; i++)
				for (int k = 0; k < n; k++)
					visited[k] = 1000;

			int** matrix = create_matrix(n);
			cout << "Matrix"; // вывод матрицы на экран
			for (int i = 0; i < n; i++)
			{
				cout << endl;
				for (int j = 0; j < n; j++)
				{
					cout << matrix[i][j] << " ";
				}
			}
			cout << endl;
			cout << endl;
			BellmanFordalgorithm(matrix, visited, n);
			for (int i = 0; i < n; i++) {
				cout << visited[i] << " ";
			}
		}
		break;
		case(2):
		{
			cout << 2;
		}
		break;
		case(6):
		{
			exit;
		}

		}

	}
}
