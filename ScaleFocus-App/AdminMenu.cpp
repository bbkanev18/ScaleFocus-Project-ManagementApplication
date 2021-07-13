#include "AdminMenu.h"

void adminMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Breake while and back to login menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Admin Menu---\n1. Users Management\n2. Teams Management\n3. Projects and Task Management\n4. Work log\nEsc. To logout\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
			subTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '3':
			subProjectMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '4': {
			std::cout << "\n           Coming soon \n";
			std::cout <<" Work log menu is not available now \n\n";
			system("pause");
			break;
		}
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
	// Breake while and back to admin menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---User Menu---\n1. Print users\n2. Create new user\n3. Edit user\n4. Delete user\nEsc. To back in main menu\n";
		// Use _getch to get user choise
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
	// Breake while and back to user menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Edit Menu---\n1. Change username\n2. Change password\n3. Change firstname\n4. Change lastname\nEsc. To back in user menu\n";
		// Use _getch to get user choise
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
	// Breake while and back to user menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Print Menu---\n1. Print all user\n2. Print user by Id\nEsc. To back in user menu\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			getListOfAllUsers(conn);
			break;
		case '2':
		{
			std::cout << "\nChoose user id to print: ";
			// Getting id from function and if fail give feedback by id
			int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
			// If function return -1 is mean id cannot found
			if (id == -1) {
				std::cout << "\n ERROR: Not found id!\n";
				system("pause");
				break;
			}
			// If function return -2 is mean you enter character in integer
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
	// Breake while and back to user menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Delete Menu---\n1. Delete user by Id\n2. Delete all users ( !back defalt admin and delete all users! )\nEsc. To back in user menu\n";
		// Use _getch to get user choise
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
	std::cout << "\nChoose user by id to delete: ";
	
	// Getting id from function and if fail give feedback by id
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	
	// If function return -2 is mean you enter character in integer
	else if (id == -2)
	{
		system("pause");
		return;
	}
	// Check you want to delete yourself
	if (id == idOfLoginUser)
	{
		std::cout << "\n ERROR: cannot delete yourself \n";
		system("pause");
		return;
	}

	std::cout << "\nIs that correct user you want to edit(y/n)";
	
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y':
	{
		// Make statemant to delete user
		nanodbc::statement deleteUser(conn);

		// Make new query to db to upadate column IsDeleted to 1
		// updating column where id = number you enter in function getUserById
		nanodbc::prepare(deleteUser, R"(
			UPDATE Users
			SET
			IsDeleted = 1
			WHERE Id = ?
		)");
		
		// Binding '?' with id of user
		deleteUser.bind(0, &id);

		// Execute query to db and store in result
		auto result = nanodbc::execute(deleteUser);

		// Check how many rows are affected
		// If there is only one print 'Delete successfully :)'
		if (result.affected_rows() == 1)
			std::cout << "\n Delete successfully :) \n";
		else
		{
			std::cout << "\n ERROR: In change username\n";
			system("pause");
			subDeleteMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	// n -> no
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
	// y -> yes
	case 'y':
	case 'Y':{
		// Make statement called deleteUsers
		nanodbc::statement deleteUsers(conn);

		// Make query to update all user with IsDelete = 1
		nanodbc::prepare(deleteUsers, R"(
		UPDATE Users
		SET
		IsDeleted = 1
		)");

		// Execute query to db
		nanodbc::execute(deleteUsers);

		// Call function resetDefaultAdmin
		// To reset default admin if there are some change from other admin
		resetDefaultAdmin(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
	// n -> no
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
	// Make statement called resetAdmin
	nanodbc::statement resetAdmin(conn);

	// Make new query to update default admin
	// To find default admin is to search where Id of creator is null
	nanodbc::prepare(resetAdmin, R"(
		UPDATE Users
		SET
		IsDeleted = 0,
		UserName = 'admin',
		Password = '713bfda78870bf9d1b261f565286f85e97ee614efe5f0faf7c34e7ca4f65baca',
		FirstName = 'admin',
		LastName = 'admin',
		DateOfCreation = GETDATE(),
		DateOfLastChange = GETDATE(),
		IdOfUserLastChange = NULL

		WHERE IdOfCreator IS NULL
	)");
	
	// Execute query to db
	nanodbc::execute(resetAdmin);

	std::cout << "\n Reset successfully! :) \n";

	system("pause");
}

void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newUseName;

	std::cout << "\nChoose user by id to editing username: ";
	
	// Getting id from function and if fail give feedback by id
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (id == -1){
		std::cout << "\n ERROR: Not found id!\n";
		system("pause"); 
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (id == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct user you want to edit(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> yes
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new username: ";
		std::cin >> newUseName;
		
		// Make statement called changeOldUserName
		nanodbc::statement changeOldUserName(conn);
		
		// Make new query to update username
		// where id is get from function getUserById
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			UserName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		// Convert normal string to nanodbc string
		nanodbc::string nwUN = newUseName;

		// bind first '?' with new username
		changeOldUserName.bind(0, nwUN.c_str());
		// bind second '?' with id of login user
		changeOldUserName.bind(1, &idOfLoginUser);
		// bind third '?' with id of user
		changeOldUserName.bind(2, &id);

		// execute query and store in result
		auto result = nanodbc::execute(changeOldUserName);

		// If there is one affected row print 'Change successfully'
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
	// n -> no
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
	
	// Getting id from function and if fail give feedback by id
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (id == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct user you want to edit(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> yes
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new password: ";
		// Hiding password with '*'
		HidePassword(newPassword);

		// Creating new statement called changeOldUserName
		nanodbc::statement changeOldUserName(conn);
		
		// Make new query to update db
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			Password = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		// Convert normal string to nanodbc string
		// and encrypting password with sha256
		nanodbc::string encryptedPassword = sha256(newPassword);

		// Bind first '?' with encrypted password
		changeOldUserName.bind(0, encryptedPassword.c_str());
		// Bind second '?' with id of login user
		changeOldUserName.bind(1, &idOfLoginUser);
		// Bind third '?' with id of user
		changeOldUserName.bind(2, &id);
		
		// execute query and store in result
		auto result = nanodbc::execute(changeOldUserName);

		// If there is one affected row print 'Change successfully'
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
	// n -> no
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

	// Getting id from function and if fail give feedback by id
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (id == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct user you want to edit(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> yes
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new firstname: ";
		std::cin >> newFirstName;
		// Creating new statement called changeOldUserName
		nanodbc::statement changeOldUserName(conn);
		// Make new query to db
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			FirstName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		// Convert normal string to nanodbc string
		nanodbc::string nwFN = newFirstName;

		// Bind first '?' with new firstname
		changeOldUserName.bind(0, nwFN.c_str());
		// Bind sencond '?' with id of login user
		changeOldUserName.bind(1, &idOfLoginUser);
		// Bind third '?' with id of user
		changeOldUserName.bind(2, &id);

		// Execute query
		auto result = nanodbc::execute(changeOldUserName);

		// If there is one affected row print 'Change successfully'
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
	// n -> no
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

	// Getting id from function and if fail give feedback by id
	int id = getUserById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (id == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (id == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct user you want to edit(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> yes
	case 'y':
	case 'Y':
	{
		std::cout << "\n\nChoose new lastname: ";
		std::cin >> newLastName;
		// Creating new statement called changeOldUserName
		nanodbc::statement changeOldUserName(conn);
		// Make new query to db
		nanodbc::prepare(changeOldUserName, R"(
			UPDATE Users
			SET
			 LastName = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		// Convert normal string to nanodbc string
		nanodbc::string nwLN = newLastName;

		// Bind first '?' with new lastname
		changeOldUserName.bind(0, nwLN.c_str());
		// Bind second '?' with id of login user
		changeOldUserName.bind(1, &idOfLoginUser);
		// Bind third '?' with id of user
		changeOldUserName.bind(2, &id);

		// Execute query
		auto result = nanodbc::execute(changeOldUserName);

		// If there is one affected row print 'Change successfully'
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
	// If you enter letter in integer
	if (std::cin.fail())
	{
		// clear all error flags
		std::cin.clear();
		// ignore INT_MAX symbols when you press enter
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "\n ERROR: wrong integer value \n";
		return -2;
	}
	// To exit from assigning user in team
	if (id == -3)
		return -3;

	// Creating statement findUser
	nanodbc::statement findUser(conn);

	// Make query to db
	nanodbc::prepare(findUser, R"(
		SELECT 
			Id, UserName, Password, FirstName, LastName, 
			DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange
			,IsDeleted
		FROM Users
		WHERE Id = ?
	)");

	// Bind first '?' with id of user you choise
	findUser.bind(0, &id);

	// Execute query
	auto result = nanodbc::execute(findUser);

	// Check is there somthing db and printed
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
	// encrypting password sha256
	std::string encrypterdPassword = sha256(Password);
	std::cout << "Choose firstname: ";
	std::cin >> FirstName;
	std::cout << "Choose lastname: ";
	std::cin >> LastName;
	std::cout << "Role (1 - administrator, 0 - user): ";
	std::cin >> role;
	// Convert bool in integer
	int getRole = role;

	// Create statment creatingNewUser
	nanodbc::statement creatingNewUser(conn);
	// Create new query to insert user
	nanodbc::prepare(creatingNewUser, R"(
		INSERT INTO Users (
		UserName, Password, FirstName, LastName, Role
		,IdOfCreator, IdOfUserLastChange, IsDeleted) 
		VALUES
		(?, ?, ?, ?, ?, ?, ?, ?);
	)");

	// Binding all user input
	creatingNewUser.bind(0, UserName.c_str());
	creatingNewUser.bind(1, encrypterdPassword.c_str());
	creatingNewUser.bind(2, FirstName.c_str());
	creatingNewUser.bind(3, LastName.c_str());
	creatingNewUser.bind(4, &getRole);
	creatingNewUser.bind(5, &idOfLoginUser);
	creatingNewUser.bind(6, &idOfLoginUser);
	creatingNewUser.bind(7, &IsDeleted);

	// Execute query
	nanodbc::execute(creatingNewUser);
	std::cout << "\nCreate successfully :)\n\n";
	system("pause");
	subAdminUserMenu(conn, idOfLoginUser, RoleOfLoginUser);
}

void getListOfAllUsers(nanodbc::connection conn) {
	// Make query to select all user
	auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Id, UserName, Password, FirstName, LastName, DateOfCreation, Role, IdOfCreator, DateOfLastChange, IdOfUserLastChange, IsDeleted FROM Users"));
	while (result.next())
		// Print one user
		printUser(conn, result);
	system("pause");
}

int printUser(nanodbc::connection conn, nanodbc::result& result) 
{
	auto IsDeleted = result.get<int>(10);
	// Check is the user is deleted
	if (IsDeleted == 0)
	{
		std::cout << "\n======================================\n";
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
			// Get id of creator and print username of creator
			printUserNameByIdOfCreator(conn, Id);
		std::cout << "Date of last change: " << DateOfLastChange.year << "/" << DateOfLastChange.month << "/" << DateOfLastChange.day << " " << DateOfLastChange.hour << ":" << DateOfLastChange.min << ":" << DateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: ";
		if (IdOfUserLastChange == 0)
			std::cout << "null\n";
		else
			// Get id of last edit and print username
			printUserNameByIdOfLastChange(conn, Id);
		std::cout << "======================================\n";
		std::cout << "\n";
		return Id;
	}
	else
	{
		return -1;
	}
}

void printUserNameByIdOfCreator(nanodbc::connection conn, int id) {
	// Create statement getIdOfCreator
	nanodbc::statement getIdOfCreator(conn);
	// Create new query
	// selecting id of creator from currently id user
	nanodbc::prepare(getIdOfCreator, R"(
			SELECT IdOfCreator
			FROM Users
			WHERE Id = ?
			)");
	// Bind first '?' wiht id of currently printing user
	getIdOfCreator.bind(0, &id);
	// Execute query
	auto result = nanodbc::execute(getIdOfCreator);
	// Read result
	result.next();
	// Get the id of creator
	int newId = result.get<int>(0);

	// Make new query
	// Get username of creator
	nanodbc::prepare(getIdOfCreator, R"(
			SELECT UserName
			FROM Users
			WHERE Id = ?
	)");
	// Bind first '?' with newId
	getIdOfCreator.bind(0, &newId);
	// Execute query
	auto result1 = nanodbc::execute(getIdOfCreator);

	// Read result1
	result1.next();
	// Cout username of creator
	std::cout << result1.get<nanodbc::string>(0) << "\n";
}

void printUserNameByIdOfLastChange(nanodbc::connection conn, int id) {
	// Create statement getIdOfLastChange
	nanodbc::statement getIdOfLastChange(conn);
	// Make new query
	// selecting id of last edit user from currently id user
	nanodbc::prepare(getIdOfLastChange, R"(
			SELECT IdOfUserLastChange
			FROM Users
			WHERE Id = ?
			)");
	// Bind first '?' wiht id of currently printing user
	getIdOfLastChange.bind(0, &id);

	// Execute query
	auto result = nanodbc::execute(getIdOfLastChange);
	// Read result
	result.next();
	// Get the id of last edit user
	int newId = result.get<int>(0);

	// Make new query
	// Get username of last edit
	nanodbc::prepare(getIdOfLastChange, R"(
			SELECT UserName
			FROM Users
			WHERE Id = ?
		)");
	// Bind first '?' with newId
	getIdOfLastChange.bind(0, &newId);
	// Execute query
	auto result1 = nanodbc::execute(getIdOfLastChange);

	// Read result1
	result1.next();
	// Cout username of last edit
	std::cout << result1.get<nanodbc::string>(0) << "\n";
}