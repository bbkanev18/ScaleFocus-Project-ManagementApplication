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