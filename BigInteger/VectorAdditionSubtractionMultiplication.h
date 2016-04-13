#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <math.h>

std::vector<int> add2(std::vector<int> lHand, std::vector<int> rHand);
std::vector<int> addPositiveAndPositive2(std::vector<int> lHand, std::vector<int> rHand);
std::vector<int> subtract2(std::vector<int> lHand, std::vector<int> rHand);
std::vector<int> subtractNegativeFromNegative2(std::vector<int> lHand, std::vector<int> rHand, int isLHandAbsBigger);
std::vector<int> subtractPositiveFromPositive2(std::vector<int> lHand, std::vector<int> rHand, int isLHandAbsBigger);
std::vector<int> multiply2(std::vector<int> lHand, std::vector<int> rHand);
std::vector<int> multiplyBySingleDigit2(std::vector<int> lHand, std::vector<int> rHand);
std::vector<int> shiftLeftByN(std::vector<int> input, int n);
std::vector<int> multiply3(std::vector<int> lHand, std::vector<int> rHand);
