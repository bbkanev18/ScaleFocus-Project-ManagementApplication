#include "Login.h"

bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT UserName FROM Users"));
	while (result.next())
	{
		auto dbUserName = result.get<nanodbc::string>(0);
		if (UserName == dbUserName)
		{
			return true;
		}
	}
	return false;
}

bool CheckUserInputForPassword(std::string Password, nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Password FROM Users"));
	while (result.next())
	{
		auto dbPassword = result.get<nanodbc::string>(0);
		if (Password == dbPassword)
		{
			return true;
		}
	}
	return false;
}

bool LogMenu(nanodbc::connection conn) {
	std::string UserName;
	std::string Password;
	system("CLS");
	std::cout << "UserName: ";
	std::cin >> UserName;
	std::cout << "Password: ";
	std::cin >> Password;
	if (CheckUserInputForPassword(Password, conn) && CheckUserInputForUserName(UserName, conn))
	{

		std::cout << "\nLogin successfully :)\n";
		std::cout << "Welcome back: " << UserName << "\n";
		return true;
	}
	if (CheckUserInputForUserName(UserName, conn) == 0)
	{
		std::cout << "\n-> Proble with UserName!\n";
	}
	if (CheckUserInputForPassword(Password, conn) == 0)
	{
		std::cout << "-> Proble with Password!\n\n";
	}
	std::cout << "Try Againg\n";
	system("pause");

	LogMenu(conn);
}