#include "stdafx.h"
#include <iostream>
#include <time.h>  
using namespace std;

double const NORM = 1e-10;


double Rand_Double_Range(double A, double b)
{
	return ((b - A) * ((double)rand() / RAND_MAX)) + A;
}

void Rand_matrix_and_sol(double** A, double** A_transposed, double* x_solution, int n) {

	for (int i = 1; i <= n; i++) {

		for (int j = 1; j <= n; j++) {
			A[i][j] = 0;
			A_transposed[i][j] = 0;
			A[i][j] = Rand_Double_Range(-10, 10);
			A_transposed[i][j] = A[i][j];
		}
		x_solution[i] = Rand_Double_Range(-10, 10);
	}

}

void F_solution(double** A, double* f, double* x_solution, int n) {

	for (int i = 1; i <= n; i++) {

		f[i] = 0;
		for (int j = 1; j <= n; j++) {
			f[i] += A[i][j] * x_solution[j];
		}
	}
}

void Gaus(double** A, double* x, double* f, int n) {
	//Метод Гаусса состоит из прямого и обратного хода
	// прямой ход
	double d = 0, s = 0;
	int i, k, j;

	for (k = 1; k <= n; k++) {
		for (j = k + 1; j <= n; j++) {

			d = A[j][k] / A[k][k];
			for (i = k; i <= n; i++) {
				A[j][i] = A[j][i] - d * A[k][i];
			}
			f[j] = f[j] - d * f[k];
		}
	}

	// обратный ход
	for (k = n; k >= 1; k--) {
		d = 0;
		for (j = k + 1; j <= n; j++) {
			s = A[k][j] * x[j];
			d = d + s;
		}
		x[k] = (f[k] - d) / A[k][k];
	}

}

void Jacobi(double** A, double* x, double* f, int n) {

	int it = 0;
	long double* Temp = new long double[n + 1];
	double norm;
	do {

		for (int i = 1; i <= n; i++)
		{
			Temp[i] = f[i];
			for (int j = 1; j <= n; j++)
			{
				if (j != i) {
					Temp[i] -= A[i][j] * x[j];
				}
			}
			Temp[i] /= A[i][i];
		}

		norm = abs(x[1] - Temp[1]);
		x[1] = Temp[1];
		for (int h = 2; h <= n; h++) {
			if (abs(x[h] - Temp[h]) > norm)
				norm = abs(x[h] - Temp[h]);
			x[h] = Temp[h];
		}


		it++;

	} while (norm > NORM);

	delete[] Temp;

}

void Gauss_Seidel(double** A, double* x, double* f, int n) {

	int it = 0;
	long double* Temp = new long double[n + 1];
	double norm;
	do {

		for (int i = 1; i <= n; i++)
		{
			Temp[i] = f[i];
			for (int j = 1; j <= n; j++)
			{
				if (j != i) {
					Temp[i] -= A[i][j] * x[j];
				}

			}
			Temp[i] /= A[i][i];
			//
			x[i] = Temp[i];
		}

		norm = abs(x[1] - Temp[1]);
		x[1] = Temp[1];
		for (int h = 2; h <= n; h++) {
			if (abs(x[h] - Temp[h]) > norm)
				norm = abs(x[h] - Temp[h]);
			//
		}


		it++;

	} while (norm > NORM);
	delete[] Temp;

}

void display_vectors_Prosejure(double* f, double* f_result, double* x, double* x_solution, int n) {

	int i;
	for (i = 1; i <= n; i++)
		cout << "f[" << i << "]= " << f[i] << "\tf*[" << i << "]= " << f_result[i] << endl;



	cout << endl << "Solutios of sistem: " << endl;
	for (i = 1; i <= n; i++)
		cout << "x[" << i << "]= " << x_solution[i] << "\t" << "x*[" << i << "]=" << x[i] << endl;
}

void f_calc_error(double* f, double* f_result, int n) {

	int i, number_delta_f;
	double delta_f = 0, f_error_sum = 0;

	for (i = 1; i <= n; i++) {
		if (abs((f[i] - f_result[i])) > abs(delta_f)) {
			delta_f = f[i] - f_result[i];
			number_delta_f = i;
		}
	}
	cout << endl << "Num of \"f\" biggest error:" << number_delta_f
		<< endl << "Biggest \"f\" error:\t" << delta_f << endl;

	for (i = 1; i <= n; i++) {
		if (f[i] - f_result[i] != 0) {
			f_error_sum += abs(f[i] - f_result[i]);
		}
	}
	cout << "abs sum of \"f\" errors:\t" << f_error_sum << endl << endl;
}

void x_calc_error(double* x, double* x_solution, int n) {
	int i, number_delta_x;
	double delta_x = 0, x_error_sum = 0;

	for (i = 1; i <= n; i++) {
		if (abs((x_solution[i] - x[i])) > abs(delta_x)) {
			delta_x = x_solution[i] - x[i];
			number_delta_x = i;
		}
	}
	cout << endl << "погрешность \"x\":\t" << delta_x << endl;

}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int n, i, j, k;
	double d, s;

	double delta_f = 0;
	double f_error_sum = 0;
	int number_delta_f = 0;

	double delta_x = 0;
	double x_error_sum = 0;
	int number_delta_x = 0;



	// Генерация матрицы и решения x(x_solution)
	cout << "Порядок Матрицы: ";
	cin >> n;

	int N = n + 1; // Для удобства работы с матрицей сместим коэффициенты массива на +1 (с 0 на 1)
	double** A = new double*[N];
	double** A_transposed = new double*[N];
	double* f = new double[N]; //реальное решение
	double* f_result = new double[N];   // полученное слау
	double* x = new double[N];    // полученное слау
	double* x_solution = new double[N]; //реальное решение

	for (i = 0; i <= n; i++) {
		A[i] = new double[N];
		A_transposed[i] = new double[N];
	}

	//Заполнение матрицы и решения x(x_solution)
	Rand_matrix_and_sol(A, A_transposed, x_solution, n);


	for (int i = 1; i <= n; i++)
	{
		A[i][i] = abs(A[i][i]) * n*n;
	}

	//Вычисление f
	F_solution(A, f, x_solution, n);

	//Метод Гаусса
	

	for (int i = 1; i <= n; i++)
		x[i] = 1;
	Jacobi(A, x, f, n);

	
	

	// f и f*
	//Вычисление f*
	for (i = 1; i <= n; i++) {

		f_result[i] = 0;
		for (j = 1; j <= n; j++) {
			f_result[i] += A[i][j] * x[j];
		}
	}




	//f-f*
	//f_calc_error(f, f_result, n);

	//x and x*
	x_calc_error(x, x_solution, n);




	Gauss_Seidel(A, x, f, n);

	// f и f*
	//Вычисление f*
	for (i = 1; i <= n; i++) {

		f_result[i] = 0;
		for (j = 1; j <= n; j++) {
			f_result[i] += A[i][j] * x[j];
		}
	}




	//f-f*
	//f_calc_error(f, f_result, n);

	//x and x*
	x_calc_error(x, x_solution, n);


	system("pause");
	return 0;

}
