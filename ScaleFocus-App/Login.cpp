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

bool CheckUserInputForPassword(std::string encryptedPassword, nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Password FROM Users"));
	while (result.next())
	{
		auto dbPassword = result.get<nanodbc::string>(0);
		if (encryptedPassword == dbPassword)
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
	std::cout << "Username: ";
	std::cin >> UserName;
	std::cout << "Password: ";
	HidePassword(Password);
	std::string encryptedPassword = sha256(Password);

	if (CheckUserInputForPassword(encryptedPassword, conn) && CheckUserInputForUserName(UserName, conn))
	{

		std::cout << "\n\nLogin successfully :)\n";
		std::cout << "Welcome back: " << UserName << "\n";
		return true;
	}
	if (CheckUserInputForUserName(UserName, conn) == 0)
	{
		std::cout << "\n\n-> Problem with UserName!\n";
	}
	if (CheckUserInputForPassword(encryptedPassword, conn) == 0)
	{
		std::cout << "\n\n-> Problem with Password!\n";
		std::cout << "[Password you enter: '" << Password << "']\n\n";
	}
	std::cout << "Try Again :)\n";
	system("pause");

	LogMenu(conn);
}


void HidePassword(std::string& Password) {
	char cr = 0;
	do
	{
		cr = _getch();
		switch (cr)
		{
		case 8: //backspace
			if (Password.size() != 0) {
				Password.pop_back();
				std::cout << char(8) << ' ' << char(8);
			}
			break;
		case 27: //escape
		case '\r': //\r
			break;
		default: //asfasfasdf 123123 
			Password.push_back(cr);
			std::cout << '*';
			break;
		}
	} while (cr != '\r');
}