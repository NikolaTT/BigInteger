#include "BigInteger.h"
#include <iostream>
#include <string>
#include <iterator>
#include <math.h>

BigInteger::BigInteger(std::vector<short> input) : number(input) {}

BigInteger::BigInteger(std::string input) : number(input[0] == '-' ? input.size() - 1 : input.size()){
	bool negative = false;
	std::vector<short>::iterator vecIter = number.begin();
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

BigInteger::BigInteger(short* array, size_t size) : number(size){
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
	add(rHand.number);
}


void BigInteger::subtract(BigInteger rHand) {
	if (isNegative() && rHand.isNegative()) {
		std::vector<short> temp = rHand.number;
		temp[0] *= (-1);
		number[0] *= (-1);
		add(temp);
		number[0] *= (-1);
	}
	else {
		
	}
}

void BigInteger::multiply(BigInteger rHand) {

}

void BigInteger::printNumber() {
	for (std::vector<short>::iterator iter = number.begin(); iter < number.end(); iter++) {
		std::cout << *iter;
	}
}

