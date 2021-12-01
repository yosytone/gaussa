#include <iostream>
#include <time.h>  
#include <windows.h>
#include <iomanip>
#include <random>
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	uniform_int_distribution<int> z(0, 100);
	random_device rd1;
	int n, i, j, k;
	double d, s;

	double delta_f = 0;
	double f_error_sum = 0;
	int number_delta_f = 0;

	double delta_x = 0;
	double x_error_sum = 0;
	int number_delta_x = 0;

	// Генерация матрицы и решения x(x_solution)
	cout << "Порядок матрицы: " << endl;
	cin >> n;

	int N = n + 1;
	double** A = new double* [N];
	double** A_transposed = new double* [N];
	double* f = new double[N];
	double* f_result = new double[N];
	double* x = new double[N];
	double* x_solution = new double[N];

	for (i = 0; i <= n; i++) {
		A[i] = new double[N];
		A_transposed[i] = new double[N];
	}


	//Заполнение матрицы и решения
	for (i = 1; i <= n; i++) {

		for (j = 1; j <= n; j++) {
			A[i][j] = 0;
			A_transposed[i][j] = 0;
			A[i][j] = z(rd1);
			A_transposed[i][j] = A[i][j];
		}
		x_solution[i] = z(rd1);
	}


	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			std::cout << std::setw(4) << A[i][j];
		std::cout << std::endl;
	}

	///////////////////////////////////////////////////



	double max_el = 0;
	int index_max_el = 0;
	int w = 1;


	while (w <= n) {

		max_el = 0;
		index_max_el = 0;

		for (i = w; i <= n; i++) {
			if (A[i][w] > max_el) {
				max_el = A[i][w];
				index_max_el = i;

			}
		}



		cout << "max = " << max_el << " " << index_max_el << endl;



		double zam = 0;

		for (j = w; j <= n; j++) {
			zam = A[w][j];
			A[w][j] = A[index_max_el][j];
			A[index_max_el][j] = zam;
		}

		w++;

	}


	///////////////////////////////////////////////////////

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			std::cout << std::setw(4) << A[i][j];
		std::cout << std::endl;
	}



	//Вычисление f
	for (i = 1; i <= n; i++) {

		f[i] = 0;
		for (j = 1; j <= n; j++) {
			f[i] += A[i][j] * x_solution[j];
		}
	}


	for (k = 1; k <= n; k++) {
		for (j = k + 1; j <= n; j++) {

			d = A[j][k] / A[k][k];
			for (i = k; i <= n; i++) {
				A[j][i] = A[j][i] - d * A[k][i];
			}
			f[j] = f[j] - d * f[k];
		}
	}


	for (k = n; k >= 1; k--) {
		d = 0;
		for (j = k + 1; j <= n; j++) {
			s = A[k][j] * x[j];
			d = d + s;
		}
		x[k] = (f[k] - d) / A[k][k];
	}

	//Вычисление f*
	for (i = 1; i <= n; i++) {

		f_result[i] = 0;
		for (j = 1; j <= n; j++) {
			f_result[i] += A[i][j] * x[j];
		}
	}

	for (i = 1; i <= n; i++)
		cout << "f[" << i << "]= " << f[i] << '\t' << "f*[" << i << "]= " << f_result[i] << endl;

	cout << endl << "Решения системы:" << endl;
	for (i = 1; i <= n; i++)
		cout << "x[" << i << "] = " << x_solution[i] << '\t' << "x*[" << i << "] = " << x[i] << endl;


	for (i = 1; i <= n; i++) {
		if (abs((x_solution[i] - x[i])) > abs(delta_x)) {
			delta_x = x_solution[i] - x[i];
			number_delta_x = i;
		}
	}


	for (i = 1; i <= n; i++) {
		delta_x = x_solution[i] - x[i];
		number_delta_x = i;
	}



	cout << endl << "погрешность: " << delta_x << endl;
	return 0;

}
