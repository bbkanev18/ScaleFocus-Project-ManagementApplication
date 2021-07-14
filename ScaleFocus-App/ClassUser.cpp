#include "ClassUser.h"
#include <iostream>
#include <exception>

User::User() {
	m_UserName = "admin";
	m_Password = "adminpass";
	m_FirstName = "admin";
	m_LastName = "admin";
	m_role = 1;
	m_IsDeleted = 0;
}

int& User::getId() { return m_id; }

std::string& User::getUserName() { return m_UserName; }

std::string& User::getPassword() { return m_Password; }

std::string& User::getFirstName() { return m_FirstName; }

std::string& User::getLastName() { return m_LastName; }

bool& User::getRole() { return m_role; }

int& User::getIdOfCreator() { return m_IdOfCreator; }

int& User::getIdOfUserLastChange() { return m_IdOfUserLastChange; }

void CreatingFirstUser(nanodbc::connection conn)
{
	User admin;

	try {
		// Make statement called creatingDefaltAdmin
		nanodbc::statement creatingDefaltAdmin(conn);

		// Make query to db to insert first user
		nanodbc::prepare(creatingDefaltAdmin, R"(
		INSERT INTO Users (UserName, Password, FirstName, LastName, Role, IsDeleted) 
		VALUES
		(?, ?, ?, ?, ?, ?) ;
	)");

		int role = admin.getRole();
		int IsDelete = admin.getIsDeleted();
		// Encrypting password with sha256
		std::string encrypterdPassword = sha256(admin.getPassword());

		// Binding '?' with default admin information
		creatingDefaltAdmin.bind(0, admin.getUserName().c_str());
		creatingDefaltAdmin.bind(1, encrypterdPassword.c_str());
		creatingDefaltAdmin.bind(2, admin.getFirstName().c_str());
		creatingDefaltAdmin.bind(3, admin.getLastName().c_str());
		creatingDefaltAdmin.bind(4, &role);
		creatingDefaltAdmin.bind(5, &IsDelete);

		nanodbc::execute(creatingDefaltAdmin);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
}


int& User::getIsDeleted() { return m_IsDeleted; }