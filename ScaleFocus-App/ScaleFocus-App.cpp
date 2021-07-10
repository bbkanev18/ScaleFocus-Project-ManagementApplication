#include <nanodbc.h>
#include <iostream>
#include <exception>
#include <string>

#include "ClassUser.h"
#include"Login.h"
#include "AdminMenu.h"
#include "TeamMenu.h"
#include "sha256.h"


//template <typename T>
//T readNumber()
//{
//	T item;
//
//	do
//	{
//		if (std::cin >> item)
//		{
//			return item;
//		}
//		else
//		{
//			std::cout << "Invalid input!" << std::endl;
//			std::cin.clear();
//			std::cin.ignore(INT_MAX, '\n');
//		};
//	} while (true);
//
//	return 0;
//}

int main() try
{
	//std::cout << readNumber<float>();


	//Connecting ssms to visual studio
	auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ScaleFocus-AppDB;Trusted_Connection=yes;MARS_Connection=Yes;");
	nanodbc::connection conn(connstr);
	
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id FROM Users"));

	if (result.next()){}
	else
	{
		CreatingFirstUser(conn);
	}




	int IdOfLoginUser;
	bool RoleOfLoginUser;
	LogMenu(conn, IdOfLoginUser, RoleOfLoginUser);



	
	//std::string username = "Gosho";

	//nanodbc::statement check(conn);
	//nanodbc::prepare(check, R"(
	//	SELECT Id FROM Users
	//	WHERE UserName = )");
	////check.bind(0, &username);

	/*auto result = nanodbc::execute(check);
	while (result.next())
	{
	}*/

	/*
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT UserName, Password FROM Users"));
	std::string userinput;
	std::cin >> userinput;
	std::string password;
	std::cin >> password;

	while (result.next())
	{
		auto dbUser = result.get<nanodbc::string>(0);
		auto dbPassword = result.get<nanodbc::string>(1);
		if (dbUser == userinput and dbPassword == password)
		{
			std::cout << ":)";
		}
		else
			std::cout << "(:";
	}
	*/

	/*
	User user;
	
	nanodbc::statement stmt(conn);

	nanodbc::prepare(stmt, R"(
		INSERT INTO Users (UserName, Password, Role) 
		VALUES
		(?, ?, ?) ;
		SELECT SCOPE_IDENTITY() as sid;
	)");

	const int a_null = 0;
	const char* b_null = "";
	int role = user.getRole();
	std::string encrypterdPassword = sha256(user.getPassword());

	//stmt.bind(0, &user.getId());
	
	stmt.bind(0, user.getUserName().c_str());
	stmt.bind(1, encrypterdPassword.c_str());
	stmt.bind(2, &role);
	//stmt.bind(3, &user.getIdOfCreator(), 1, &a_null);
	//stmt.bind(4, &user.getIdOfUserLastChange(), 1, &a_null);

	auto result = nanodbc::execute(stmt);
	std::cout << result.affected_rows() << std::endl;

	if (result.next_result())
	if (result.next())
	{
		std::cout << "ID: " << result.get<int>("sid", -1) << std::endl;
	}
	*/
	//nanodbc::execute(conn, NANODBC_TEXT(std::string("insert into User (Id, UserName, Password, Role, IdOfCreator, IdOfUserLastChange) VALUES ('"+Id+"', '"+Password+"', '"+Role+"', '"+IdOfCreator+"', '"+IdOfUserLastChange+")")));
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}




/*
int main() try
{
	auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=Test;Trusted_Connection=yes;");
	nanodbc::connection conn(connstr);
	//nanodbc::execute(conn, NANODBC_TEXT("create table t (i int)"));
	
	//nanodbc::execute(conn, NANODBC_TEXT("insert into TestTable (UserName, Password) VALUES ('"+ user +"', '"+ password +"')"));
	//nanodbc::execute(conn, NANODBC_TEXT("insert into TestTable (Id, firstname) VALUES (1, 'hello')"));

	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, UserName, Password, TimeCreated FROM TestTable"));
	while (result.next())
	{
		auto id = result.get<int>(0);
		auto i = result.get<nanodbc::string>(1);
		auto pass = result.get<nanodbc::string>(2);
		auto time = result.get<nanodbc::string>(3);
		//auto i = result.get<int>("One", -1);
		//auto s = result.get<nanodbc::string>(1, "");
		//std::cout << i << ", " << s << std::endl;
		std::cout << id << ", " << i << ", " << pass << ", " << time << "\n";
	}
	//result = nanodbc::execute(conn, NANODBC_TEXT("DELETE FROM TestTable"));
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}
*/