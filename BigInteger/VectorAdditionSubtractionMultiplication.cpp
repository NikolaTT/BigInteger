#include "VectorAdditionSubtractionMultiplication.h"

int absCompare2(std::vector<int> lHand, std::vector<int> rHand) {
	if (lHand.size() > rHand.size()) return 1;
	else if (lHand.size() < rHand.size()) return -1;
	else {
		if (abs(lHand[0]) > abs(rHand[0])) return 1;
		else if (abs(lHand[0]) < abs(rHand[0])) return -1;
		else {
			std::vector<int>::const_iterator lHandIter = lHand.begin() + 1;
			std::vector<int>::const_iterator rHandIter = rHand.begin() + 1;

			for (; lHandIter < lHand.end(); lHandIter++, rHandIter++) {
				if (*lHandIter > *rHandIter) return 1;
				else if (*lHandIter < *rHandIter) return -1;
			}

			return 0;
		}
	}
}

std::vector<int> add2(std::vector<int> lHand, std::vector<int> rHand) {
	if (!(lHand[0] < 0) && rHand[0]< 0) {
		rHand[0] *= -1;
		return subtract2(lHand, rHand);
	}
	else if (lHand[0] < 0 && rHand[0] < 0) {
		rHand[0] *= -1;
		return subtract2(lHand, rHand);
	}
	else if (lHand[0] < 0 && !(rHand[0] < 0)) {
		rHand[0] *= -1;
		return subtract2(lHand, rHand);
	}
	else {
		return addPositiveAndPositive2(lHand, rHand);
	}
}

std::vector<int> addPositiveAndPositive2(std::vector<int> lHand, std::vector<int> rHand) {
	int carry = 0;
	std::vector<int> result(lHand.size() > rHand.size() ? lHand.size() : rHand.size());

	std::vector<int>::iterator lHandIter = lHand.end() - 1;
	std::vector<int>::iterator rHandIter = rHand.end() - 1;
	std::vector<int>::iterator resultIter = result.end() - 1;



	while (lHandIter > lHand.begin() && rHandIter > rHand.begin()) {
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

	if (lHandIter != lHand.begin()) {
		lHandIter--;
		resultIter--;
		while (lHandIter > lHand.begin()) {
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

	return result;
}

std::vector<int> subtract2(std::vector<int> lHand, std::vector<int> rHand) {
	if (lHand[0] < 0 && rHand[0] > 0) {
		lHand[0] *= (-1);
		return add2(lHand, rHand);
		lHand[0] *= (-1);
	}
	else if (!(lHand[0] < 0) && rHand[0] < 0) {
		rHand[0] *= (-1);
		return add2(lHand, rHand);
	}
	else {
		int absComp = absCompare2(lHand, rHand);

		if (absComp == 0) return std::vector<int>(1);

		else {
			if (!(lHand[0] < 0) && rHand[0] > 0) {
				return subtractPositiveFromPositive2(lHand, rHand, absComp);
			}
			else {
				return subtractNegativeFromNegative2(lHand, rHand, absComp);
			}
		}

	}
}

std::vector<int> subtractNegativeFromNegative2(std::vector<int> lHand, std::vector<int> rHand, int isLHandAbsBigger) {
	lHand[0] *= -1;
	rHand[0] *= -1;
	std::vector<int> temp = subtractPositiveFromPositive2(lHand, rHand, isLHandAbsBigger);
	temp[0] *= -1;
	return temp;
}

std::vector<int> subtractPositiveFromPositive2(std::vector<int> lHand, std::vector<int> rHand, int isLHandAbsBigger) {

	int carry = 0;
	size_t resSize = lHand.size() > rHand.size() ? lHand.size() : rHand.size();
	std::vector<int> resVector(resSize);

	std::vector<int>::const_iterator lHandIter = lHand.end() - 1;
	std::vector<int>::const_iterator rHandIter = rHand.end() - 1;
	std::vector<int>::iterator resIter = resVector.end() - 1;

	//algorithm is for LPositive and RPositive,
	//might need other function for LNegative and RNegative
	if (isLHandAbsBigger == 1) {
		while (lHandIter > lHand.begin() && rHandIter > rHand.begin()) {
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

		while (lHandIter > lHand.begin()) {
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

		std::vector<int>::iterator iter = resVector.begin();
		while (*iter++ == 0);
		resVector = std::vector<int>(--iter, resVector.end());
		return resVector;
	}
	else if (isLHandAbsBigger == -1) {
		while (lHandIter > lHand.begin() && rHandIter > rHand.begin()) {
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

		/*while (lHandIter > lHand.begin()) {
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

		std::vector<int>::iterator iter = resVector.begin();
		while (*iter++ == 0);
		resVector = std::vector<int>(--iter, resVector.end());
		resVector[0] *= -1;

		return resVector;
	}

	return std::vector<int>(1);
}

std::vector<int> multiply3(std::vector<int> lHand, std::vector<int> rHand) {
	return std::vector<int>(0);
}

std::vector<int> multiply2(std::vector<int> lHand, std::vector<int> rHand) {
	bool makeNegative = (lHand[0] < 0 && rHand[0] > 0) || (!(lHand[0] < 0) && rHand[0] < 0);
	std::vector<int> temp;

	lHand[0] = abs(lHand[0]);
	rHand[0] = abs(rHand[0]);

	if (lHand.size() < 2 || rHand.size() < 2) {
		temp = multiplyBySingleDigit2(lHand, rHand); 
		if (makeNegative) temp[0] *= -1;
		return temp;
	}
	
	size_t lHandMid = lHand.size() / 2;
	size_t rHandMid = rHand.size() / 2;
		
		
	std::vector<int> low1 = std::vector<int>(lHand.begin(), lHand.begin() + lHandMid);
	std::vector<int> low2 = std::vector<int>(rHand.begin(), rHand.begin() + rHandMid);
		
	std::vector<int> high1 = std::vector<int>(lHand.begin() + lHandMid, lHand.end());
	std::vector<int> high2 = std::vector<int>(rHand.begin() + rHandMid, rHand.end());
		
	size_t m = std::max((lHand.size() + 1) / 2, (rHand.size() + 1) / 2);
		
		
		/* 3 calls made to numbers approximately half the size */
	std::vector<int> z0 = multiply2(low1, low2);
	std::vector<int> z1 = multiply2(add2(low1, high1), add2(low2, high2));
	std::vector<int> z2 = multiply2(high1, high2);
		
		//Note: In general x * 10 ^ y in this case is simply a left-shift
		//      of the digits in the 'x' array y-places. i.e. 4 * 10 ^ 3
		//      results in the array x[4] = { 4, 0, 0, 0 }

	std::vector<int> z4 = subtract2(z1, z2);
	z4 = subtract2(z4, z0);
	z4 = shiftLeftByN(z4, m);

	z2 = shiftLeftByN(z2, 2*m);
	
	

	z2 = add2(z2, z4);
	z2 = add2(z2, z0);

	if (makeNegative) z2[0] *= -1;

	return z2;
	/*
	return (z2.shiftLeft(m)) + ((z1 - z2 - z0).shiftLeft(m / 2)) + (z0)


	return std::vector<int>(1);*/
}

std::vector<int> multiplyBySingleDigit2(std::vector<int> lHand, std::vector<int> rHand) {
	bool makeNegative = (lHand[0] < 0 && rHand[0] > 0) || (!(lHand[0] < 0) && rHand[0] < 0);
	
	lHand[0] = abs(lHand[0]);
	rHand[0] = abs(rHand[0]);

	int carry = 0;
	std::vector<int> resVector = std::vector<int>(lHand.size() + rHand.size() - 1);

	std::vector<int>::const_iterator lHandIter = lHand.end();
	std::vector<int>::const_iterator rHandIter = rHand.end();
	std::vector<int>::iterator resIter = resVector.begin();

	size_t pos1 = lHand.size();
	size_t pos2 = rHand.size();

	while (lHandIter > lHand.begin()) {
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

	if (makeNegative) resVector[0] *= -1;

	return resVector;
}

std::vector<int> shiftLeftByN(std::vector<int> input, int n) {
	std::vector<int> temp = input;
	for (int i = 0; i < n; i++) {
		temp.push_back(0);
	}
	return temp;
}