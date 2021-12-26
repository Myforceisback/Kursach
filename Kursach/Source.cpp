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
#define inf 100000;

using namespace std;

int** Matrica, ** Vis, n, *PUTI;

int Razmer() {

	int n;
	cout << "Введите размер >> " << " ";
	cin >> n;
	return n;

}

int* FordBellman(int start)
{
	int* puti = new int[n];
	for (int i = 0; i < n; i++) {
		puti[i] = inf;
	}
	puti[start] = 0;
	
	for (int i = 1; i < n - 1; i++) {
		for (int j = 0; j < n/*возможная ошибка*/; j++)
			if (puti[i] + Matrica[i][j] < puti[j])
				puti[j] = puti[i] + Matrica[i][j];
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

void printPuti(int* Put) {

	cout << "Кратчайшие расстояния: " << endl;

	for (int i = 0; i < n; i++) {

		cout << Put << " ";

	}

	cout << endl;

}

void EditMatrica()
{
	int i, j, d, c;
	cout << "Введите номера смежных вершин и вес ребра между ними:\nДля завершения нажмите '-'\n";
	cin >> c;
	if (c == '-')
	{
		return;
	}
	else
	{
		cin >> i >> j >> d;
		if (i > n || j > n)
		{
			cout << "Таких вершин в графе нет!\n";
		}
		else
		{
			Matrica[i][j] = d;
		}
		printMatrica(Matrica);
		EditMatrica();
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matrica[i][j] == 0 && i != j)
			{
				Matrica[i][j] = SHRT_MAX;
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
}

void Save(int** Matrica, int** Vis)
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
	fprintf(G, "Матрица кратчайших путей:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Vis[i][j] == SHRT_MAX)
			{
				fprintf(G, " %d ", NULL);
			}
			else
			{
				fprintf(G, " %d ", Vis[i][j]);
			}
		}
		fprintf(G, "\n");
	}
	fclose(G);
}

void Read()
{
	FILE* G;
	if (!fopen("Graph", "r"))
	{
		printf("Невозможно открыть файл!\n");
		system("pause");
		return;
	}
	G = fopen("Graph", "r");
	fseek(G, 21, SEEK_SET);
	fscanf(G, "%d", &n);
	Matrica = createMatrix();
	fseek(G, 28, SEEK_CUR);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(G, " %d ", &Matrica[i][j]);
		}
	}
	fclose(G);
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
			PUTI = FordBellman(start-1);
			printPuti(PUTI);
			system("pause");
			break;

		case(5):

			system("cls");
			cout << "Результат сохранён в файл Graph." << endl;
			Save(Matrica, Vis);
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
	printf(HEADER);
	system("pause");
	menu();
	system("pause");
	return 0;

}

