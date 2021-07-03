#include <iostream>
#include <thread>

using namespace std;

void print(int** arr, int n, int m)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			cout << *(*(arr+i)+j) << " ";
		}
		cout << endl;
	}
}

int check_right(int** arr, int** check_arr, int n, int m, int i, int j);
int check_up(int** arr, int** check_arr, int n, int m, int i, int j);
int check_down(int** arr, int** check_arr, int n, int m, int i, int j);

int check_left(int** arr, int** check_arr, int n, int m, int i, int j)
{
	int S = 0;
	check_arr[i][j] = 1;
	//Left
	if (j - 1 >= 0)
	{
		if ((arr[i][j - 1] == 1)&&(check_arr[i][j-1] == 0))
		{
			S += 1 + check_left(arr, check_arr, n, m, i, j - 1);
		}
	}

	//Up
	if (i - 1 >= 0)
	{
		if ((arr[i - 1][j] == 1) && (check_arr[i-1][j] == 0))
		{
			S += 1 + check_up(arr, check_arr, n, m, i - 1, j);
		}
	}

	//Down
	if (i + 1 < n)
	{
		if ((arr[i + 1][j] == 1)&&(check_arr[i+1][j] == 0))
		{
			S += 1 + check_down(arr, check_arr, n, m, i + 1, j);
		}
	}

	return S;

}

int check_right(int** arr, int** check_arr, int n, int m, int i, int j)
{
	int S = 0;
	check_arr[i][j] = 1;

	//Right
	if (j + 1 < m)
	{
		if ((arr[i][j + 1] == 1)&&(check_arr[i][j + 1] == 0))
		{
			S += 1 + check_right(arr, check_arr, n, m, i, j + 1);
		}
	}
	//Up
	if (i - 1 >= 0)
	{
		if ((arr[i - 1][j] == 1) && (check_arr[i - 1][j] == 0))
		{
			S += 1 + check_up(arr, check_arr, n, m, i - 1, j);
		}
	}

	//Down
	if (i + 1 < n)
	{
		if ((arr[i + 1][j] == 1) && (check_arr[i + 1][j] == 0))
		{
			S += 1 + check_down(arr, check_arr, n, m, i + 1, j);
		}
	}
	return S;
}

int check_up(int** arr, int** check_arr, int n, int m, int i, int j)
{
	int S = 0;
	check_arr[i][j] = 1;
	//Left
	if (j - 1 >= 0)
	{
		if ((arr[i][j - 1] == 1) && (check_arr[i][j - 1] == 0))
		{
			S += 1 + check_left(arr, check_arr, n, m, i, j - 1);
		}
	}
	//Right
	if (j + 1 < m)
	{
		if ((arr[i][j + 1] == 1) && (check_arr[i][j + 1] == 0))
		{
			S += 1 + check_right(arr, check_arr, n, m, i, j + 1);
		}
	}
	//Up
	if (i - 1 >= 0)
	{
		if ((arr[i - 1][j] == 1) && (check_arr[i - 1][j] == 0))
		{
			S += 1 + check_up(arr, check_arr, n, m, i - 1, j);
		}
	}
	return S;
}

int check_down(int** arr, int** check_arr, int n, int m, int i, int j)
{
	int S = 0;
	check_arr[i][j] = 1;
	//Left
	if (j - 1 >= 0)
	{
		if ((arr[i][j - 1] == 1) && (check_arr[i][j - 1] == 0))
		{
			S += 1 + check_left(arr, check_arr, n, m, i, j - 1);
		}
	}
	//Right
	if (j + 1 < m)
	{
		if ((arr[i][j + 1] == 1) && (check_arr[i][j + 1] == 0))
		{
			S += 1 + check_right(arr, check_arr, n, m, i, j + 1);
		}
	}
	//Down
	if (i + 1 < n)
	{
		if ((arr[i + 1][j] == 1) && (check_arr[i + 1][j] == 0))
		{
			S += 1 + check_down(arr, check_arr, n, m, i + 1, j);
		}
	}
	return S;
}
int check(int** arr, int** check_arr, int n, int m, int i, int j)
{
	if (arr[i][j] == 1)
	{
		int S = 1;
		check_arr[i][j] = 1;
		//Left
		thread th_left([&]() {
			if (j - 1 >= 0)
			{
				if (arr[i][j - 1] == 1)
				{
					S += 1 + check_left(arr, check_arr, n, m, i, j - 1);
				}
			}
		});
		

		//Right
		thread th_right([&]() {
			if (j + 1 < m)
			{
				if (arr[i][j + 1] == 1)
				{
					S += 1 + check_right(arr, check_arr, n, m, i, j + 1);
				}
			}
		});
		

		//Up
		thread th_up([&]() {
			if (i - 1 >= 0)
			{
				if (arr[i - 1][j] == 1)
				{
					S += 1 + check_up(arr, check_arr, n, m, i - 1, j);
				}
			}
		});
		

		//Down
		thread th_down([&]() {
			if (i + 1 < n)
			{
				if (arr[i + 1][j] == 1)
				{
					S += 1 + check_down(arr, check_arr, n, m, i + 1, j);
				}
			}
		});

		th_left.join();
		th_right.join();
		th_up.join();
		th_down.join();
		
		
		return S;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int n = 10, m = 10;
	srand(11);
	int** arr = new int*[n];
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = new int[m];
		for (size_t j = 0;  j < m;  j++)
		{
			arr[i][j] = rand() % 2;
		}
	}

	int** check_arr = new int*[n];
	for (size_t i = 0; i < n; i++)
	{
		check_arr[i] = new int[m];
		for (size_t j = 0; j < m; j++)
		{
			check_arr[i][j] = 0;
		}
	}

	cout << "Array: " << endl;
	print(arr, n, m);

	int Smax = 0;
	int S = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			S = check(arr, check_arr, n, m, i, j);
			if (S > Smax)
			{
				Smax = S;
			}
		}
	}

	cout << endl << "-----------------------------------------------" << endl;

	cout << "Check Array: " << endl;
	print(check_arr, n, m);

	cout << endl << "-----------------------------------------------" << endl;

	cout << "Smax = " << Smax << endl;

	return 0;
}