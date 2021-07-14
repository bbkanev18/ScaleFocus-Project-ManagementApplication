#include "TeamMenu.h"


void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Breake while and back to admin menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Team Menu---\n1. Print teams\n2. Create new team\n3. Edit team\n4. Delete team\nEsc. To back in main menu\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			subPrintTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2':
			createTeam(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '3':
			subEditTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '4':
			deleteTeam(conn, idOfLoginUser, RoleOfLoginUser);
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
	// Breake while and back to team menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Print Menu---\n1. Print all teams\n2. Print team by id\nEsc. To back in team menu\n";
		// Use _getch to get user choise
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

void subEditTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	// Breake while and back to team menu
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "---Edit Menu---\n1. Edit team title\n2. Add user in team\n3. Remove user from a team\nEsc. To back in team menu\n";
		// Use _getch to get user choise
		switch (_getch())
		{
		case '1':
			editTeamTitle(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '2': 
			addUserInTeam(conn, idOfLoginUser, RoleOfLoginUser);
			break;
		case '3':
			removeUserFromTeam(conn, idOfLoginUser, RoleOfLoginUser);
			break;
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
	// Make statemet called getTeam
	nanodbc::statement getTeam(conn);
	// Make new query to get all team
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
	// Execute query and store the result
	auto result = nanodbc::execute(getTeam);

	// Make new statement called countColums
	nanodbc::statement countColums(conn);
	// Make query to count how many columns
	// to set the size of dynamic array
	nanodbc::prepare(countColums, R"(
		SELECT COUNT(*)
		FROM Teams
	)");

	// Execute query
	auto result2 = nanodbc::execute(countColums);
	// Read the result2
	result2.next();
	// Store information from result
	int colums = result2.get<int>(0);
	
	// Create some variable
	// to check is database is empty
	int* test = new int[colums];
	int counter = 0;
	bool isTrue = true;

	std::cout << "\n";
	while (result.next())
	{
		// Store information from column IsDelete
		int dbIsDelete = result.get<int>(6);
		test[counter] = dbIsDelete;
		counter++;
		printOneTeam(conn, result);
	}
	// Check if database is empty
	for (int i = 0; i < counter; i++)
		if (test[i] == 0)
			isTrue = false;
	if (isTrue)
		std::cout << "\n ERROR: There are no teams in database! \n";
	std::cout << "\n";
	delete[] test;
	system("pause");
}

void editTeamTitle(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::string newTitle;
	std::cout << "\nChoose team to edit title by id: ";
	
	// Getting id from function and if fail give feedback by id
	int id = getTeamById(conn, idOfLoginUser, RoleOfLoginUser);
	
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
	std::cout << "\nIs that correct team you want to edit(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y':{
		std::cout << "\n\nChoose new title: ";
		std::cin >> newTitle;
		
		// Make statement changeOldTitle
		nanodbc::statement changeOldTitle(conn);
		// Make query to update db with new title
		// where id is the return value from function getTeamById
		nanodbc::prepare(changeOldTitle, R"(
			UPDATE Teams
			SET
			Title = ?
			,IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
		)");

		// Convert normal string in to nanodbc string
		nanodbc::string nwT = newTitle;

		// Bind first '?' with new title
		changeOldTitle.bind(0, nwT.c_str());
		// Bind second '?' with id of login user
		changeOldTitle.bind(1, &idOfLoginUser);
		// Bind third '?' with the id of team
		changeOldTitle.bind(2, &id);

		// Execute query to db and store in result
		auto result = nanodbc::execute(changeOldTitle);

		// Check how many rows are affected
		// If there is only one print 'Change successfully :)'
		if (result.affected_rows() == 1)
			std::cout << "\nChange successfully :)\n";
		else
		{
			std::cout << "\n ERROR: In change title \n";
			system("pause");
			subEditTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		system("pause");
		break;
	}
	// n - No
	case 'n':
	case 'N':
		subEditTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	default:
		subEditTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
		break;
	}
}

void addUserInTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int idOfTeam, idOfUser;
	std::cout << "\nChoose id of team which you want to add user: ";
	
	// Getting id from function and if fail give feedback by id
	idOfTeam = getTeamById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (idOfTeam == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (idOfTeam == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct team you want to add user(y/n)";
	
	// Use _getch to get user choise
	switch (_getch())
	{
	case 'y':
	case 'Y': {
		system("cls");
		int numberOfUser;
		int copyOfNumberOfUser;
		int counter = -1;
		std::cout << "Choose how many users you want to assign in that team: ";
		std::cin >> numberOfUser;
		// Create dynamic array
		// to check you already assign user
		int* insertUserAlready = new int[numberOfUser];
		// Make copy of number of user you want to assign
		copyOfNumberOfUser = numberOfUser;

		while (numberOfUser > 0)
		{
			system("cls");
			std::cout << "You need to add: " << numberOfUser << " more user\n";
			std::cout << "If you want to exit, enter -3 in id\n";
			std::cout << "\nChoose user by id: ";

			// Getting id from function and if fail give feedback by id
			int idOfUser = getUserById(conn, idOfLoginUser, RoleOfLoginUser);

			// Check id of user is already assign
			for (int i = 0; i < copyOfNumberOfUser; i++)
			{
				if (insertUserAlready[i] == idOfUser)
				{
					std::cout << "\n !ERROR: You already enter this id!\n";
					idOfUser = -4;
				}
			}

			// If function return -1 is mean id cannot found 
			if (idOfUser == -1) {
				std::cout << "\n ERROR: Not found id!\n";
				system("pause");
			}
			// If function return -2 is mean you enter character in integer
			else if (idOfUser == -2)
				system("pause");
			// If you enter to many user but you do not have enough in db
			else if (idOfUser == -3)
				break;
			// If try to enter user twice
			else if (idOfUser == -4)
				system("pause");
			else {
				insertAssignUser(conn, idOfTeam, idOfUser, numberOfUser, insertUserAlready, counter, idOfLoginUser, RoleOfLoginUser);
			}
		}
		// Free memory from dynamic array
		delete[] insertUserAlready;

		break;
	}
	default:
		break;
	}


}

void removeUserFromTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int idOfTeam, idOfUser;
	std::cout << "\nChoose id of team which you want to remove user: ";
	
	// Getting id from function and if fail give feedback by id
	idOfTeam = getTeamById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (idOfTeam == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (idOfTeam == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct team you want to remove user(y/n)";
	
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y': {
		system("cls");
		int numberOfUser;
		int copyOfNumberOfUser;
		int counter = -1;
		std::cout << "Choose how many users you want to remove in that team: ";
		std::cin >> numberOfUser;
		// Create dynamic array
		// to check you already remove user
		int* insertUserAlready = new int[numberOfUser];
		copyOfNumberOfUser = numberOfUser;

		while (numberOfUser > 0)
		{
			system("cls");
			std::cout << "You need to remove: " << numberOfUser << " more user\n";
			std::cout << "If you want to exit, enter -3 in id\n";
			std::cout << "\nChoose user by id: ";
			// Getting id from function and if fail give feedback by id
			int idOfUser = getUserById(conn, idOfLoginUser, RoleOfLoginUser);

			// Check id of user is already remove
			for (int i = 0; i < copyOfNumberOfUser; i++)
			{
				if (insertUserAlready[i] == idOfUser)
				{
					std::cout << "\n !ERROR: You already enter this id!\n";
					idOfUser = -4;
				}
			}

			// If function return -1 is mean id cannot found 
			if (idOfUser == -1) {
				std::cout << "\n ERROR: Not found id!\n";
				system("pause");
			}
			// If function return -2 is mean you enter character in integer
			else if (idOfUser == -2)
				system("pause");
			// If you what to exit
			else if (idOfUser == -3)
				break;
			// If try to remove user twice
			else if (idOfUser == -4)
				system("pause");
			else {
				removeAssignUser(conn, idOfTeam, idOfUser, numberOfUser, insertUserAlready, counter, idOfLoginUser, RoleOfLoginUser);
			}
		}
		// Free memory from dynamic array
		delete[] insertUserAlready;

		break;
	}
	default:
		break;
	}
}

int getTeamById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int id;

	std::cin >> id;
	// If you enter letter in integer
	if (std::cin.fail())
	{
		// clear all error flags from visual studio
		std::cin.clear();
		// ignore INT_MAX symbols when you press enter
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "\n ERROR: wrong integer value \n";
		return -2;
	}

	// Creating statement getTeamById
	nanodbc::statement getTeamById(conn);
	// Make query to db to find team by id
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

	// Bind '?' with id of team
	getTeamById.bind(0, &id);

	// Execute query
	auto result = nanodbc::execute(getTeamById);

	// Check is there somthing db and printed
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
	// Check is the team is deleted from db 
	if (dbIsDeleted == 0)
	{
		std::cout << "\n======================================\n";
		std::cout << "Id: " << dbId << "\n";
		std::cout << "Title: " << dbTitle << "\n";
		std::cout << "Date of creation: " << dbDateOfCreation.year << "/" << dbDateOfCreation.month << "/" << dbDateOfCreation.day << " " << dbDateOfCreation.hour << ":" << dbDateOfCreation.min << ":" << dbDateOfCreation.sec << "\n";
		std::cout << "Id of creator: ";
		// Get id of creator and print username of creator
		printUserNameByIdOfCreatorOnTeam(conn, dbId);
		std::cout << "Date of last change: " << dbDateOfLastChange.year << "/" << dbDateOfLastChange.month << "/" << dbDateOfLastChange.day << " " << dbDateOfLastChange.hour << ":" << dbDateOfLastChange.min << ":" << dbDateOfLastChange.sec << "\n";
		std::cout << "Id of the user that did the last change: ";
		// Get id of last edit and print username
		printUserNameByIdOfLastChangeOnTeam(conn, dbId);
		std::cout << "\nUser in Team:\n";

		// Make statement getUserAssignInTeam
		nanodbc::statement getUserAssignInTeam(conn);
		// Make query to db to find user that assign in team
		nanodbc::prepare(getUserAssignInTeam, R"(
			SELECT IdOfUser
			FROM UsersTeams
			WHERE IdOfTeam = ?
		)");

		// Bind '?' with id of team
		getUserAssignInTeam.bind(0, &dbId);

		// Execute query
		auto result = nanodbc::execute(getUserAssignInTeam);
		// Read first row
		// if it is empty print 'There are no users assign in team'
		if (result.next()) {
				printUserAssignInTeam(conn, result);
				// If there are more one user assign in team
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
	// Create statement getIdOfCreator
	nanodbc::statement getIdOfCreator(conn);
	// Create new query
	// selecting id of creator from currently id team
	nanodbc::prepare(getIdOfCreator, R"(
		SELECT IdOfCreator
			FROM Teams
		WHERE Id = ?
	)");
	// Bind first '?' wiht id of currently printing team
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

void printUserNameByIdOfLastChangeOnTeam(nanodbc::connection conn, int id) {
	// Create statement getIdOfLastChange
	nanodbc::statement getIdOfLastChange(conn);
	// Make new query
	// selecting id of last edit user from currently id user
	nanodbc::prepare(getIdOfLastChange, R"(
			SELECT IdOfUserLastChange
			FROM Teams
			WHERE Id = ?
			)");
	// Bind first '?' wiht id of currently printing team
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

int printUserAssignInTeam(nanodbc::connection conn, nanodbc::result& result) {
	// Get id of user
	int idOfUser = result.get<int>(0);

	// Make new statement getUserAssignInTeam
	nanodbc::statement getUserAssignInTeam(conn);
	// Make query to get first and last name of assign user
	nanodbc::prepare(getUserAssignInTeam, R"(
		SELECT 
			FirstName,
			LastName,
			IsDeleted
		FROM Users
		WHERE Id = ?
	)");

	// Bind '?' with id of user
	getUserAssignInTeam.bind(0, &idOfUser);

	// Execute query
	auto result2 = nanodbc::execute(getUserAssignInTeam);
	
	// Read result2
	result2.next();
	int isDeleted = result2.get<int>(2);
	// Check is user is delete
	if (isDeleted == 0)
	{
		// Cout first and last name of assign user
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

	// Make statement createNewTeam
	nanodbc::statement createNewTeam(conn);
	// Make query to add team in db
	nanodbc::prepare(createNewTeam, R"(
		INSERT INTO Teams (
		Title, IdOfCreator, IdOfUserLastChange, IsDeleted)
		VALUES
		(?, ?, ?, ?);
	)");

	// Binding '?' with team information
	createNewTeam.bind(0, title.c_str());
	createNewTeam.bind(1, &idOfLoginUser);
	createNewTeam.bind(2, &idOfLoginUser);
	createNewTeam.bind(3, &IsDeleted);

	// Execute query
	auto result = nanodbc::execute(createNewTeam);

	// If there is affecter rows print 'Create successfully :)'
	if (result.affected_rows() == 1)
		std::cout << "\nCreate successfully :)\n";
	else{
		std::cout << "\n ERROR: In creating team \n";
		system("pause");
		return;
	}

	system("pause");
	// Make new statement findCreatedTeam
	nanodbc::statement findCreatedTeam(conn);
	// Make new query to find id created team
	nanodbc::prepare(findCreatedTeam, R"(
		SELECT Id
		FROM Teams
		WHERE Title = ?
	)");

	// Bind '?' with title was created team
	findCreatedTeam.bind(0, title.c_str());

	// Execute query
	auto result2 = nanodbc::execute(findCreatedTeam);
	result2.next();
	// Store id of created team
	int idOfTeam = result2.get<int>(0);

	system("cls");
	int numberOfUser;
	int copyOfNumberOfUser;
	int counter = -1;
	std::cout << "Choose how many users you want to assign in that team: ";
	std::cin >> numberOfUser;
	// Create dynamic array
	// to check you already add user
	int *insertUserAlready= new int[numberOfUser];
	// make copy of number of user you want to enter
	copyOfNumberOfUser = numberOfUser;


	while (numberOfUser > 0)
	{
		system("cls");
		std::cout << "You need to add: " << numberOfUser << " more user\n";
		std::cout << "If you want to exit, enter -3 in id\n";
		std::cout << "\nChoose user by id: ";
		// Getting id from function and if fail give feedback by id
		int idOfUser = getUserById(conn, idOfLoginUser, RoleOfLoginUser);

		// Check id of user is already add
		for (int i = 0; i < copyOfNumberOfUser; i++)
		{
			if (insertUserAlready[i] == idOfUser)
			{
				std::cout << "\n !ERROR: You already enter this id!\n";
				idOfUser = -4;
			}
		}
		
		// If function return -1 is mean id cannot found 
		if (idOfUser == -1) {
			std::cout << "\n ERROR: Not found id!\n";
			system("pause");
		}
		// If function return -2 is mean you enter character in integer
		else if (idOfUser == -2)
			system("pause");
		// If you what to exit
		else if (idOfUser == -3)
			break;
		// If try to add user twice
		else if (idOfUser == -4)
			system("pause");
		else{
			insertAssignUser(conn, idOfTeam, idOfUser, numberOfUser, insertUserAlready, counter, idOfLoginUser, RoleOfLoginUser);
		}
	}
	// Free memory from dynamic array
	delete[] insertUserAlready;
	std::cout << "\n\n Create and insert user successfully :) \n\n";
	system("pause");
}

void insertAssignUser(nanodbc::connection conn, int idOfTeam , int idOfUser, int& numberOfUser, int insertUserAlready[], int& counter, int& idOfLoginUser, bool& RoleOfLoginUser) {

	std::cout << "\nIs that correct user you want to add in team(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y': {
		// Make statement insertUserInTeam
		nanodbc::statement insertUserInTeam(conn);
		// Make new query to database to insert new user into team
		nanodbc::prepare(insertUserInTeam, R"(
		INSERT INTO UsersTeams 
			(IdOfUser, IdOfTeam)
		VALUES
			(?, ?)
		)");
		// Binding '?' with id of user and team
		insertUserInTeam.bind(0, &idOfUser);
		insertUserInTeam.bind(1, &idOfTeam);

		// Execute query
		nanodbc::execute(insertUserInTeam);
		// Save user in dynamic array
		numberOfUser--;
		++counter;
		insertUserAlready[counter] = idOfUser;
		std::cout << "\n\n Insert successfully :) \n\n";

		// Make new statement updateDB
		nanodbc::statement updateDB(conn);
		// Make new query to update database
		nanodbc::prepare(updateDB, R"(
			UPDATE Teams
			SET
			IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
			
		)");
		// Binding '?' with id of longin user and team
		updateDB.bind(0, &idOfLoginUser);
		updateDB.bind(1, &idOfTeam);
		// Execute query
		nanodbc::execute(updateDB);

		system("pause");
		break;
	}
	default:
		break;
	}

}

void removeAssignUser(nanodbc::connection conn, int idOfTeam, int idOfUser, int& numberOfUser, int insertUserAlready[], int& counter, int& idOfLoginUser, bool& RoleOfLoginUser) {
	std::cout << "\nIs that correct user you want to remove from team(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y': {
		// Make statement removeUserInTeam
		nanodbc::statement removeUserInTeam(conn);
		// Make query to remove assign user in db
		nanodbc::prepare(removeUserInTeam, R"(
			DELETE FROM UsersTeams
			WHERE IdOfUser = ? and IdOfTeam = ?
		)");

		// Binding '?' wiht id of user and team
		removeUserInTeam.bind(0, &idOfUser);
		removeUserInTeam.bind(1, &idOfTeam);
		//Executing query
		nanodbc::execute(removeUserInTeam);
		// Save remove id user
		numberOfUser--;
		++counter;
		insertUserAlready[counter] = idOfUser;
		std::cout << "\n\n Remove user successfully :) \n\n";
		nanodbc::statement updateDB(conn);
		// Make query to updata team
		nanodbc::prepare(updateDB, R"(
			UPDATE Teams
			SET
			IdOfUserLastChange = ?
			,DateOfLastChange = GETDATE()
			WHERE Id = ?;
			
		)");

		// Binding '?' with id of login user and team
		updateDB.bind(0, &idOfLoginUser);
		updateDB.bind(1, &idOfTeam);
		// Execute query
		nanodbc::execute(updateDB);

		system("pause");
		break;
	}
	default:
		break;
	}
}

void deleteTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser) {
	int idOfTeam;
	std::cout << "\nChoose id of team which you want to remove from database: ";
	
	// Getting id from function and if fail give feedback by id
	idOfTeam = getTeamById(conn, idOfLoginUser, RoleOfLoginUser);
	
	// If function return -1 is mean id cannot found
	if (idOfTeam == -1) {
		std::cout << "\n ERROR: Not found id!\n";
		system("pause");
		return;
	}
	// If function return -2 is mean you enter character in integer
	else if (idOfTeam == -2)
	{
		system("pause");
		return;
	}
	std::cout << "\nIs that correct team you want remove from database(y/n)";
	// Use _getch to get user choise
	switch (_getch())
	{
	// y -> Yes
	case 'y':
	case 'Y':{
		// Make statement deleteTeam
		nanodbc::statement deleteTeam(conn);
		// Make query to change isdeleted to 1
		nanodbc::prepare(deleteTeam, R"(
			UPDATE Teams
			SET
			IsDeleted = 1
			WHERE Id = ?
		)");
		// Bind '?' with id of team
		deleteTeam.bind(0, &idOfTeam);
		// Execute query
		auto  result = nanodbc::execute(deleteTeam);

		// Check if there is affecter rows and print 'Remove team successfully :)'
		if (result.affected_rows() == 1)
		{
			std::cout << "\n Remove team successfully :) \n";
			system("pause");
		}
		else
		{
			std::cout << "\n ERROR: In remove team \n";
			system("pause");
			subTeamMenu(conn, idOfLoginUser, RoleOfLoginUser);
		}
		break;
	}
	default:
		break;
	}
}