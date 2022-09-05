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
#include <iomanip>
#include <string>
#include <vector>
#include "Employee.h"
#include "Util.h"

using namespace std;
using namespace oracle::occi;


namespace dbs
{
	int findEmployee(Connection* conn, int employeeNumber, Employee* emp)
	{
		int exist = true;

		string query =
			"SELECT "
			"e.employeenumber, "
			"e.lastname, "
			"e.firstname, "
			"e.email, "
			"o.phone, "
			"e.extension, "
			"er.firstname || ' ' || er.lastname AS managername, "
			"e.jobtitle, "
			"o.city "
			"FROM dbs211_employees e "
			"LEFT JOIN dbs211_employees er "
			"ON e.reportsto = er.employeenumber "
			"LEFT JOIN dbs211_offices o "
			"ON e.officecode = o.officecode "
			"WHERE e.employeenumber = '" + to_string(employeeNumber) + "' ";
		try {
			Statement* stmt = conn->createStatement(query);
			ResultSet* rs = stmt->executeQuery();

			if (!rs->next())
			{
				exist = false;
			}
			else
			{
				memset(emp, 0, sizeof Employee);

				emp->employeeNumber = rs->getInt(1);
				rs->getString(2).copy(emp->lastName, 50);
				rs->getString(3).copy(emp->firstName, 50);
				rs->getString(4).copy(emp->email, 100);
				rs->getString(5).copy(emp->phone, 50);
				rs->getString(6).copy(emp->extension, 10);
				rs->getString(7).copy(emp->reportsTo, 100);
				rs->getString(8).copy(emp->jobTitle, 50);
				rs->getString(9).copy(emp->city, 50);
			}
			conn->terminateStatement(stmt);
		}
		catch (SQLException& sqlExcp)
		{
			auto errCode = sqlExcp.getErrorCode();
			auto errMsg = sqlExcp.getMessage();
			cout << "[Error] " << errCode << " : " << errMsg
				<< "@ findEmployee" << endl;

			exist = false;
		}
		catch (exception& excp)
		{
			cout << excp.what() << endl;
		}

		return exist;
	}

	void displayEmployee(Connection* conn, Employee emp)
	{
		string employeeNum;
		cout << "Enter Employee Number: ";
		cin >> employeeNum;
		cin.ignore(1000, '\n');

		if (!isDigit(employeeNum))
		{
			cout << "[Error] Employee Number Format Error: Only Digits Allowed" << endl;
		}
		else
		{
			int exist = findEmployee(conn, stoi(employeeNum), &emp);
			if (exist)
			{
				cout << endl
					<< left << setw(15) << "employeeNumber"
					<< "= " << emp.employeeNumber << endl
					<< left << setw(15) << "lastName"
					<< "= " << emp.lastName << endl
					<< left << setw(15) << "firstName"
					<< "= " << emp.firstName << endl
					<< left << setw(15) << "email"
					<< "= " << emp.email << endl
					<< left << setw(15) << "phone"
					<< "= " << emp.phone << endl
					<< left << setw(15) << "extension"
					<< "= " << emp.extension << endl
					<< left << setw(15) << "reportsTo"
					<< "= " << emp.reportsTo << endl
					<< left << setw(15) << "jobTitle"
					<< "= " << emp.jobTitle << endl
					<< left << setw(15) << "city"
					<< "= " << emp.city << endl;
			}
			else
			{
				cout << endl
					<< "Employee " << employeeNum
					<< " does not exist." << endl;
			}
		}
		cout << endl;
	}

	void displayEmployeeTable(const Employee& emp)
	{
		string name = string(emp.firstName) + " " + string(emp.lastName);
		cout << "  "
			<< setw(5) << emp.employeeNumber << " "
			<< setw(20) << left << name << " "
			<< setw(33) << left << emp.email << " "
			<< setw(17) << left << emp.phone << " "
			<< setw(8) << left << emp.extension << " "
			<< emp.reportsTo << endl;
	}

	void displayEmployeeHeader()
	{
		cout << setw(110) << setfill('-') << "-" << setfill(' ') << endl;
		cout << "  "
			<< setw(5) << left << "E" << " "
			<< setw(20) << left << "Employee Name" << " "
			<< setw(33) << left << "Email" << " "
			<< setw(17) << left << "Phone" << " "
			<< setw(8) << left << "Ext" << " "
			<< "Manaager" << endl;
		cout << setw(110) << setfill('-') << "-" << setfill(' ') << endl;
	}


	void displayAllEmployees(Connection* conn)
	{
		// Get all employee number
		vector<int> empNum;
		string query =
			"SELECT emp.employeenumber "
			"from dbs211_employees emp";
		try
		{
			Statement* stmt = conn->createStatement(query);
			ResultSet* rs = stmt->executeQuery();
			if (!rs->next())
			{
				cout << "[Error] No Employee Exist" << endl;
			}
			else
			{
				do {
					empNum.push_back(rs->getInt(1));
				} while (rs->next());
			}
			if (empNum.empty())
			{
				cout << "[Error] No Employee Exist" << endl;
			}
			conn->terminateStatement(stmt);
		}
		catch (SQLException& sqlExcp) {
			auto errCode = sqlExcp.getErrorCode();
			auto errMsg = sqlExcp.getMessage();
			cout << "[Error] " << errCode << " : " << errMsg << endl;
		}

		Employee emp{};
		displayEmployeeHeader();
		for (auto it = empNum.begin(); it != empNum.end(); it++)
		{
			int status = findEmployee(conn, *it, &emp);
			if (status)
			{
				displayEmployeeTable(emp);
			}
		}
		cout << endl;
	}


	void getEmployee(Employee* emp)
	{
		cout << endl << "************ New Employee Information *************" << endl;
		cout << "Employee Number: ";
		cin >> emp->employeeNumber;
		cout << "Last Name: ";
		cin >> emp->lastName;
		cout << "First Name: ";
		cin >> emp->firstName;
		cout << "Extenstion: ";
		cin >> emp->extension;
		cout << "Email: ";
		cin >> emp->email;
		cin.ignore();
		cout << "Job Title: ";
		cin.getline(emp->jobTitle, 49);
		cout << "City: ";
		cin >> emp->city;
		cout << endl;
	}

	void insertEmployee(Connection* conn, Employee emp)
	{
		Employee tmp{};
		if (!findEmployee(conn, emp.employeeNumber, &tmp))
		{
			string query = 
				"INSERT INTO dbs211_employees(employeenumber, lastname, "
				"firstname, extension, email, officecode, reportsto, jobtitle) "
				"VALUES(:1, :2, :3, :4, :5, '1', 1002, :6)";

			try {
				// Start a INSERT trasaction
				Statement* stmt = conn->createStatement();
				// Set SQL parameters
				stmt->setSQL(query);
				stmt->setInt(1, emp.employeeNumber);
				stmt->setString(2, emp.lastName);
				stmt->setString(3, emp.firstName);
				stmt->setString(4, emp.extension);
				stmt->setString(5, emp.email);
				stmt->setString(6, emp.jobTitle);
				stmt->executeUpdate();
				// Commit Change
				conn->commit();
				conn->terminateStatement(stmt);

				cout << "The new employee is added successfully." << endl << endl;
			}
			catch (SQLException& sqlExp)
			{
				// print error msg
				auto errCode = sqlExp.getErrorCode();
				auto errMsg = sqlExp.getMessage();
				cout << "[Error] " << errCode << " : " << errMsg << endl;

				// rollback transaction
				conn->rollback();
			}
		}
		else
		{
			cout << endl
				<< "An employee with the same employee number exists."
				<< endl << endl;
		}
	}

	void updateEmployee(Connection* conn, int employeeNumber)
	{
		Employee emp{};
		if (findEmployee(conn, employeeNumber, &emp))
		{
			string extension;
			cout << "New Extension: ";
			cin >> extension;
			clearBuffer();

			string query =
				"UPDATE dbs211_employees "
				"SET extension ='" + extension + "' "
				"WHERE employeenumber = " + to_string(employeeNumber);
			
			try {
				// start a insert transaction
				Statement* stmt = conn->createStatement();
				stmt->execute(query);

				// commit if no error
				conn->commit();
				conn->terminateStatement(stmt);

				cout << endl
					<< "Employee Number " << employeeNumber
					<< " is updated."
					<< endl << endl;

			}
			catch (SQLException& sqlExp)
			{
				// print error msg
				auto errCode = sqlExp.getErrorCode();
				auto errMsg = sqlExp.getMessage();
				cout << "[Error] " << errCode << " : " << errMsg << endl;

				// rollback transaction
				conn->rollback();
			}
		}
		else
		{
			cout << endl 
				<< "Employee Number " << employeeNumber
				<< " does not exist."
				<< endl << endl;
		}
	}

	int getEmployeeNumber()
	{
		int employeeNumber = 0;
		cout << "Employee Number: ";
		cin >> employeeNumber;
		clearBuffer();

		return employeeNumber;
	}

	void deleteEmployee(Connection* conn, int employeeNumber)
	{
		string query = "DELETE FROM dbs211_employees WHERE employeenumber = :1";
		Employee emp{};
		// Check employee exist
		int exist = findEmployee(conn, employeeNumber, &emp);
		if (exist)
		{
			try {
				Statement* stmt = conn->createStatement();
				stmt->setSQL(query);
				stmt->setInt(1, employeeNumber);
				stmt->executeUpdate();

				// commit if no error
				conn->commit();
				conn->terminateStatement(stmt);

				cout << endl
					<< "The employee is deleted"
					<< endl;
			}
			catch (SQLException& sqlExcp) {
				// print error message
				auto errCode = sqlExcp.getErrorCode();
				auto errMsg = sqlExcp.getMessage();
				cout << "[Error] " << errCode << " : " << errMsg << endl;

				// rollback transaction
				conn->rollback();
			}
		}
		else
		{
			cout << endl
				<< "Employee " << employeeNumber
				<< " does not exist." << endl;
		}
		cout << endl;
	}
}