#include "AdminMenu.h"

void adminMenu(nanodbc::connection conn) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "--Admin Menu--\n1. List users\n2. Create new user\n3. Edit user\n4. Delete user\nEsc. To exit program\n";
		switch (_getch())
		{
		case '1':
			subMenuListUser(conn);
			break;
		case 27:
			isTrue = false;
			break;
		default:
			break;
		}
	}
}

void subMenuListUser(nanodbc::connection conn) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "1. List all user\n2. List by Id\nEsc. To back in main menu\n";
		switch (_getch())
		{
		case '1':
			getListOfAllUsers(conn);
			break;
		case '2':
			getUserListById(conn);
			break;
		case 27:
			isTrue = false;
			break;
		default:
			break;
		}
	}
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

void getUserListById(nanodbc::connection conn) 
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
	std::cout << "Enter User Id: ";
	std::cin >> id;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	

	findUser.bind(0, &id);

	auto result = nanodbc::execute(findUser);
	if (result.next()) 
	{
		printUser(conn, result);
	}
	else {
		getUserListById(conn);
	}
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
}