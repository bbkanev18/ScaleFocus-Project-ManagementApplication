#include "TeamMenu.h"


void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Team Menu---\n1. Print teams\n2. Create new team\n3. Edit team\n4. Delete team\nEsc. To back in main menu\n";
		switch (_getch())
		{
		case '1':
			subPrintTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
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

void subPrintTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Print Menu---\n1. Print all teams\n2. Print team by id\nEsc. To back in team menu\n";
		switch (_getch())
		{
		case '1':
			getAllTeams(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
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


void getAllTeams(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	nanodbc::statement getTeam(conn);

	nanodbc::prepare(getTeam, R"(
		SELECT
			Id,
			Title,
			DateOfCreation,
			IdOfCreator,
			DateOfLastChange,
			IdOfUserLastChange,
			IsDeleted
		FROM Teams
	)");

	auto result = nanodbc::execute(getTeam);
	std::cout << "\n";
	while (result.next())
	{
		printOneTeam(conn, result);
		std::cout << "\n";
	}
	system("pause");
}

int printOneTeam(nanodbc::connection conn, nanodbc::result& result) {
	auto dbId = result.get<int>(0);
	auto dbTitle = result.get<nanodbc::string>(1);
	auto dbDateOfCreation = result.get<nanodbc::timestamp>(2);
	auto dbIdOfCreator = result.get<int>(3);
	auto dbDateOfLastChange = result.get<nanodbc::timestamp>(4);
	auto dbIdOfTheUserLastChange = result.get<int>(5);
	auto dbIsDeleted = result.get<int>(6);

	if (dbIsDeleted == 0)
	{

		std::cout << "Id: " << dbId << "\n";
		std::cout << "Title: " << dbTitle << "\n";
		std::cout << "Date of creation: " << dbDateOfCreation.year << "/" << dbDateOfCreation.month << "/" << dbDateOfCreation.day << " " << dbDateOfCreation.hour << ":" << dbDateOfCreation.min << ":" << dbDateOfCreation.sec << "\n";
		std::cout << "Id of creator: ";
		printUserNameByIdOfCreatorOnTeam(conn, dbId);
		std::cout << "Date of last change: " << dbDateOfLastChange.year << "/" << dbDateOfLastChange.month << "/" << dbDateOfLastChange.day << " " << dbDateOfLastChange.hour << ":" << dbDateOfLastChange.min << ":" << dbDateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: ";
		printUserNameByIdOfLastChangeOnTeam(conn, dbId);
		std::cout << "======================================\n";
		return dbId;
	}
	else
		return -1;
}

void printUserNameByIdOfCreatorOnTeam(nanodbc::connection conn, int id) {
	nanodbc::statement getIdOfCreator(conn);

	nanodbc::prepare(getIdOfCreator, R"(
			SELECT IdOfCreator
			FROM Teams
			WHERE Id = ?
			)");
	getIdOfCreator.bind(0, &id);

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

void printUserNameByIdOfLastChangeOnTeam(nanodbc::connection conn, int id) {
	nanodbc::statement getIdOfLastChange(conn);

	nanodbc::prepare(getIdOfLastChange, R"(
			SELECT IdOfUserLastChange
			FROM Teams
			WHERE Id = ?
			)");
	getIdOfLastChange.bind(0, &id);

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