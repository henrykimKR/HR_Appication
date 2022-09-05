/*********************************
 *      DBS 211 Milestone #02
 *********************************
 *     Group: 11
 *      Name: Chun-Yi Kuo
 *			  Jeff Ty
 *            Seong Hoon Kim
 *      Date: 2022-08-05
 *********************************/

#pragma once
#ifndef UTIL_H
#include <string>

namespace dbs
{
	// Input Int in range from upper to lower (both inclusively)
	int inputIntRange(int upper, int lower);
	// Check if input is digit.
	bool isDigit(const std::string& str);
	// Clear cin Buffer
	void clearBuffer();
}
#endif // !UTIL_H
