#include "Login.h"

bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Make query to db to get username, id and role
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, Role ,UserName, IsDeleted FROM Users"));
	while (result.next())
	{
		auto IsDeleted = result.get<int>(3);
		// Check is user delete from db
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
	// Make query to db to get password
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Password, IsDeleted FROM Users"));
	while (result.next())
	{
		auto IsDeleted = result.get<int>(1);
		// Check is user delete from db
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
	//Hide password with '*'
	HidePassword(Password);
	// Crypting password using sha256
	std::string encryptedPassword = sha256(Password);
	
	// If check password and username return true
	// You enter in your profile
	if (CheckUserInputForPassword(encryptedPassword, conn) && CheckUserInputForUserName(UserName, conn, idOfLoginUser, RoleOfLoginUser))
	{
		std::cout << "\n\nLogin successfully :)\n";
		std::cout << "Welcome back: " << UserName << "\n";
		system("pause");

		// Check you are user or admin
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

	// If username is wrong give you feedback
	if (CheckUserInputForUserName(UserName, conn, idOfLoginUser, RoleOfLoginUser) == 0)
	{
		std::cout << "\n\n-> Problem with UserName!\n";
	}

	// If password is wrong give you feedback
	if (CheckUserInputForPassword(encryptedPassword, conn) == 0)
	{
		std::cout << "\n\n-> Problem with Password!\n";
	}
	std::cout << "\nTry Again :)\n";
	system("pause");
	
	// If check functions fail you can try again
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
			// delete character if enter backspace
			if (Password.size() != 0) {
				Password.pop_back();
				std::cout << char(8) << ' ' << char(8);
			}
			break;
		case 27: //escape
		case '\r': //\r
			break;
		default: // print '*' instate of your input
			Password.push_back(cr);
			std::cout << '*';
			break;
		}
	} while (cr != '\r');
}