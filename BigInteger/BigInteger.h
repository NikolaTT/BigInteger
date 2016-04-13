#ifndef BIG_INTEGER_TOSHEV
#define BIG_INTEGER_TOSHEV

#include <string>
#include <vector>
#include "VectorAdditionSubtractionMultiplication.h"

class BigInteger
{
public:
	BigInteger();
	BigInteger(std::string);
	BigInteger(std::vector<int>);
	BigInteger(int* array, size_t size);
	BigInteger(const BigInteger &obj);
	BigInteger(int);
	~BigInteger();

	size_t getSize() const;
	bool isNegative() const;

	int absCompare(BigInteger rHand) const;
	void printNumber();

	void add(BigInteger rHand);

	void subtract(BigInteger rHand);
	void multiply(BigInteger rHand);


	template<typename T>
	int absCompare(std::vector<T>& rHand) const {
		if (number.size() > rHand.size()) return 1;
		else if (number.size() < rHand.size()) return -1;
		else {
			if (abs(number[0]) > abs(rHand[0])) return 1;
			else if (abs(number[0]) < abs(rHand[0])) return -1;
			else {
				std::vector<int>::const_iterator lHandIter = number.begin() + 1;
				std::vector<T>::const_iterator rHandIter = rHand.begin() + 1;

				for (; lHandIter < number.end(); lHandIter++, rHandIter++) {
					if (*lHandIter > *rHandIter) return 1;
					else if (*lHandIter < *rHandIter) return -1;
				}

				return 0;
			}
		}
	}

	template<typename T>
	void addPositiveAndPositive(std::vector<T>& rHand) {
		int carry = 0;
		std::vector<int> result(number.size() > rHand.size() ? number.size() : rHand.size());

		std::vector<int>::iterator lHandIter = number.end() - 1;
		std::vector<T>::iterator rHandIter = rHand.end() - 1;
		std::vector<int>::iterator resultIter = result.end() - 1;



		while (lHandIter > number.begin() && rHandIter > rHand.begin()) {
			*resultIter = (carry + *lHandIter + *rHandIter);
			carry = *resultIter / 10;
			*resultIter %= 10;

			lHandIter--;
			rHandIter--;
			resultIter--;
		}

		*resultIter = (carry + *lHandIter + *rHandIter);
		carry = *resultIter / 10;
		*resultIter %= 10;

		if (lHandIter != number.begin()) {
			lHandIter--;
			resultIter--;
			while (lHandIter > number.begin()) {
				*resultIter = (carry + *lHandIter);
				carry = *resultIter / 10;
				*resultIter %= 10;

				lHandIter--;
				resultIter--;
			}

			*resultIter = (carry + *lHandIter);
			carry = *resultIter / 10;
			*resultIter %= 10;
		}

		else if (rHandIter != rHand.begin()) {
			rHandIter--;
			resultIter--;
			while (rHandIter > rHand.begin()) {
				*resultIter = (carry + *rHandIter);
				carry = *resultIter / 10;
				*resultIter %= 10;

				rHandIter--;
				resultIter--;
			}

			*resultIter = (carry + *rHandIter);
			carry = *resultIter / 10;
			*resultIter %= 10;
		}

		if (carry > 0) {
			result.insert(resultIter, carry);
		}

		number = result;
	}

	template<typename T> void subtract(std::vector<T>& rHand) {
		if (isNegative() && rHand[0] > 0) {
			number[0] *= (-1);
			add(rHand);
			number[0] *= (-1);
		}
		else if (!isNegative() && rHand[0] < 0) {
			rHand[0] *= (-1);
			add(rHand);
		}
		else {
			int absComp = absCompare(rHand);

			if (absComp == 0) number = std::vector<int>(1);

			else {
				if (!isNegative() && rHand[0] > 0) {
					subtractPositiveFromPositive(rHand, absComp);
				}
				else {
					subtractNegativeFromNegative(rHand, absComp);
				}
			}

		}
	}


private:
	std::vector<int> number;
	
	template<typename T>
	BigInteger multiplyByVector(std::vector<T> rHand) {

		return *this;
		/*if (number.size() < 2 || rHand.size() < 2) {
			multiplyBySingleDigit(rHand);
			return *this;
		}
		
		size_t num1Mid = number.size() / 2;
		size_t num2Mid = rHand.size() / 2;

		vector<int> low1 = vector<int>(num1.begin(), num1.begin() + num1Mid);
		vector<int> low2 = vector<int>(num2.begin(), num2.begin() + num2Mid);
		
		vector<int> high1 = vector<int>(num1.begin() + num1Mid, num1.end());
		vector<int> high2 = vector<int>(num2.begin() + num2Mid, num2.end());

		BigInteger low1BI(low1);
		BigInteger low2BI(low2);

		BigInteger high1BI(high1);
		BigInteger high1BI(high2);

		size_t m = max((num1.size() + 1) / 2, (num2.size() + 1) / 2);

		BigInteger high1z0 = karatsuba(low1, low2);
		BigInteger high1z1 = karatsuba(low1.add(high1), low2.add(high2));
		BigInteger high1z2 = karatsuba(high1, high2);

		return (z2.shiftLeft(m)) + ((z1 - z2 - z0).shiftLeft(m / 2)) + (z0)*/



		//vector<short> karatsuba(vector<short> num1, vector<short> num2) {
		//	/* calculates the size of the numbers */
		//	if (num1.Length < 2) or (num2.Length < 2) //Length < 2 means number < 10    
		//		return num1 * num2 //Might require another mult routine that multiplies the arrays by single digits
		//
		//	size_t num1Mid = num1.size() / 2;
		//	size_t num2Mid = num2.size() / 2;
		//
		//	vector<short> low1 = vector<short>(num1.begin(), num1.begin() + num1Mid);
		//	vector<short> low2 = vector<short>(num2.begin(), num2.begin() + num2Mid);
		//
		//	vector<short> high1 = vector<short>(num1.begin() + num1Mid, num1.end());
		//	vector<short> high2 = vector<short>(num2.begin() + num2Mid, num2.end());
		//
		//	size_t m = max((num1.size() + 1) / 2, (num2.size() + 1) / 2);
		//
		//
		//		/* 3 calls made to numbers approximately half the size */
		//	vector<short> high1z0 = karatsuba(low1, low2);
		//	vector<short> high1z1 = karatsuba(low1.add(high1), low2.add(high2));
		//	vector<short> high1z2 = karatsuba(high1, high2);
		//
		//		//Note: In general x * 10 ^ y in this case is simply a left-shift
		//		//      of the digits in the 'x' array y-places. i.e. 4 * 10 ^ 3
		//		//      results in the array x[4] = { 4, 0, 0, 0 }
		//	z1.subtract(z2);
		//	z1.subtract(z0);
		//	return (z2.shiftLeft(m)) + (z1.shiftLeft(m / 2)) + (z0);
		//}
		//
		//if (num1.Length < 2) or (num2.Length < 2) //Length < 2 means number < 10    
		//	return num1 * num2 //Might require another mult routine that multiplies the arrays by single digits
	}

	
	template<typename T>
	void multiplyBySingleDigit(std::vector<T>& rHand) {
		int carry = 0;
		std::vector<int> resVector = std::vector<int>(getSize() + rHand.size() - 1);
		
		std::vector<int>::const_iterator lHandIter = number.end();
		std::vector<T>::const_iterator rHandIter = rHand.end();
		std::vector<int>::iterator resIter = resVector.begin();

		size_t pos1 = getSize();
		size_t pos2 = rHand.size();

		while (lHandIter > number.begin()) {
			lHandIter--;
			pos1--;
			rHandIter = rHand.end();
			pos2 = rHand.size();
			while (rHandIter > rHand.begin()) {
				rHandIter--;
				pos2--;
				*(resIter + pos1 + pos2) += (*lHandIter) * (*rHandIter);
			}
		}

		resIter = resVector.end();
		while (resIter > resVector.begin()) {
			*(--resIter) += carry;
			carry = *resIter / 10;
			*resIter %= 10;
		}
		
		if (carry > 0) {
			resVector.insert(resVector.begin(), carry);
		}

		number = resVector;
	}

	template<typename T>
	void subtractNegativeFromNegative(std::vector<T>& rHand, int isLHandAbsBigger) {
		number[0] *= -1;
		rHand[0] *= -1;
		subtractPositiveFromPositive(rHand, isLHandAbsBigger);
		number[0] *= -1;
	}

	
	template<typename T>
	void subtractPositiveFromPositive(std::vector<T>& rHand, int isLHandAbsBigger) {
		
		int carry = 0;
		size_t resSize = number.size() > rHand.size() ? number.size() : rHand.size();
		std::vector<int> resVector(resSize);

		std::vector<int>::const_iterator lHandIter = number.end() - 1;
		std::vector<T>::const_iterator rHandIter = rHand.end() - 1;
		std::vector<int>::iterator resIter = resVector.end() - 1;

		//algorithm is for LPositive and RPositive,
		//might need other function for LNegative and RNegative
		if (isLHandAbsBigger == 1) {
			while (lHandIter > number.begin() && rHandIter > rHand.begin()) {
				*resIter = *lHandIter - *rHandIter + carry;
				if (*resIter < 0) carry = -1;
				else carry = 0;
				*resIter += 10;
				*resIter %= 10;
				
				lHandIter--;
				rHandIter--;
				resIter--;
			}

			*resIter = *lHandIter - *rHandIter + carry;
			if (*resIter < 0) carry = -1;
			else carry = 0;
			*resIter += 10;
			*resIter %= 10;

			while (lHandIter > number.begin()) {
				lHandIter--;
				resIter--;

				*resIter = *lHandIter + carry;
				if (*resIter < 0) carry = -1;
				else carry = 0;
				*resIter += 10;
				*resIter %= 10;
			}


			/*while (rHandIter > rHand.begin()) {
				rHandIter--;
				resIter--;

				*resIter = (-1)*(*rHandIter) + carry;
				if (*resIter < 0) {
					carry = -1;
					*resIter *= -1;
				}
				else carry = 0;
			}*/
			
			number = resVector;
			std::vector<int>::iterator iter = number.begin();
			while (*iter++ == 0);
			number = std::vector<int>(--iter, number.end());
		}
		else if(isLHandAbsBigger == -1){
			while (lHandIter > number.begin() && rHandIter > rHand.begin()) {
				*resIter = *lHandIter - *rHandIter + carry;
				if (*resIter > 0) carry = 1;
				else carry = 0;
				*resIter = 10 - *resIter;
				*resIter %= 10;
				

				lHandIter--;
				rHandIter--;
				resIter--;
			}

			*resIter = *lHandIter - *rHandIter + carry;
			if (*resIter > 0) carry = 1;
			else carry = 0;
			*resIter = 10 - *resIter;
			*resIter %= 10;

			/*while (lHandIter > number.begin()) {
				lHandIter--;
				resIter--;

				*resIter = *lHandIter + carry;
				if (*resIter < 0) carry = -1;
				else carry = 0;
			}*/

			while (rHandIter > rHand.begin()) {
				rHandIter--;
				resIter--;

				*resIter = (-1)*(*rHandIter) + carry;
				if (*resIter > 0) carry = 1;
				else carry = 0;
				*resIter = 10 - *resIter;
				*resIter %= 10;
			}

			number = resVector;
			std::vector<int>::iterator iter = number.begin();
			while (*iter++ == 0);
			number = std::vector<int>(--iter, number.end());
			number[0] *= -1;
		}
	}
	
	
	
	
	
	
	friend class BigInteger;
};





#endif












//int carry = 0;
//rHand[0] *= (-1);
//size_t resSize = number.size() > rHand.size() ? number.size() : rHand.size();
//std::vector<short> resVector(resSize);
//
//std::vector<short>::const_iterator lHandIter = number.end() - 1;
//std::vector<T>::const_iterator rHandIter = rHand.end() - 1;
//std::vector<short>::iterator resIter = resVector.end() - 1;
//
////algorithm is for LPositive and RPositive,
////might need other function for LNegative and RNegative
//if (isLHandAbsBigger == -1) {
//	while (lHandIter > number.begin() && rHandIter > rHand.begin()) {
//		*resIter = (-1)*(*lHandIter) + *rHandIter + carry;
//		if (*resIter < 0) carry = -1;
//		else carry = 0;
//		*resIter += 10;
//		*resIter %= 10;
//
//		lHandIter--;
//		rHandIter--;
//		resIter--;
//	}
//
//	*resIter = (-1)*(*lHandIter) + *rHandIter + carry;
//	if (*resIter < 0) carry = -1;
//	else carry = 0;
//	*resIter += 10;
//	*resIter %= 10;
//
//	/*while (lHandIter > number.begin()) {
//	lHandIter--;
//	resIter--;
//
//	*resIter = (-1)*(*lHandIter) + carry;
//	if (*resIter < 0) carry = -1;
//	else carry = 0;
//	*resIter += 10;
//	*resIter %= 10;
//	}*/
//
//
//	while (rHandIter > rHand.begin()) {
//		rHandIter--;
//		resIter--;
//
//		*resIter = (*rHandIter) + carry;
//		if (*resIter < 0) {
//			carry = -1;
//			*resIter *= -1;
//		}
//		else carry = 0;
//	}
//
//	number = resVector;
//	std::vector<short>::iterator iter = number.begin();
//	while (*iter++ == 0);
//	number = std::vector<short>(--iter, number.end());
//}
//else if (isLHandAbsBigger == 1) {
//	while (lHandIter > number.begin() && rHandIter > rHand.begin()) {
//		*resIter = (-1)*(*lHandIter) + *rHandIter + carry;
//		if (*resIter > 0) carry = 1;
//		else carry = 0;
//		*resIter = 10 - *resIter;
//		*resIter %= 10;
//
//
//		lHandIter--;
//		rHandIter--;
//		resIter--;
//	}
//
//	*resIter = (-1)*(*lHandIter) + *rHandIter + carry;
//	if (*resIter > 0) carry = 1;
//	else carry = 0;
//	*resIter = 10 - *resIter;
//	*resIter %= 10;
//
//	while (lHandIter > number.begin()) {
//		lHandIter--;
//		resIter--;
//
//		*resIter = (-1)*(*lHandIter) + carry;
//		if (*resIter < 0) carry = -1;
//		else carry = 0;
//	}
//
//	/*while (rHandIter > rHand.begin()) {
//	rHandIter--;
//	resIter--;
//
//	*resIter = (*rHandIter) + carry;
//	if (*resIter > 0) carry = 1;
//	else carry = 0;
//	*resIter = 10 - *resIter;
//	*resIter %= 10;
//	}*/
//
//	number = resVector;
//	std::vector<short>::iterator iter = number.begin();
//	while (*iter++ == 0);
//	number = std::vector<short>(--iter, number.end());
//	number[0] *= -1;
//}