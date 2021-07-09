#include "AdminMenu.h"

void adminMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Admin Menu---\n1. Users Management\n2. Teams Management\n3. Projects Management\nEsc. To logout\n";
		switch (_getch())
		{
		case '1':
			subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case 27:
			isTrue = false;
			LogMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void subAdminUserMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---User Menu---\n1. List users\n2. Create new user\n3. Edit user\n4. Delete user\nEsc. To back in main menu\n";
		switch (_getch())
		{
		case '1':
			subMenuListUser(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
			createUser(conn, idOfLoginUser, RoleOfLoginUser);
		case '3':
			subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case 27:
			isTrue = false;
			adminMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void subEditMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		int failToEnterId = 5;
		system("cls");
		std::cout << "---Edit Menu---\n1. Change username\n2. Change password\n3. Change firstname\n4. Change lastname\nEsc. To back in user menu\n";
		switch (_getch())
		{
		case '1':
			editUserName(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
			editPassword(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '3':
			editFirstName(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '4':
			editLastName(conn, idOfLoginUser, RoleOfLoginUser);
		case 27:
			isTrue = false;
			subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void subMenuListUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		int failToEnterId = 5;
		system("cls");
		std::cout << "---Print Menu---\n1. List all user\n2. List by Id\nEsc. To back in user menu\n";
		switch (_getch())
		{
		case '1':
			getListOfAllUsers(conn);
			break;
		case '2':
			getUserListById(conn, failToEnterId, idOfLoginUser, RoleOfLoginUser);
			break;
		case 27:
			isTrue = false;
			subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newUseName;
	
	int id = getUserByIdForEdit(conn, idOfLoginUser, RoleOfLoginUser);
	std::cout << "\nIs that correct user you want to edit(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new username: ";
		std::cin >> newUseName;
		nanodbc::statement changeOldUserName(conn);
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			UserName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		nanodbc::string nwUN = newUseName;

		changeOldUserName.bind(0, nwUN.c_str());
		changeOldUserName.bind(1, &idOfLoginUser);
		changeOldUserName.bind(2, &id);
		auto result = nanodbc::execute(changeOldUserName);

		if (result.affected_rows() == 1)
			std::cout << "\nChange successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change username\n";
			system("pause");
			subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	case 'n':
	case 'N':
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

void editPassword(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newPassword;

	int id = getUserByIdForEdit(conn, idOfLoginUser, RoleOfLoginUser);
	std::cout << "\nIs that correct user you want to edit(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new password: ";
		HidePassword(newPassword);
		nanodbc::statement changeOldUserName(conn);
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			Password = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		nanodbc::string encryptedPassword = sha256(newPassword);

		changeOldUserName.bind(0, encryptedPassword.c_str());
		changeOldUserName.bind(1, &idOfLoginUser);
		changeOldUserName.bind(2, &id);
		auto result = nanodbc::execute(changeOldUserName);

		if (result.affected_rows() == 1)
			std::cout << "\nChange successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change password\n";
			system("pause");
			subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	case 'n':
	case 'N':
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

void editFirstName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newFirstName;

	int id = getUserByIdForEdit(conn, idOfLoginUser, RoleOfLoginUser);
	std::cout << "\nIs that correct user you want to edit(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new firstname: ";
		std::cin >> newFirstName;
		nanodbc::statement changeOldUserName(conn);
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			FirstName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		nanodbc::string nwFN = newFirstName;

		changeOldUserName.bind(0, nwFN.c_str());
		changeOldUserName.bind(1, &idOfLoginUser);
		changeOldUserName.bind(2, &id);
		auto result = nanodbc::execute(changeOldUserName);

		if (result.affected_rows() == 1)
			std::cout << "\nChange successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change password\n";
			system("pause");
			subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	case 'n':
	case 'N':
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

void editLastName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newLastName;

	int id = getUserByIdForEdit(conn, idOfLoginUser, RoleOfLoginUser);
	std::cout << "\nIs that correct user you want to edit(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new lastname: ";
		std::cin >> newLastName;
		nanodbc::statement changeOldUserName(conn);
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			 LastName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		nanodbc::string nwLN = newLastName;

		changeOldUserName.bind(0, nwLN.c_str());
		changeOldUserName.bind(1, &idOfLoginUser);
		changeOldUserName.bind(2, &id);
		auto result = nanodbc::execute(changeOldUserName);

		if (result.affected_rows() == 1)
			std::cout << "\nChange successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change password\n";
			system("pause");
			subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	case 'n':
	case 'N':
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

int getUserByIdForEdit(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int id;

	std::cout << "\nChoose user by id to editing name: ";
	std::cin >> id;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "\n ERROR: wrong integer value \n";
		system("pause");
		subEditMenu(conn, idOfLoginUser, RoleOfLoginUser);
	}

	nanodbc::statement findUser(conn);

	nanodbc::prepare(findUser, R"(
		SELECT 
			Id, UserName, Password, FirstName, LastName, 
			DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange
		FROM Users
		WHERE Id = ?
	)");

	findUser.bind(0, &id);

	auto result = nanodbc::execute(findUser);
	if (result.next())
		printUser(conn, result);
	return id;
}

void createUser(nanodbc::connection conn, int& idOfLoginUser,bool& RoleOfLoginUser) {
	std::string UserName;
	std::string Password;
	std::string FirstName;
	std::string LastName;
	bool role;
	system("cls");
	std::cout << "Choose username: ";
	std::cin >> UserName;
	std::cout << "Choose password: ";
	std::cin >> Password;
	std::string encrypterdPassword = sha256(Password);
	std::cout << "Choose firstname: ";
	std::cin >> FirstName;
	std::cout << "Choose lastname: ";
	std::cin >> LastName;
	std::cout << "Role (1 - administrator, 0 - user): ";
	std::cin >> role;
	int getRole = role;

	nanodbc::statement creatingNewUser(conn);

	nanodbc::prepare(creatingNewUser, R"(
		INSERT INTO Users (
		UserName, Password, FirstName, LastName, Role
		,IdOfCreator, IdOfUserLastChange) 
		VALUES
		(?, ?, ?, ?, ?, ?, ?) ;
	)");

	creatingNewUser.bind(0, UserName.c_str());
	creatingNewUser.bind(1, encrypterdPassword.c_str());
	creatingNewUser.bind(2, FirstName.c_str());
	creatingNewUser.bind(3, LastName.c_str());
	creatingNewUser.bind(4, &getRole);
	creatingNewUser.bind(5, &idOfLoginUser);
	creatingNewUser.bind(6, &idOfLoginUser);

	nanodbc::execute(creatingNewUser);
	std::cout << "\nCreate successfully :)\n\n";
	system("pause");
	subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
}

void getListOfAllUsers(nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, UserName, Password, FirstName, LastName, DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange FROM Users"));
	while (result.next())
	{
		printUser(conn, result);
		std::cout << "\n";
	}
	system("pause");
}

void getUserListById(nanodbc::connection conn, int failToEnterId, int& idOfLoginUser, bool& RoleOfLoginUser)
{
	
	nanodbc::statement findUser(conn);

	nanodbc::prepare(findUser, R"(
		SELECT 
			Id, UserName, Password, FirstName, LastName, 
			DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange
		FROM Users
		WHERE Id = ?
	)");

	int id;
	system("cls");
	std::cout << "--If you enter " << failToEnterId << " times wrong you go back to list menu--\n";
	std::cout << "Enter User Id: ";
	std::cin >> id;
	failToEnterId--;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	if (failToEnterId == 0)
		subMenuListUser(conn, idOfLoginUser, RoleOfLoginUser);
	

	findUser.bind(0, &id);

	auto result = nanodbc::execute(findUser);
	if (result.next()) 
		printUser(conn, result);
	else 
		getUserListById(conn, failToEnterId, idOfLoginUser, RoleOfLoginUser);
	std::cout << "\n";
	system("pause");
}

void printUser(nanodbc::connection conn, nanodbc::result& result) 
{
	auto Id = result.get<int>(0);
	auto UserName = result.get<nanodbc::string>(1);
	auto Password = result.get<nanodbc::string>(2);
	auto FirstName = result.get<nanodbc::string>(3, "null");
	auto LastName = result.get<nanodbc::string>(4, "null");
	auto DateOfCreation = result.get<nanodbc::timestamp>(5);
	auto Role = result.get<int>(6);
	auto IdOfCreator = result.get<int>(7, NULL);
	auto DateOfLastChange = result.get<nanodbc::timestamp>(8);
	auto IdOfUserLastChange = result.get<int>(9, NULL);
	std::cout << "\nRole: ";
	if (Role)
		std::cout << "Admin role\n";
	else
		std::cout << "User role\n";
	std::cout << "Id: " << Id << "\n";
	std::cout << "Username: " << UserName << "\n";
	std::cout << "Password: " << Password << "\n";
	std::cout << "Firstname: " << FirstName << "\n";
	std::cout << "Lastname: " << LastName << "\n";
	std::cout << "Date of creation: " << DateOfCreation.year << "/" << DateOfCreation.month << "/" << DateOfCreation.day << " " << DateOfCreation.hour << ":" << DateOfCreation.min << ":" << DateOfCreation.sec << "\n";
	std::cout << "Id of creator: ";
	if (IdOfCreator == 0)
		std::cout << "null\n";
	else
		std::cout << IdOfCreator << "\n";
	std::cout << "Date of last change: " << DateOfLastChange.year << "/" << DateOfLastChange.month << "/" << DateOfLastChange.day << " " << DateOfLastChange.hour << ":" << DateOfLastChange.min << ":" << DateOfLastChange.sec << "\n";
	std::cout << "Id of the user that did the last change: ";
	if (IdOfUserLastChange == 0)
		std::cout << "null\n";
	else
		std::cout << IdOfUserLastChange << "\n";
	std::cout << "======================================\n";
}