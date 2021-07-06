#include <nanodbc.h>
#include <iostream>
#include <exception>
#include <string>

int main() try
{
	auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=Test;Trusted_Connection=yes;");
	nanodbc::connection conn(connstr);
	//nanodbc::execute(conn, NANODBC_TEXT("create table t (i int)"));
	std::string user = "admin";
	std::string password = "adminpass";
	//nanodbc::execute(conn, NANODBC_TEXT("insert into TestTable (UserName, Password) VALUES ('"+ user +"', '"+ password +"')"));

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