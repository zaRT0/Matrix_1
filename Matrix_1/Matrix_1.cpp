﻿#include "Matrix_1.h"
#include<iostream>
using namespace std;
using namespace matrix;

int main() {
	setlocale(LC_ALL, "rus");
	Matrix<int> c(3, 3, 4);
	Matrix<int> d(3, 3, 3);
	c *= 2;
	cout << c;
	return 0;
}
