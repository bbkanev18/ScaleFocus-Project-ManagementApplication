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
		case '2':
			subTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
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
		std::cout << "---User Menu---\n1. Print users\n2. Create new user\n3. Edit user\n4. Delete user\nEsc. To back in main menu\n";
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
		case '4':
			subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
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

void subMenuListUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Print Menu---\n1. Print all user\n2. Print user by Id\nEsc. To back in user menu\n";
		switch (_getch())
		{
		case '1':
			getListOfAllUsers(conn);
			break;
		case '2':
		{
			std::cout << "\nChoose user id to print: ";
			int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
			if (id == -1) {
				std::cout << "\n ERROR: Not found id!\n";
				system("pause");
				break;
			}
			else if (id == -2)
			{
				system("pause");
				break;
			}
			system("pause");
			break;
		}
		case 27:
			isTrue = false;
			subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void subDeleteMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Delete Menu---\n1. Delete user by Id\n2. Delete all users ( !back defalt admin and delete all users! )\nEsc. To back in user menu\n";
		switch (_getch())
		{
		case '1':
			deleteOneUser(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
			delteAllUsers(conn, idOfLoginUser, RoleOfLoginUser);
			LogMenu(conn, idOfLoginUser, RoleOfLoginUser);
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

void deleteOneUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int IsDeleted = 1;

	std::cout << "\nChoose user by id to delete: ";
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	else if (id == -2)
	{
		system("pause");
		return;
	}

	if (id == idOfLoginUser)
	{
		std::cout << "\n ERROR: cannot delete yourself \n";
		system("pause");
		return;
	}

	std::cout << "\nIs that correct user you want to edit(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y':
	{
		nanodbc::statement deleteUser(conn);

		nanodbc::prepare(deleteUser, R"(
			UPDATE Users
			SET
			IsDeleted = ?
			WHERE Id = ?
		)");

		deleteUser.bind(0, &IsDeleted);
		deleteUser.bind(1, &id);
		auto result = nanodbc::execute(deleteUser);

		if (result.affected_rows() == 1)
			std::cout << "\nDelete successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change username\n";
			system("pause");
			subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	case 'n':
	case 'N':
		subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

void delteAllUsers(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::cout << "\nAre you sure?\n";
	std::cout << "y/n: ";

	char yesOrNo;
	std::cin >> yesOrNo;

	switch (yesOrNo)
	{
	case 'y':
	case 'Y':{
		nanodbc::statement deleteUsers(conn);

		nanodbc::prepare(deleteUsers, R"(
		UPDATE Users
		SET
		IsDeleted = 1
		)");

		nanodbc::execute(deleteUsers);

		resetDefaultAdmin(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
	case 'n':
	case 'N':
		subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}

}

void resetDefaultAdmin(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) 
{
	nanodbc::statement resetAdmin(conn);

	nanodbc::prepare(resetAdmin, R"(
		UPDATE Users
		SET
		IsDeleted = 0,
		UserName = 'admin',
		Password = '713bfda78870bf9d1b261f565286f85e97ee614efe5f0faf7c34e7ca4f65baca',
		DateOfCreation = GETDATE(),
		DateOfLastChange = GETDATE(),
		IdOfUserLastChange = NULL

		WHERE IdOfCreator IS NULL
	)");

	auto result = nanodbc::execute(resetAdmin);

	std::cout << "\n Reset successfully! :)\n";

	system("pause");
}

void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newUseName;

	std::cout << "\nChoose user by id to editing username: ";
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	if (id == -1){
		std::cout << "\n ERROR: Not found id!\n";
		system("pause"); 
		return;
	}
	else if (id == -2)
	{
		system("pause");
		return;
	}
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

	std::cout << "\nChoose user by id to editing password: ";
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	else if (id == -2)
	{
		system("pause");
		return;
	}
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

	std::cout << "\nChoose user by id to editing firstname: ";
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	else if (id == -2)
	{
		system("pause");
		return;
	}
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
	
	std::cout << "\nChoose user by id to editing lastname: ";
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	else if (id == -2)
	{
		system("pause");
		return;
	}
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

int getUserById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int id;

	std::cin >> id;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "\n ERROR: wrong integer value \n";
		return -2;
	}

	nanodbc::statement findUser(conn);

	nanodbc::prepare(findUser, R"(
		SELECT 
			Id, UserName, Password, FirstName, LastName, 
			DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange
			,IsDeleted
		FROM Users
		WHERE Id = ?
	)");

	findUser.bind(0, &id);

	auto result = nanodbc::execute(findUser);

	if (result.next()){
		return printUser(conn, result);
	}
	else{
		return -1;
	}
}

void createUser(nanodbc::connection conn, int& idOfLoginUser,bool& RoleOfLoginUser) {
	std::string UserName;
	std::string Password;
	std::string FirstName;
	std::string LastName;
	bool role;
	int IsDeleted = 0;
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
		,IdOfCreator, IdOfUserLastChange, IsDeleted) 
		VALUES
		(?, ?, ?, ?, ?, ?, ?, ?);
	)");

	creatingNewUser.bind(0, UserName.c_str());
	creatingNewUser.bind(1, encrypterdPassword.c_str());
	creatingNewUser.bind(2, FirstName.c_str());
	creatingNewUser.bind(3, LastName.c_str());
	creatingNewUser.bind(4, &getRole);
	creatingNewUser.bind(5, &idOfLoginUser);
	creatingNewUser.bind(6, &idOfLoginUser);
	creatingNewUser.bind(7, &IsDeleted);

	nanodbc::execute(creatingNewUser);
	std::cout << "\nCreate successfully :)\n\n";
	system("pause");
	subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
}

void getListOfAllUsers(nanodbc::connection conn) {
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, UserName, Password, FirstName, LastName, DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange, IsDeleted FROM Users"));
	while (result.next())
		printUser(conn, result);
	system("pause");
}

int printUser(nanodbc::connection conn, nanodbc::result& result) 
{
	auto IsDeleted = result.get<int>(10);
	if (IsDeleted == 0)
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
		else{
			nanodbc::statement getIdOfCreator(conn);

			nanodbc::prepare(getIdOfCreator, R"(
			SELECT IdOfCreator
			FROM Users
			WHERE Id = ?
			)");
			getIdOfCreator.bind(0, &Id);

			auto result = nanodbc::execute(getIdOfCreator);
			result.next();
			int newId = result.get<int>(0);

			nanodbc::prepare(getIdOfCreator, R"(
			SELECT UserName
			FROM Users
			WHERE Id = ?
			)");

			getIdOfCreator.bind(0, &newId);

			auto result1 = nanodbc::execute(getIdOfCreator);


			result1.next();
			std::cout << result1.get<nanodbc::string>(0) << "\n";
		}

		std::cout << "Date of last change: " << DateOfLastChange.year << "/" << DateOfLastChange.month << "/" << DateOfLastChange.day << " " << DateOfLastChange.hour << ":" << DateOfLastChange.min << ":" << DateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: ";
		if (IdOfUserLastChange == 0)
			std::cout << "null\n";
		else {
			nanodbc::statement getIdOfLastChange(conn);

			nanodbc::prepare(getIdOfLastChange, R"(
			SELECT IdOfUserLastChange
			FROM Users
			WHERE Id = ?
			)");
			getIdOfLastChange.bind(0, &Id);

			auto result = nanodbc::execute(getIdOfLastChange);
			result.next();
			int newId = result.get<int>(0);

			nanodbc::prepare(getIdOfLastChange, R"(
			SELECT UserName
			FROM Users
			WHERE Id = ?
			)");

			getIdOfLastChange.bind(0, &newId);

			auto result1 = nanodbc::execute(getIdOfLastChange);


			result1.next();
			std::cout << result1.get<nanodbc::string>(0) << "\n";
		}
		std::cout << "======================================\n";
		std::cout << "\n";
		return Id;
	}
	else
	{
		return -1;
	}
}

