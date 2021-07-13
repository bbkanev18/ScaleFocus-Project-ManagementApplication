#include "Login.h"


bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, Role ,UserName, IsDeleted FROM Users"));
	
	while (result.next())
	{
		auto IsDeleted = result.get<int>(3);
		if (IsDeleted == 0)
		{
			auto dbIdUser = result.get<int>(0);
			auto dbRoleUser = result.get<int>(1);
			auto dbUserName = result.get<nanodbc::string>(2);
			if (UserName == dbUserName)
			{
				idOfLoginUser = dbIdUser;
				RoleOfLoginUser = dbRoleUser;
				return true;
			}
		}
	}
	return false;
}

bool CheckUserInputForPassword(std::string encryptedPassword, nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Password, IsDeleted FROM Users"));
	while (result.next())
	{
		auto IsDeleted = result.get<int>(1);
		if (IsDeleted == 0)
		{
			auto dbPassword = result.get<nanodbc::string>(0);
			if (encryptedPassword == dbPassword)
			{
				return true;
			}
		}
	}
	return false;
}

void LogMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string UserName;
	std::string Password;
	system("CLS");
	std::cout << "Username: ";
	std::cin >> UserName;
	std::cout << "Password: ";
	HidePassword(Password);
	std::string encryptedPassword = sha256(Password);

	if (CheckUserInputForPassword(encryptedPassword, conn) && CheckUserInputForUserName(UserName, conn, idOfLoginUser, RoleOfLoginUser))
	{
		std::cout << "\n\nLogin successfully :)\n";
		std::cout << "Welcome back: " << UserName << "\n";
		system("pause");

		if (RoleOfLoginUser == 1)
			adminMenu(conn, idOfLoginUser, RoleOfLoginUser);
		else {
			system("cls");
			std::cout << "\n           Coming soon \n";
			std::cout << " The user menu is not available now \n\n";
			system("pause");
		}

		return ;
	}
	if (CheckUserInputForUserName(UserName, conn, idOfLoginUser, RoleOfLoginUser) == 0)
	{
		std::cout << "\n\n-> Problem with UserName!\n";
	}
	if (CheckUserInputForPassword(encryptedPassword, conn) == 0)
	{
		std::cout << "\n\n-> Problem with Password!\n";
	}
	std::cout << "\nTry Again :)\n";
	system("pause");

	LogMenu(conn, idOfLoginUser, RoleOfLoginUser);
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