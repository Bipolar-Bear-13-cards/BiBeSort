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
	cout << "������ �� 30 ���������" << endl;
	jh.print();
	jh();
	cout << "������, ��������������� �������\
 ����������� �����" << endl;
	jh.print();
	jh1();
	cout << "������, ���������������\
 ��������������� ����������� �����" << endl;
	jh1.print();
	cout << "����� ��� ��������� �������\
 ������ ���� ���������� ��� �������,\
����� �������� �� ������ �������" << endl;
	int ygr = 0;
	while (ygr < 1) {
		cout << "������� ����� ����������\
 ����������" << endl;
		cin >> ygr;
	}
	int yfd = 0;
	while (yfd < 1) {
		cout << "������� ����������\
 ������������" << endl;
		cin >> yfd;
	}
	int yhf = 0;
	while (yhf < 1) {
		cout << "������� �����\
 ��������� � �����������\
 �������" << endl;
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
	cout << "���������� ������������ \
(��������������� ���������� \
/ ������� ����������)" << endl;
	uya.print_results();
	cout << "� ���������\
 ���������� �������� " << jh.get_adt()\
		<< " �������(-a)" << endl;
	system("pause");
	delete[] jjj;
	delete[] hhh;
	return 0;
}