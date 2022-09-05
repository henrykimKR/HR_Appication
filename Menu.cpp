/*********************************
 *      DBS 211 Milestone #02
 *********************************
 *     Group: 11
 *      Name: Chun-Yi Kuo
 *			  Jeff Ty
 *            Seong Hoon Kim
 *      Date: 2022-08-05
 *********************************/

#include <iostream>
#include <string>
#include "Menu.h"
#include "Util.h"

using namespace std;

namespace dbs
{
	int menu()
	{
		int select = -1;
		cout << "********************* HR Menu *********************" << endl;
		cout << "1) Find Employee" << endl
			<< "2) Employee Report" << endl
			<< "3) Add Employee" << endl
			<< "4) Update Employee" << endl
			<< "5) Remove Employee" << endl
			<< "0) Exit" << endl;
		cout << "Please enter your select: ";
		select = inputIntRange(5, 0);

		return select;
	}
}

