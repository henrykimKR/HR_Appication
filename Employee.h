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
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <occi.h>

using namespace oracle::occi;
using namespace std;

namespace dbs
{

	typedef struct Employee
	{
		int employeeNumber;
		char lastName[50];
		char firstName[50];
		char email[100];
		char phone[50];
		char extension[10];
		char reportsTo[100];
		char jobTitle[50];
		char city[50];
	}Employee;

	int findEmployee(Connection* conn, int employeeNumber, Employee* emp);
	void displayEmployee(Connection* conn, Employee emp);
	void displayEmployeeTable(const Employee& emp);
	void displayEmployeeHeader();
	void displayAllEmployees(Connection* conn);

	void getEmployee(Employee* emp);
	void insertEmployee(Connection* conn, Employee emp);

	void updateEmployee(Connection* conn, int employeeNumber);

	int getEmployeeNumber();
	void deleteEmployee(Connection* conn, int employeeNumber);
}		
#endif // !EMPLOYEE_H
