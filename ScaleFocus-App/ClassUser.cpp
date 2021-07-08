#include "ClassUser.h"
#include <iostream>
#include <exception>

User::User() {
	m_UserName = "admin";
	m_Password = "adminpass";
	m_role = 1;
}

int& User::getId() { return m_id; }

std::string& User::getUserName() { return m_UserName; }

std::string& User::getPassword() { return m_Password; }

std::string User::getFirstName() { return m_FirstName; }

std::string User::getLastName() { return m_LastName; }

bool& User::getRole() { return m_role; }

int& User::getIdOfCreator() { return m_IdOfCreator; }

int& User::getIdOfUserLastChange() { return m_IdOfUserLastChange; }

void CreatingFirstUser(nanodbc::connection conn)
{
	User admin;

	try {

		nanodbc::statement creatingDefaltAdmin(conn);

		nanodbc::prepare(creatingDefaltAdmin, R"(
		INSERT INTO Users (UserName, Password, Role) 
		VALUES
		(?, ?, ?) ;
	)");

		int role = admin.getRole();
		std::string encrypterdPassword = sha256(admin.getPassword());

		creatingDefaltAdmin.bind(0, admin.getUserName().c_str());
		creatingDefaltAdmin.bind(1, encrypterdPassword.c_str());
		creatingDefaltAdmin.bind(2, &role);

		nanodbc::execute(creatingDefaltAdmin);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
}