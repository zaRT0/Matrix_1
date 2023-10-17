#include "Matrix_1.h"
#include <iostream>
using namespace std;
using namespace matrix;

int main() {
	setlocale(LC_ALL, "rus");
	Matrix<int> c(3, 3, 1);
	Matrix<int> d(3, 3, 2);
	c *= 2;
	cout << c;
	/*auto result = c * 2.0f;*/
	auto result = c * d;
	cout << result;
	return 0;
}
