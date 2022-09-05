/*********************************
 *      DBS 211 Milestone #02
 *********************************
 *     Group: 11
 *      Name: Chun-Yi Kuo
 *			  (143760213)
 *			  Jeff Ty
 *            (159725217)
 *			  Seong Hoon Kim 
 *			  (143080216)
 *      Date: 2022-08-05
 *********************************/

#include <iostream>
#include <iomanip>
#include <occi.h>
#include "Menu.h"
#include "Employee.h"

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;
using namespace dbs;

int main(void)
{
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;

	/* Used Variables */
	string str;
	string user = "dbs211_222g13";
	string pass = "97161400";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		cout << "******************************" << endl;
		cout << "** DBS211 NGG Final Project **" << endl;
		cout << "******************************" << endl;
		cout << "**         Group 11         **" << endl;
		cout << "** ------------------------ **" << endl;
		cout << "**        Chun-Ti Kuo       **" << endl;
		cout << "**        (143760213)       **" << endl;
		cout << "**          Jeff Ty         **" << endl;
		cout << "**        (159725217)       **" << endl;
		cout << "**      Seong Hoon Kim      **" << endl;
		cout << "**        (143080216)       **" << endl;
		cout << "******************************" << endl << endl;

		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);
		cout << "Connection is Successful!" << endl << endl;

		Employee emp{};
		int employeeNumber = 0;
		int select = 0;
		do
		{
			select = menu();

			switch (select)
			{
			case 1:
				displayEmployee(conn, emp);
				break;
			case 2:
				displayAllEmployees(conn);
				break;
			case 3:
				getEmployee(&emp);
				insertEmployee(conn, emp);
				break;
			case 4:
				employeeNumber = getEmployeeNumber();
				updateEmployee(conn, employeeNumber);
				break;
			case 5:
				employeeNumber = getEmployeeNumber();
				deleteEmployee(conn, employeeNumber);
				break;
			case 0:
				cout << endl << "Exit" << endl;
				break;
			default:
				break;
			}
		} while (select);

		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		auto errCode = sqlExcp.getErrorCode();
		auto errMsg = sqlExcp.getMessage();
		cout << "[Error] " << errCode << " : " << errMsg << endl;
	}

	cin.ignore(1000, '\n');
	cin.get();
	return 0;
}
