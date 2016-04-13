#include "BigInteger.h"
#include <iostream>
#include <string>
#include <iterator>
#include <math.h>

BigInteger::BigInteger(std::vector<int> input) : number(input) {}

BigInteger::BigInteger(int input) {
	if (input == 0) {
		number.push_back(0);
	}
	else {
		bool isPositive = input > 0;
		input = abs(input);
		while (input != 0) {
			number.push_back(input % 10);
			input /= 10;
		}
		std::reverse(number.begin(), number.end());
		if (!isPositive) number[0] *= (-1);
	}	
}

BigInteger::BigInteger(std::string input) : number(input[0] == '-' ? input.size() - 1 : input.size()){
	bool negative = false;
	std::vector<int>::iterator vecIter = number.begin();
	std::string::iterator stringIter = input.begin();

	if ((*stringIter) == '-') {
		negative = true;
		stringIter++;
	}

	for (; stringIter < input.end(); stringIter++, vecIter++) {
		*vecIter = (*stringIter - '0');
	}

	if (negative) {
		number[0] *= (-1);
	}
}

BigInteger::BigInteger(int* array, size_t size) : number(size){
	std::copy(array, array + size, number.begin());
}

BigInteger::BigInteger(const BigInteger &obj) {
	number = obj.number;
}

BigInteger::BigInteger() {}

BigInteger::~BigInteger(){
	
}

int BigInteger::absCompare(BigInteger rHand) const {
	return absCompare(rHand.number);
}

size_t BigInteger::getSize() const {
	return number.size();
}

bool BigInteger::isNegative() const {
	return number[0] < 0;
}

void BigInteger::add(BigInteger rHand) {
	number = add2(number, rHand.number);
}

void BigInteger::subtract(BigInteger rHand) {
	number = subtract2(number, rHand.number);
}

void BigInteger::multiply(BigInteger rHand) {
	if ((number.size() == 1 && number[0] == 0) || (rHand.number.size() == 1 && rHand.number[0] == 0)) {
		number = std::vector<int>(1);
	}

	number = multiplyBySingleDigit2(number, rHand.number);
	
}

void BigInteger::printNumber() {
	for (std::vector<int>::iterator iter = number.begin(); iter < number.end(); iter++) {
		std::cout << *iter;
	}
}

