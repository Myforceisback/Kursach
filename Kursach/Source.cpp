#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define HEADER ("Курсовая работа\nТема: Алгоритм Форда - Беллмана.\nВыполнил: Шадрин Д.А.\n")
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <queue>
#include <algorithm>
#define inf 10000;

using namespace std;

int** Matrica, ** Vis, n, puti[1000], e, x;

struct Edges {
	int v, u, w;
};
Edges edge[10000];

int Razmer() {

	int n;
	cout << "Введите размер >> " << " ";
	cin >> n;
	return n;

}

int* FordBellman(int start)
{
	for (int i = 0; i < n; i++) {
		puti[i] = inf;
	}
	puti[start] = 0;

	for (int i = 0; i < n; i++) {
		x = 0;
		bool stop = false;
		for (int j = 0; j < e; j++)
			if (puti[edge[j].v] + edge[j].w < puti[edge[j].u]) {

				puti[edge[j].u] =  puti[edge[j].v] + edge[j].w;
				x = edge[j].u;
				stop = true;

			}
		if (!stop) break;
	}

	if (x != 0) {
		cout << " Ошибка, найден отрицательный цикл" << endl;
	}
	else {
		cout << "Кратчайшие расстояния: " << endl;

		for (int i = 0; i < n; i++) {

			cout << puti[i] << " ";

		}

		cout << endl;
	}
	
	return puti;
}

int** createMatrix() {

		int** M = (int**)(malloc(n * sizeof(int*)));
		for (int i = 0; i < n; i++)
		{
			M[i] = (int*)(malloc(n * sizeof(int)));
			for (int j = 0; j < n; j++)
			{
				M[i][j] = 0;
			}
		}
		return M;
	}

void printMatrica(int** Matrica)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] == SHRT_MAX)
			{
				cout << NULL << " ";
			}
			else
			{
				cout << Matrica[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void EditMatrica()
{
	cout << endl << endl << "Введите расстояния путей между вершинами:" << endl;
	for (int row = 0; row < n; row++) {

		for (int col = 0; col < n; col++) {
			cout << endl << "[" << row + 1 << "] -> [" << col + 1 << "] = ";
			cin >> Matrica[row][col];
		}
	}
		printMatrica(Matrica);
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] == 0 && i != j)
			{
				Matrica[i][j] = SHRT_MAX;
			}
		}
	}*/
	e = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] != 0)// передача значений в список ребер
			{
				edge[e].v = i;
				edge[e].u = j;
				edge[e].w = Matrica[i][j];
				e++;
			}
		}
	}
}

void EditVis()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				Matrica[i][j] = 0;
			}
			else if (rand() % 100 < 30)
			{
				Matrica[i][j] = SHRT_MAX;
			}
			else
			{
				Matrica[i][j] = (rand() % n) + 1;
			}
		}
	}
	e = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] != 0)// передача значений в список ребер
			{
				edge[e].v = i;
				edge[e].u = j;
				edge[e].w = Matrica[i][j];
				e++;
			}
		}
	}
}

void Save(int** Matrica, int* puti, int start)
{
	FILE* G = fopen("Graph", "w");
	fprintf(G, "Размерность матрицы: %d\n", n);
	fprintf(G, "Матрица смежности графа:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] == SHRT_MAX)
			{
				fprintf(G, " %d ", NULL);
			}
			else
			{
				fprintf(G, " %d ", Matrica[i][j]);
			}
		}
		fprintf(G, "\n");
	}
	if (x != 0) {
		
		fprintf(G, "Найден отрицательный цикл");
		fclose(G);
		return;
	}
	else{
		for (int i = 0; i < n; i++) {

			if (puti[i] == 10000)
				fprintf(G, "%d -> %d = Пути не существует\n", start, i );
			else {
				fprintf(G, "%d -> %d = %d\n", start, i , puti[i]);

			}
		}
		fclose(G);
	}
	
	FILE* Gg = fopen("GraphMatrix", "w");
	fprintf(Gg, "%d\n", n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] == SHRT_MAX)
			{
				fprintf(Gg, "%d ", NULL);
			}
			else
			{
				fprintf(Gg, "%d ", Matrica[i][j]);
			}
		}
		fprintf(Gg, "\n");
	}
	fclose(Gg);
}

void Read()
{
	FILE* Gg;
	if (!fopen("Graph", "r"))
	{
		printf("Невозможно открыть файл!\n");
		system("pause");
		return;
	}
	Gg = fopen("GraphMatrix", "r");
	fscanf(Gg, "%d", &n);
	Matrica = createMatrix();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(Gg, " %d ", &Matrica[i][j]);
		}
	}
	fclose(Gg);
	e = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] != 0)// передача значений в список ребер
			{
				edge[e].v = i;
				edge[e].u = j;
				edge[e].w = Matrica[i][j];
				e++;
			}
		}
	}
}

void addVersh()
{
	Matrica = (int**)(realloc(Matrica, (n + 1) * sizeof(int**)));
	for (int i = 0; i < n; i++)
	{
		Matrica[i] = (int*)(realloc(Matrica[i], (n + 1) * sizeof(int)));
	}
	Matrica[n] = (int*)(malloc((n + 1) * sizeof(int)));
	n++;
	for (int i = 0; i < n; i++)
	{
		Matrica[n - 1][i] = 0;
		Matrica[i][n - 1] = 0;
	}
}

void delVersh(int v)
{
	for (int i = v; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Matrica[i][j] = Matrica[i + 1][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = v; j < n - 1; j++)
		{
			Matrica[i][j] = Matrica[i][j + 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		Matrica[i] = (int*)(realloc(Matrica[i], (n - 1) * sizeof(int)));
	}
	free(Matrica[n - 1]);
	n--;
}

void Secmenu() {

	int nav_n, nav_nn;
	do
	{

		system("cls");
		cout << "Редактирование\n1)Заполнение графа\n2)Добавление вершины\n3)Удаление вершины\n4)Назад\n->";
		cin >> nav_n;
		switch (nav_n) 
		{
		case(1):

			system("cls");
			cout << "Заполнение матрицы?\n1)Ручное\n2)Автоматическое\n3)Назад\n->";
			cin >> nav_nn;
			if (nav_nn == 1)
			{
				EditMatrica();
			}
			else if (nav_nn == 2)
			{
				EditVis();
				system("cls");
				cout << "Успех" << endl;
				system("pause");
			}
			else if (nav_nn == 3)
			{
				return;
			}
			else
			{
				cout << "ERROR" << endl;
				system("pause");
			}break;

		case(2):

			system("cls");
			Razmer();
			cout << "Успех" << endl;
			system("pause");
			break;

		case(3):

			system("cls");
			cout << "Номер удаляемой вершины >> " << endl;
			cin >> nav_nn;
			if (nav_nn < nav_n)
			{
				delVersh(nav_nn);
			}
			else
			{
				system("cls");
				cout << "Вершины нет" << endl;
				system("pause");
				return;
			}
			break;

		case(4):

			return;

		default:

			system("cls");
			cout << "ERROR" << endl;
			system("pause");
			break;

		}

	} while (nav_n != 4);

}

void menu()
{
	int nav_n;
	do {
		system("cls");
		cout << "Меню\n1)Создать граф\n2)Редактировать граф\n3)Посмореть граф\n4)Алгоритм Форда - Беллмана\n5)Сохранить результат\n6)Загрузить граф\n7)Выход\n->";
		cin >> nav_n;
		switch (nav_n) 
		{
		case(1):

			system("cls");
			n = Razmer();
			Matrica = createMatrix();
			Vis = createMatrix();
			break;

		case(2):

			Secmenu();
			break;

		case(3):

			system("cls");
			cout << "Матрица смежности:" << endl;
			printMatrica(Matrica);
			system("pause");
			break;

		case(4):
			int start;
			cout << "Стартовая вершина >> " << " ";
			cin >> start;
			FordBellman(start-1);
			system("pause");
			break;

		case(5):

			system("cls");
			cout << "Результат сохранён в файл Graph." << endl;
			Save(Matrica, puti, start);
			system("pause");
			break;

		case (6):

			system("cls");
			Read();
			cout << "Матрица смежности успешно загружена!" << endl;
			system("pause");
			break;

		case(7):

			exit(NULL);

		default:
			system("cls");
			cout << "ERROR" << endl;
			system("pause");
			break;
		}
	} while (nav_n != 7);
}

int main() {

	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	cout << HEADER;
	system("pause");
	menu();
	system("pause");
	return 0;

}
