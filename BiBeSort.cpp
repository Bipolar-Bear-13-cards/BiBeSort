#include "stdafx.h"
#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <cmath>
#include <chrono>
#include <atomic>
#include "BiBeSort_1.h"
#include "BiBeSort_2.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	double * jjj;
	jjj = new double[30];
	for (int i = 0; i < 30; i++)
		jjj[i] = rand();
	my_array <double> jh(jjj, 30);
	my_array1 <double> jh1(jjj, 30);
	cout << "массив из 30 элементов" << endl;
	jh.print();
	jh();
	cout << "массив, отсортированной обычной\
 сортировкой Шелла" << endl;
	jh.print();
	jh1();
	cout << "массив, отсортированной\
 распараллеленой сортировкой Шелла" << endl;
	jh1.print();
	cout << "далее идёт сравнение времени\
 работы этих сортировок для массива,\
длину которого вы введёте позднее" << endl;
	int ygr = 0;
	while (ygr < 1) {
		cout << "введите число повторений\
 сортировки" << endl;
		cin >> ygr;
	}
	int yfd = 0;
	while (yfd < 1) {
		cout << "введите количество\
 исследований" << endl;
		cin >> yfd;
	}
	int yhf = 0;
	while (yhf < 1) {
		cout << "введите число\
 элементов в исследуемом\
 массиве" << endl;
		cin >> yhf;
	}
	double * hhh;
	hhh = new double[yhf];
	for (int i = 0; i < yhf; i++)
		hhh[i] = rand();
	my_array <double> jhu(hhh, yhf);
	my_array1 <double> jhu1(hhh, yhf);
	TestSystem uya;
	uya(jhu, jhu1, ygr, yfd);
	cout << "результаты исследований \
(распараллеленая сортировка \
/ обычная сортировка)" << endl;
	uya.print_results();
	cout << "в праграмме\
 паралельно работало " << jh.get_adt()\
		<< " потоков(-a)" << endl;
	system("pause");
	delete[] jjj;
	delete[] hhh;
	return 0;
}