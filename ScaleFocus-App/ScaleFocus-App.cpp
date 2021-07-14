#include <nanodbc.h> // ♥♥♥
#include <iostream>
#include <exception>
#include <string>

#include "ClassUser.h"
#include"Login.h"
#include "AdminMenu.h"
#include "TeamMenu.h"
#include "ProjectMenu.h"
#include "sha256.h"

int main() try
{
	// Connecting ssms to visual studio
	auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=ScaleFocus-AppDB;Trusted_Connection=yes;MARS_Connection=Yes;");
	nanodbc::connection conn(connstr);
	
	// Check database is empty
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id FROM Users"));

	if (result.next()){}
	else
		// Creating default user
		CreatingFirstUser(conn);

	// Get Id of currently login user
	int IdOfLoginUser;
	
	// Get Role of currently login user
	bool RoleOfLoginUser;
	
	LogMenu(conn, IdOfLoginUser, RoleOfLoginUser);
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	// Print what is the problem in db
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}