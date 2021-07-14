#include "ProjectMenu.h"

void subProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Breake while and back to admin menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Project and Task Menu---\n1. Print project\n2. Create new project\n3. Edit project\n4. Delete project\nEsc. To back in main menu\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			subPrintProjectMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2': {
			std::cout << "\n         Coming soon \n";
			std::cout << " Create menu is not available now \n\n";
			system("pause");
			break;
		}
		case '3': {
			std::cout << "\n         Coming soon \n";
			std::cout << " Edit menu is not available now \n\n";
			system("pause");
			break;
		}
		case '4': {
			std::cout << "\n         Coming soon \n";
			std::cout << " Delete menu is not available now \n\n";
			system("pause");
			break;
		}
		case 27:
			isTrue = false;
			adminMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void subPrintProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Breake while and back to project and task menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Print Menu---\n1. Print all project\n2. Print project by id\nEsc. To back in project and task menu\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			printAllProject(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2': {
			std::cout << "\n              Coming soon \n";
			std::cout << " Pirnt project by id is not available now \n\n";
			system("pause");
			break;
		}
		case 27:
			isTrue = false;
			subProjectMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		default:
			break;
		}
	}
}

void printAllProject(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Make new statement getAllProject
	nanodbc::statement getAllProject(conn);
	// Make query to db to select information for project
	nanodbc::prepare(getAllProject, R"(
		SELECT 
			Id,
			Title,
			Description,
			DateOfCreation,
			IdOfCreator,
			DateOfLastChange,
			IdOfUserLastChange,
			IdTeam,
			IsDeleted
		FROM Projects
	)");
	// Execute query
	auto result = nanodbc::execute(getAllProject);
	// Read row and print
	while (result.next())
	{
		printOneProject(conn, result);
	}
	system("pause");
}


void printOneProject(nanodbc::connection conn, nanodbc::result& result) {
	auto dbId = result.get<int>(0);
	auto dbTitle = result.get<nanodbc::string>(1);
	auto dbDescription = result.get<nanodbc::string>(2);
	auto dbDateOfCreation = result.get<nanodbc::timestamp>(3);
	auto dbIdOfCreator = result.get<int>(4);
	auto dbDateOfLastChange = result.get<nanodbc::timestamp>(5);
	auto dbIdOfUserLastChange = result.get<int>(6);
	auto dbIdTeam = result.get<int>(7);
	auto dbIsDeleted = result.get<int>(8);
	
	// Check is project is delete
	if (dbIsDeleted == 0)
	{
		std::cout << "\n======================================\n";
		std::cout << "Id: " << dbId << "\n";
		std::cout << "Title: " << dbTitle << "\n";
		std::cout << "Description: " << dbDescription << "\n";
		std::cout << "Date of creation: " << dbDateOfCreation.year << "/" << dbDateOfCreation.month << "/" << dbDateOfCreation.day << " " << dbDateOfCreation.hour << ":" << dbDateOfCreation.min << ":" << dbDateOfCreation.sec << "\n";
		std::cout << "Id of creator: " << dbIdOfCreator << "\n";
		std::cout << "Date of last change: " << dbDateOfLastChange.year << "/" << dbDateOfLastChange.month << "/" << dbDateOfLastChange.day << " " << dbDateOfLastChange.hour << ":" << dbDateOfLastChange.min << ":" << dbDateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: " << dbIdOfUserLastChange << "\n";
		std::cout << "Id of team: " << dbIdTeam << "\n";
		std::cout << "\n======================================\n";
	}
}