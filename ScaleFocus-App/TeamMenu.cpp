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
			createTeam(conn, idOfLoginUser, RoleOfLoginUser);
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
		case '2': {
			std::cout << "\nChoose team id to print: ";
			int id = getTeamById(conn, idOfLoginUser, RoleOfLoginUser);
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
			subTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
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


	nanodbc::statement countColums(conn);

	nanodbc::prepare(countColums, R"(
		SELECT COUNT(*)
		FROM Teams
	)");

	auto result2 = nanodbc::execute(countColums);
	result2.next();
	int colums = result2.get<int>(0);
	
	int* test = new int[colums];
	int counter = 0;
	bool isTrue = true;

	std::cout << "\n";
	while (result.next())
	{
		int dbIsDelete = result.get<int>(6);
		test[counter] = dbIsDelete;
		counter++;
		printOneTeam(conn, result);
	}
	for (int i = 0; i < counter; i++)
		if (test[i] == 0)
			isTrue = false;
	if (isTrue)
		std::cout << "\n ERROR: There are no teams in database! \n";
	std::cout << "\n";
	delete[] test;
	system("pause");
}

int getTeamById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int id;

	std::cin >> id;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "\n ERROR: wrong integer value \n";
		return -2;
	}

	nanodbc::statement getTeamById(conn);

	nanodbc::prepare(getTeamById, R"(
		SELECT
			Id,
			Title,
			DateOfCreation,
			IdOfCreator,
			DateOfLastChange,
			IdOfUserLastChange,
			IsDeleted
		FROM Teams
		WHERE Id = ?
	)");

	getTeamById.bind(0, &id);

	auto result = nanodbc::execute(getTeamById);

	if (result.next()) {
		return printOneTeam(conn, result);
	}
	else {
		return -1;
	}
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
		std::cout << "\n======================================\n";
		std::cout << "Id: " << dbId << "\n";
		std::cout << "Title: " << dbTitle << "\n";
		std::cout << "Date of creation: " << dbDateOfCreation.year << "/" << dbDateOfCreation.month << "/" << dbDateOfCreation.day << " " << dbDateOfCreation.hour << ":" << dbDateOfCreation.min << ":" << dbDateOfCreation.sec << "\n";
		std::cout << "Id of creator: ";
		printUserNameByIdOfCreatorOnTeam(conn, dbId);
		std::cout << "Date of last change: " << dbDateOfLastChange.year << "/" << dbDateOfLastChange.month << "/" << dbDateOfLastChange.day << " " << dbDateOfLastChange.hour << ":" << dbDateOfLastChange.min << ":" << dbDateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: ";
		printUserNameByIdOfLastChangeOnTeam(conn, dbId);
		std::cout << "\nUser in Team:\n";


		nanodbc::statement getUserAssignInTeam(conn);

		nanodbc::prepare(getUserAssignInTeam, R"(
			SELECT IdOfUser
			FROM UsersTeams
			WHERE IdOfTeam = ?
		)");

		getUserAssignInTeam.bind(0, &dbId);


		auto result = nanodbc::execute(getUserAssignInTeam);
		if (result.next()) {
				printUserAssignInTeam(conn, result);
				while (result.next()) 
					printUserAssignInTeam(conn, result);
		}
		else
			std::cout << "\n--> There are no users assign in team\n";

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

int printUserAssignInTeam(nanodbc::connection conn, nanodbc::result& result) {
	nanodbc::statement getUserAssignInTeam(conn);
	
	nanodbc::prepare(getUserAssignInTeam, R"(
		SELECT 
			FirstName,
			LastName,
			IsDeleted
		FROM Users
		WHERE Id = ?
	)");

	int idOfUser = result.get<int>(0);
	getUserAssignInTeam.bind(0, &idOfUser);

	auto result2 = nanodbc::execute(getUserAssignInTeam);
	

	result2.next();
	int isDeleted = result2.get<int>(2);
	if (isDeleted == 0)
	{
		std::string dbFirstName = result2.get<nanodbc::string>(0);
		std::string dbLastName = result2.get<nanodbc::string>(1);
		std::cout << "\n--> " << dbFirstName << " " << dbLastName << "\n";
		return 0;
	}
	else
		return -1;
}

void createTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	system("cls");
	int IsDeleted = 0;
	std::string title;
	std::cout << "Title of team: ";
	std::cin >> title;

	nanodbc::statement createNewTeam(conn);

	nanodbc::prepare(createNewTeam, R"(
		INSERT INTO Teams (
		Title, IdOfCreator, IdOfUserLastChange, IsDeleted)
		VALUES
		(?, ?, ?, ?);
	)");


	createNewTeam.bind(0, title.c_str());
	createNewTeam.bind(1, &idOfLoginUser);
	createNewTeam.bind(2, &idOfLoginUser);
	createNewTeam.bind(3, &IsDeleted);

	auto result = nanodbc::execute(createNewTeam);

	if (result.affected_rows() == 1)
		std::cout << "\nCreate successfully :)\n";
	else{
		std::cout << "\n ERROR: In creating team \n";
		system("pause");
		return;
	}

	system("pause");
	nanodbc::statement findCreatedTeam(conn);

	nanodbc::prepare(findCreatedTeam, R"(
		SELECT Id
		FROM Teams
		WHERE Title = ?
	)");

	findCreatedTeam.bind(0, title.c_str());

	auto result2 = nanodbc::execute(findCreatedTeam);
	result2.next();
	int idOfTeam = result2.get<int>(0);

	system("cls");
	int numberOfUser;
	int copyOfNumberOfUser;
	int counter = -1;
	std::cout << "Choose how many users you want to assign in that team: ";
	std::cin >> numberOfUser;
	int *insertUserAlready= new int[numberOfUser];
	copyOfNumberOfUser = numberOfUser;


	while (numberOfUser > 0)
	{
		system("cls");
		std::cout << "You need to add: " << numberOfUser << " more user\n";
		std::cout << "If you want to exit, enter -3 in id\n";
		std::cout << "\nChoose user by id: ";
		int idOfUser = getUserById(conn, idOfLoginUser, RoleOfLoginUser);

		for (int i = 0; i < copyOfNumberOfUser; i++)
		{
			if (insertUserAlready[i] == idOfUser)
			{
				std::cout << "\n !ERROR: You already enter this id!\n";
				idOfUser = -4;
			}
		}
		
		if (idOfUser == -1) {
			std::cout << "\n ERROR: Not found id!\n";
			system("pause");
		}
		else if (idOfUser == -2)
			system("pause");
		else if (idOfUser == -3)
			break;
		else if (idOfUser == -4)
			system("pause");
		else{
			insertAssignUser(conn, idOfTeam, idOfUser, numberOfUser, insertUserAlready, counter);
		}
	}
	delete[] insertUserAlready;
	std::cout << "\n\n Create and insert user successfully :) \n\n";
	system("pause");
}

void insertAssignUser(nanodbc::connection conn, int idOfTeam , int idOfUser, int& numberOfUser, int insertUserAlready[1000], int& counter) {

	std::cout << "\nIs that correct user you want to add in team(y/n)";
	switch (_getch())
	{
	case 'y':
	case 'Y': {
		nanodbc::statement insertUserInTeam(conn);

		nanodbc::prepare(insertUserInTeam, R"(
		INSERT INTO UsersTeams 
			(IdOfUser, IdOfTeam)
		VALUES
			(?, ?)
		)");

		insertUserInTeam.bind(0, &idOfUser);
		insertUserInTeam.bind(1, &idOfTeam);

		nanodbc::execute(insertUserInTeam);
		numberOfUser--;
		++counter;
		insertUserAlready[counter] = idOfUser;
		std::cout << "\n\n Insert successfully :) \n\n";
		system("pause");
		break;
	}
	default:
		break;
	}

}