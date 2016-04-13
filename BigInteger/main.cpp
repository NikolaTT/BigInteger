#include "FFT.h"
#include "BigInteger.h"
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <complex>
#include <time.h>
#include <algorithm>

using namespace std;


int main() {
	int addNum = 1000;

	time_t timer1;
	time_t timer2;

	BigInteger* arrBigInt = new BigInteger[addNum];
	
	for (int i = 0; i < addNum; i++) {
		arrBigInt[i] = BigInteger(rand());
	}

	cout << "Adding " << addNum << " numbers in: ";
	
	time(&timer1);
	for (int i = 0; i < addNum-1; i++) {
		arrBigInt[i].add(arrBigInt[i+1]);
	}
	time(&timer2);
	double seconds = difftime(timer2, timer1);
	cout << seconds << " seconds.";

	cout << endl << endl;

	cout << "Multiplying " << addNum << " numbers in: ";
	time(&timer1);
	for (int i = 0; i < addNum - 1; i++) {
		arrBigInt[i].multiply(arrBigInt[i + 1]);
	}
	time(&timer2);
	seconds = difftime(timer2, timer1);
	cout << seconds << " seconds.";

	cout << endl << endl;

	cout << "Subtracting " << addNum << " numbers in: ";
	time(&timer1);
	for (int i = 0; i < addNum - 1; i++) {
		arrBigInt[i].subtract(arrBigInt[i + 1]);
	}
	time(&timer2);
	seconds = difftime(timer2, timer1);
	cout << seconds << " seconds.";

	cout << endl << endl;

	system("pause");
}