/*********************************
 *      DBS 211 Milestone #02
 *********************************
 *     Group: 11
 *      Name: Chun-Yi Kuo
 *			  Jeff Ty
 *            Seong Hoon Kim
 *      Date: 2022-08-05
 *********************************/

#include <string>
#include <iostream>
#include "Util.h"

using namespace std;

namespace dbs
{
	int inputIntRange(int upper, int lower)
	{
		int select = -1;
		bool flag = true;

		while (flag)
		{
			cin >> select;
			if (cin.fail())
			{
				cout << "Invalid format. Please input number between "
					<< lower
					<< " and "
					<< upper
					<< " : ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (select > upper || select < lower)
			{
				cout << "Out of range. Please input number between "
					<< lower
					<< " and "
					<< upper
					<< " : ";
			}
			else
			{
				flag = false;
			}
		}

		return select;
	}

	bool isDigit(const string& str)
	{
		return str.find_first_not_of("0123456789") == string::npos;
	}

	void clearBuffer()
	{
		if (cin.fail())
			cin.clear();
		cin.ignore(1000, '\n');
	}

}