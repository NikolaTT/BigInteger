#ifndef BIG_INTEGER_TOSHEV
#define BIG_INTEGER_TOSHEV

#include <string>
#include <vector>

class BigInteger
{
public:
	BigInteger();
	BigInteger(std::string);
	BigInteger(std::vector<short>);
	BigInteger(short* array, size_t size);
	BigInteger(const BigInteger &obj);
	~BigInteger();

	size_t getSize() const;
	bool isNegative() const;

	template<typename T>
	int absCompare(std::vector<T>& rHand) const {
		if (number.size() > rHand.size()) return 1;
		else if (number.size() < rHand.size()) return -1;
		else {
			if (abs(number[0]) > abs(rHand[0])) return 1;
			else if (abs(number[0] < abs(rHand[0]))) return -1;
			else {
				std::vector<short>::const_iterator lHandIter = number.begin() + 1;
				std::vector<T>::const_iterator rHandIter = rHand.begin() + 1;

				for (; lHandIter < number.end(); lHandIter++, rHandIter++) {
					if (*lHandIter > *rHandIter) return 1;
					else if (*lHandIter < *rHandIter) return -1;
				}

				return 0;
			}
		}
	}

	int absCompare(BigInteger rHand) const;

	void printNumber();

	template<typename T>
	void add(std::vector<T>& rHand) {
		short carry = 0;
		std::vector<short> result(number.size() > rHand.size() ? number.size() : rHand.size());

		std::vector<short>::iterator lHandIter = number.end() - 1;
		std::vector<T>::iterator rHandIter = rHand.end() - 1;
		std::vector<short>::iterator resultIter = result.end() - 1;



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

	void add(BigInteger rHand);
	template<typename T> void subtract(std::vector<T> rHand);
	void subtract(BigInteger rHand);
	void multiply(BigInteger rHand);



private:
	std::vector<short> number;

	friend class BigInteger;
};

























#endif