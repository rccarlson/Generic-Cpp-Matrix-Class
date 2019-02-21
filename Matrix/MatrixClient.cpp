#include "pch.h"
#include "Matrix.h"
#include <iostream>
#include <initializer_list>
/*void looper();

int main() {
	int loopcount = 0;
	while (true) {
		looper();
		if (++loopcount % 100000 == 0)
			std::cout << "loop " << loopcount << std::endl;
	}
}*/

void main()
{
	Matrix<double> a({ {1,2},{3,4},{5,6} });
	std::cout << "Matrix a:" << std::endl;
	a.print();
	Matrix<double> b({ {7,8,9},{10,11,12} });
	std::cout << "Matrix b:" << std::endl;
	b.print();
	std::cout << std::endl;
	
	std::cout << "c=a*b:" << std::endl;
	Matrix<double> c = (a * b);
	c.print();
	std::cout << std::endl;

	std::cout << "a+2:" << std::endl;
	(a+2).print();
	std::cout << std::endl;

	std::cout << "try to find determinant of a:" << std::endl;
	try {
		std::cout << a.det() << std::endl;
	}
	catch (InvalidDimensions e) {
		std::cout << "Could not find determinant because: " << e.what() << std::endl;
	}
	
	std::cout << "redefine c" << std::endl;
	c = { {3,8},{4,6} };
	c.print();
	std::cout << "determinant of c = " << c.det() << std::endl;
	std::cout << "inverse of c:" << std::endl;
	c.inv().print();
	std::cout << "transpose c:" << std::endl;
	c.transpose().print();
	std::cout << "trace of c = " << c.trace() << std::endl;
	std::cout << std::endl;
	
}
