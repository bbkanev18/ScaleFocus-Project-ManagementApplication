#include "AdminMenu.h"

void adminMenu() {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "1. Users Management View\n2. List users\n3. Create new user\n4. Edit user\n5. Delete user\nEsc. To exit program\n";
		switch (_getch())
		{
		case '1':
			//subMenuManagementView
			break;
		case '2':
			subMenuListUser();
			break;
		case 27:
			isTrue = false;
			break;
		default:
			break;
		}
	}
}

void subMenuListUser() {
	bool isTrue = true;
	while (isTrue)
	{
		system("cls");
		std::cout << "1. List all user\n2.List by Id\n";
		switch (_getch())
		{
		case '1':
			//subMenuManagementView
			break;
		case '2':
			subMenuListUser();
			break;
		case 27:
			isTrue = false;
			break;
		default:
			break;
		}
	}
}